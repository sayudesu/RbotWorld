#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameOver.h"
#include "SceneGameClear.h"
#include <DxLib.h>
#include "game.h"
#include "Object/Player.h"

#include "Object/Field.h"
#include "Object/Map/Map.h"
#include "UI.h"

#include "Object/Coin.h"
#include "Object/ItemManegaer.h"
#include "ItemName.h"

#include "FieldBase.h"

#include "Sound.h"

#include <cassert>

namespace
{
	// 初期位置
	Vec3 kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneMain::SceneMain(std::shared_ptr<FieldBase>field):
	m_slowCount(0),
	m_enemyCount(0),
	m_tempRand(0),
	m_isInvincible(false),
	m_pPlayer(nullptr),
	m_pField(nullptr),
	m_pMap(nullptr),
	m_pUi(nullptr),
	m_pFieldOne(field)
{
	// インスタンス作成
	m_pItem = std::make_shared<ItemManegaer>();
	
	m_pPlayer = new Player;
	m_pField = new Field;
	m_pMap = new Map;
	m_pUi = new UI;

}

SceneMain::~SceneMain()
{

	m_pItem.reset();

	delete m_pPlayer;
	delete m_pField;
	delete m_pMap;
}

void SceneMain::Init()
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
	// コインの数
	m_coinNum = coinNum + 1;

	// コインの数分
	// コインの位置を代入
	for (int i = 0; i < m_coinNum; i++)
	{
		m_CoinPosX.push_back(m_pField->GetCoinX()[i]);
		m_CoinPosY.push_back(m_pField->GetCoinY()[i]);
	}

	// コインを作成
	m_pItem->CreateCoin(m_CoinPosX, m_CoinPosY, m_coinNum);

	// ダイヤの数
	const int diamondNum = static_cast<int>(m_pField->GetDiamondNum());
	// ダイヤの数
	m_diamondNum = diamondNum + 1;

	// ダイヤの数分
	// ダイヤの位置を代入
	for (int i = 0; i < m_diamondNum; i++)
	{
		m_diamondPosX.push_back(m_pField->GetDiamondX()[i]);
		m_diamondPosY.push_back(m_pField->GetDiamondY()[i]);
	}

	// コインを作成
	m_pItem->CreateDiamond(m_diamondPosX, m_diamondPosY, m_diamondNum);


	m_pUi->SetItemMaxNum(Item::coin, m_coinNum);
	m_pUi->SetItemMaxNum(Item::diamond, m_diamondNum);

	m_isInvincible = true;

	m_hDoor = LoadGraph("Data/Img/DoorH.png");

	// BGM再生
	Sound::startBgm(Sound::SoundId_Main, 50);
}

void SceneMain::End()
{
	m_pPlayer->End();

	m_pField->End();

	DeleteGraph(m_hDoor);

	Sound::stopBgm(Sound::SoundId_Main);
}

// 更新 //
SceneBase* SceneMain::Update()
{

	m_pFieldOne->Update();
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

	// プレイヤーと地面の当たり判定
	FieldCheckHit();

	// ゴールに到達するとゲームクリア画面に移動
	if (m_pPlayer->GetPos().x > 30000)
	{
		m_pPlayer->SetMoveing(false);
		if (SceneBase::UpdateSliderClose())
		{
			// スコアを渡す
			return new SceneGameClear{ m_pUi->GetScore(),m_coinCount,m_diamondCount };
		}
	}
//	return new SceneGameClear{ m_pUi->GetScore(),m_coinCount,m_diamondCount };
	// 落下するかプレイヤーが死んだ場合はゲームオーバー画面に移動
	if (m_pPlayer->GetPos().y < -1000.0f ||
		m_pPlayer->GetIsDead())
	{
		m_pPlayer->SetMoveing(false);
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneGameOver;
		}
	}

	if (DxLib::CheckHitKey(KEY_INPUT_M))
	{
		m_pUi->SetItemMaxNum(Item::coin, 3);
	}

	// 関数化します //

	// プレイヤーの判定用座標
	// コインの位置
	// プレイヤーの位置からコインの位置を引く
	// 触れたコインの数をカウントする
	VECTOR pos = { m_pPlayer->GetPos().x,m_pPlayer->GetPos().y + 250.0f ,m_pPlayer->GetPos().z };
	// コインとプレイヤーの当たり判定
	for (int i = 0; i < m_coinNum; i++)
	{
		const VECTOR coinPos = VGet(m_CoinPosX[i], m_CoinPosY[i] + 150.0f, m_pPlayer->GetPos().z);

		const VECTOR vec = VSub(pos, coinPos);

		const float del = VSize(vec);

		// ベクトルのサイズを取得する
		// コインに当たっている場合は判定を行わない
		// 触れたコインの番号を渡す
		if (del < 128 * 2 + 62)
		{
			if (!m_pItem->isErase(Item::coin,i))
			{
				m_pItem->SetEraseNo(Item::coin,i);
				m_coinCount++;
			}
		}
	}

	// コインとプレイヤーの当たり判定
	// プレイヤーの位置からコインの位置を引く
	// ベクトルのサイズを取得する
	// コインの位置
	for (int i = 0; i < m_diamondNum; i++)
	{
		const VECTOR diamondPos = VGet(m_diamondPosX[i], m_diamondPosY[i] + 250.0f, m_pPlayer->GetPos().z);

		const VECTOR vec = VSub(pos, diamondPos);

		const float del = VSize(vec);

		// コインに当たっている場合は判定を行わない
		// 触れたコインの番号を渡す
		// 触れたコインの数をカウントする
		if (del < 128 * 2 + 62)
		{
			if (!m_pItem->isErase(Item::diamond,i))
			{
				m_pItem->SetEraseNo(Item::diamond,i);
				m_diamondCount++;
			}
		}
	}
	m_pUi->Update();
	// 取得したアイテムの数を渡す。
	m_pUi->SetItemNum(Item::coin, m_coinCount);
	m_pUi->SetItemNum(Item::diamond, m_diamondCount);

	// スライドを開ける
	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}
// 描画 //
void SceneMain::Draw()
{
	m_pMap->Draw();
	m_pPlayer->Draw();
	m_pFieldOne->Draw();
	m_pField->Draw();
	m_pItem->Draw();
	m_pUi->Draw();

	SceneBase::DrawSliderDoor();
}

void SceneMain::FieldCheckHit()
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
