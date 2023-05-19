#include "SceneDebug.h"
#include <DxLib.h>
#include "game.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/EnemyRush.h"
#include "Object/Field.h"

#include "Util/Vec3.h"

namespace
{
	// 初期位置
	Vec3 kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneDebug::SceneDebug():
	m_slowCount(0),
	m_enemyCount(0),
	m_isInvincible(false),
	m_isEnemyDamageHit(false),
	m_pPlayer(nullptr),
	m_pField(nullptr)
{
	m_pEnemyRush.push_back(std::make_shared<EnemyRush>(kPos));

	m_pPlayer = new Player;
	m_pField = new Field;
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
}

void SceneDebug::End()
{
	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->End();
	}

	m_pPlayer->End();
	m_pField->End();

	delete m_pPlayer;
	delete m_pField;
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
			//if (enemyRush->GetPos().x < 0)
			//{
			//	enemyRush->End();
			//}
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
			m_tempRand = GetRand(4);
		}
	}

	// 当たり判定の情報
	// 敵との判定
	//for (auto& enemy : m_pEnemyRush)
	//{
	//	// DxLibの関数を利用して当たり判定をとる
	//	MV1_COLL_RESULT_POLY_DIM result;		//あたりデータ

	//	result = MV1CollCheck_Capsule(
	//		enemy->GetModelHandle(),
	//		enemy->GetColFrameIndex(),
	//		m_pPlayer->GetPos(),
	//		m_pPlayer->GetLastPos(),
	//		m_pPlayer->GetRadius());
	//	if (result.HitNum > 0)	//1舞以上のポリゴンと当たっていたらモデルにあっている設定
	//	{
	//		printfDx("Hit %d\n", result.HitNum);
	//		//enemy->OnDamage(50);
	//	}

	//	// 当たり判定情報の後始末
	//	MV1CollResultPolyDimTerminate(result);
	//}
	// 地面との判定


	// DxLibの関数を利用して当たり判定をとる
	MV1_COLL_RESULT_POLY_DIM result;		//あたりデータ

	result = MV1CollCheck_Capsule(
		m_pField->GetModelHandle(),
		m_pField->GetColFrameIndex(),
		m_pPlayer->GetPos(),
		m_pPlayer->GetLastPos(),
		m_pPlayer->GetRadius());
	if (result.HitNum > 0)	//1舞以上のポリゴンと当たっていたらモデルにあっている設定
	{
		printfDx("地面判定\n");
		//enemy->OnDamage(50);
	}

	// 当たり判定情報の後始末
	MV1CollResultPolyDimTerminate(result);


	// プレイヤーの操作
	//	m_pPlayer->UpdateControl();

	// 無敵時間外に敵に当たっているかの判定
	//if (!m_isInvincible)
	//{
	//	for (auto & enemyRush : m_pEnemyRush)
	//	{
	//		//damege(
	//		//	m_pPlayer->GetPos().left,//プレイヤーの座標
	//		//	m_pPlayer->GetPos().top,
	//		//	m_pPlayer->GetPos().right,
	//		//	m_pPlayer->GetPos().bottom,
	//		//	enemyRush->GetPos().left,// 敵の座標
	//		//	enemyRush->GetPos().top,
	//		//	enemyRush->GetPos().right,
	//		//	enemyRush->GetPos().bottom,
	//		//	true,// ダメージを受ける側(プレイヤー : true敵: false）
	//		//	enemyRush->GetAttackDamage()
	//		//);	

	//		//damege(
	//		//	m_pPlayer->GetPosAttack().left,//プレイヤーの座標
	//		//	m_pPlayer->GetPosAttack().top,
	//		//	m_pPlayer->GetPosAttack().right,
	//		//	m_pPlayer->GetPosAttack().bottom,
	//		//	enemyRush->GetPos().left,// 敵の座標
	//		//	enemyRush->GetPos().top,
	//		//	enemyRush->GetPos().right,
	//		//	enemyRush->GetPos().bottom,
	//		//	false,// ダメージを受ける側(プレイヤー : true敵: false）
	//		//	enemyRush->GetAttackDamage()
	//		//);

	//		//if (m_isEnemyDamageHit)
	//		//{
	//		//	enemyRush->SetDamage(m_pPlayer->GetAttackDamage());
	//		//	m_isEnemyDamageHit = false;
	//		//}
	// }

	//}
	// 無敵時間の調整
	//if (!m_pPlayer->GetInvincible()) m_isInvincible = false;

	// フェイド処理
	UpdateFade();

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

// 敵との衝突判定 //
bool SceneDebug::damege(
	int left, int top, int right, int bottom,
	int left1,int top1,int right1,int bottom1,
	bool playerOrEnemy ,int damage)
{

	// プレイヤーとエネミーの衝突
	//if (left > right1) return true;;
	//	
	//if (right < left1) return true;;
	//	
	//if (top > bottom1) return true;;
	//	
	//if (bottom <top1) return true;;

	//if (playerOrEnemy)
	//{
	//	// ダメージ量を渡す
	//	m_pPlayer->SetDamge(damage);
	//	// 振動開始
	//	StartJoypadVibration(DX_INPUT_PAD1, 1000, 60, -1);
	//	StartJoypadVibration(DX_INPUT_PAD1, 1000, 60, 1);
	//	// ダメージをくらった
	//	m_isInvincible = true;
	//}
	//else
	//{
	//	m_isEnemyDamageHit = true;
	//}

	return false;
}

