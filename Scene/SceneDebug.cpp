#include "SceneDebug.h"
#include <DxLib.h>
#include "game.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/EnemyRush.h"
#include "Object/Field.h"
#include "SceneTitle.h"

#include "Util/Vec3.h"

#include "Sound.h"

namespace
{
	// 初期位置
	Vec3 kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneDebug::SceneDebug():
	m_slowCount(0),
	m_enemyCount(0),
	m_isInvincible(false),
	m_pPlayer(nullptr),
	m_pField(nullptr)
{
	m_pEnemyRush.push_back(std::make_shared<EnemyRush>(kPos));
	m_pPlayer = new Player;
	m_pField = new Field;
}

SceneDebug::~SceneDebug()
{
	delete m_pPlayer;
	delete m_pField;

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

	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Init();
	}

	m_isInvincible = true;

	Sound::startBgm(Sound::SoundId_Main, 50);
}

void SceneDebug::End()
{

	Sound::stopBgm(Sound::SoundId_Main);

	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->End();
	}

	m_pPlayer->End();

	m_pField->End();
}

// 更新 //
SceneBase* SceneDebug::Update()
{
	m_pField->Update();

	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Update();
	}

//	printfDx("%d\n", m_pPlayer->GetSlowWorld());
	// スローモーション処理
	
	///////////////////////////////
	// ここはプレイヤーcppに置く //
	//     プレイヤーの操作      //
	///////////////////////////////
	m_pPlayer->UpdateControl();

	m_slowCount = (m_slowCount += 1) % m_pPlayer->GetSlowWorld();

	if (m_slowCount == 0)
	{
		// プレイヤーの更新
		m_pPlayer->Update();
		for (auto& enemyRush : m_pEnemyRush)
		{
			enemyRush->Update();

			//// 敵が画面座標から出たら削除
			if (enemyRush->GetPos().x < 0)
			{
				enemyRush->End();
			}
		}

		// 敵を生成(まだ完全なエネミー削除処理なし)
		m_enemyCount++;
		if (m_enemyCount > 60 * m_tempRand)
		{
			m_enemyCount = 0;
			Vec3 pos = { m_pPlayer->GetPos().x,0.0f,0.0f};
			pos.x += 3000;
			m_pEnemyRush.push_back(std::make_shared<EnemyRush>(pos));
		}

		// 次のエネミーをランダム秒に出現
		if (m_enemyCount == 0)
		{
			m_tempRand = GetRand(2);
		}
	}

	// プレイヤーとエネミーの当たり判定
	playerCheckHit();
	// プレイヤーと地面の当たり判定
	fieldCheckHit();
	// 無敵時間の調整
	if (!m_pPlayer->GetInvincible()) m_isInvincible = false;


	
	// フェイド処理
	UpdateFade();

	if (m_pPlayer->GetPos().x > 30000)
	{
		return(new SceneTitle);
	}
	if (m_pPlayer->GetPos().y < -1000.0f)
	{
		return(new SceneTitle);
	}
	return this;
}
// 描画 //
void SceneDebug::Draw()
{

	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Draw();
	}

	m_pPlayer->Draw();

	m_pField->Draw();

	// フェイド処理
	SceneBase::DrawFade();
}

void SceneDebug::playerCheckHit()
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
				m_pPlayer->OnDamage(30);
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

void SceneDebug::fieldCheckHit()
{
	// 地面判定の情報を渡す
	m_pPlayer->FieldCheckHit(false);
	// 地面との判定
	// DxLibの関数を利用して当たり判定をとる

	for (int x = 0; x < m_pField->GetModelNumX(); x++)
	{
		MV1_COLL_RESULT_POLY_DIM result;		//あたりデータ
		result = MV1CollCheck_Capsule(
			m_pField->GetModelHandle(x),
			m_pField->GetColFrameIndex(),
			m_pPlayer->GetPos(),
			m_pPlayer->GetSize(),
			m_pPlayer->GetRadius());
		if (result.HitNum > 0)	//1枚以上のポリゴンと当たっていたらモデルにあっている設定
		{
			// 地面判定の情報を渡す
			m_pPlayer->FieldCheckHit(true);
		}
		// 当たり判定情報の後始末
		MV1CollResultPolyDimTerminate(result);
	}
}
