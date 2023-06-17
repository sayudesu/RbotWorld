#include "SceneDebug.h"
#include "SceneTitle.h"
#include "SceneGameOver.h"
#include "SceneGameClear.h"
#include <DxLib.h>
#include "game.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/EnemyRush.h"
#include "Object/Field.h"
#include "Object/Map/Map.h"

#include "Coin.h"
#include "ItemManegaer.h"

#include "Sound.h"

#include <cassert>

namespace
{
	// 初期位置
	Vec3 kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneDebug::SceneDebug():
	m_slowCount(0),
	m_enemyCount(0),
	m_tempRand(0),
	m_isInvincible(false),
	m_pPlayer(nullptr),
	m_pField(nullptr),
	m_pMap(nullptr)
{
	// インスタンス作成
	m_pItem = std::make_shared<ItemManegaer>();

	m_pPlayer = new Player;
	m_pField = new Field;
	m_pMap = new Map;
}

SceneDebug::~SceneDebug()
{

	m_pItem.reset();

	delete m_pPlayer;
	delete m_pField;
	delete m_pMap;
}

void SceneDebug::Init()
{
	// 3D関連の設定
	// Zバッファを使用する
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);
	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);

	m_pPlayer->Init();

	m_pField->Init();

	m_pMap->Load();

	// コインの数
	const int coinNum = static_cast<int>(m_pField->GetCoinNum());
	// コインの数分の配列浅間
	int* posX = new int[coinNum];
	int* posY = new int[coinNum];
	// コインカウント用
	int coinCount = -1;
	
	// コインの数をカウント
	// コインの位置を取得
	// コインの数を超えたら初期化
	for (int y = 0; y < m_pField->GetModelNumY(); y++)
	{
		for (int x = 0; x < m_pField->GetModelNumX(); x++)
		{
			if (m_pField->GetCoinPosX(y, x) != 0 && m_pField->GetCoinPosY(y, x) != 0)
			{				
				coinCount++;

				posX[coinCount] = m_pField->GetCoinPosX(y, x);
				posY[coinCount] = m_pField->GetCoinPosY(y, x);
		
				if (coinCount >= m_pField->GetCoinNum())
				{
					coinCount = 0;
				}
			}
		}
	}

	// コインを作成
	m_pItem->CreateCoin(posX, posY, coinCount);
	// 配列の要素を削除
	delete[] posX;
	delete[] posY;

	m_isInvincible = true;

	Sound::startBgm(Sound::SoundId_Main, 50);
}

void SceneDebug::End()
{
	m_pPlayer->End();

	m_pField->End();

	Sound::stopBgm(Sound::SoundId_Main);
}

// 更新 //
SceneBase* SceneDebug::Update()
{
	// フェイド処理
	UpdateFade();

	m_pField->Update();

	// プレイヤーの操作
	m_pPlayer->UpdateControl();

	m_pItem->Update();

	// ゲームスロー再生用
	m_slowCount = (m_slowCount += 1) % m_pPlayer->GetSlowWorld();

	if (m_slowCount == 0)
	{
		// プレイヤーの更新
		m_pPlayer->Update();
	}

	// プレイヤーとエネミーの当たり判定
	PlayerCheckHit();
	// プレイヤーと地面の当たり判定
	FieldCheckHit();

	// 無敵時間の調整
	if (!m_pPlayer->GetInvincible()) m_isInvincible = false;

	// ゴールに到達するとゲームクリア画面に移動
	if (m_pPlayer->GetPos().x > 30000)
	{
		StartFadeOut();
		//SceneBase::UpdateFade();

		return(new SceneGameClear);	
	}

	// 落下するかプレイヤーが死んだ場合はゲームオーバー画面に移動
	if (m_pPlayer->GetPos().y < -1000.0f ||
		m_pPlayer->GetIsDead())
	{
		if (!IsFading())
		{
			return(new SceneGameOver);
		}
	}
	return this;
}
// 描画 //
void SceneDebug::Draw()
{
	m_pMap->Draw();
	m_pPlayer->Draw();
	m_pField->Draw();
	m_pItem->Draw();

#if false
	for (int y = 0; y < m_pField->GetModelNumY(); y++)
	{
		for (int x = 0; x < m_pField->GetModelNumX(); x++)
		{
			if (m_pField->GetCoinPosX(y, x) != 0)
			{
				int posX = m_pField->GetCoinPosX(y, x);
				int posY = m_pField->GetCoinPosY(y, x);
				DrawSphere3D(VGet(posX, posY, 5.0f), 80.0f, 32.0f, 0xffffff, 0xffffff, true);
			}
		}
	}
#endif
	// フェイド処理
	SceneBase::DrawFade();
}

void SceneDebug::PlayerCheckHit()
{
	// 当たり判定の情報
	if (!m_isInvincible)
	{
		// 敵との判定
		for (auto& enemy : m_pEnemyRush)
		{
			// DxLibの関数を利用して当たり判定をとる
			MV1_COLL_RESULT_POLY_DIM result;		//あたりデータ

			result = MV1CollCheck_Capsule(
				enemy->GetModelHandle(),
				enemy->GetColFrameIndex(),
				m_pPlayer->GetPos(),
				m_pPlayer->GetSize(),
				m_pPlayer->GetRadius());
			if (result.HitNum > 0)	//1枚以上のポリゴンと当たっていたらモデルにあっている設定
			{
				// ダメージ量を渡す
				m_pPlayer->OnDamage(enemy->GetAttackDamage());
				// 振動開始
				StartJoypadVibration(DX_INPUT_PAD1, 1000, 60, -1);
				// ダメージをくらった
				m_isInvincible = true;
			}

			// 当たり判定情報の後始末
			MV1CollResultPolyDimTerminate(result);
		}
	}
}

void SceneDebug::FieldCheckHit()
{
	// 地面判定の情報を渡す
	m_pPlayer->FieldCheckHit(false);
	// 地面との判定
	// DxLibの関数を利用して当たり判定をとる

	for (int y = 0; y < m_pField->GetModelNumY(); y++)
	{
		for (int x = 0; x < m_pField->GetModelNumX(); x++)
		{
			MV1_COLL_RESULT_POLY_DIM result;		//あたりデータ
			result = MV1CollCheck_Capsule(
				m_pField->GetModelHandle(y,x),
				m_pField->GetColFrameIndex(y,x),
				m_pPlayer->GetPos(),
				m_pPlayer->GetSize(),
				m_pPlayer->GetRadius());
			if (result.HitNum > 0)	//1枚以上のポリゴンと当たっていたらモデルにあっている設定
			{
				// 地面判定の情報を渡す
				m_pPlayer->FieldCheckHit(true);
				m_pPlayer->FieldPosY(m_pField->SetPosY(y, x));
			}
			// 当たり判定情報の後始末
			MV1CollResultPolyDimTerminate(result);
		}
	}

}
