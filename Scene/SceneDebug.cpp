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

	// スローモーション処理
	m_slowCount = (m_slowCount += 1) % m_pPlayer->GetSlowWorld();
	if (m_slowCount == 0)
	{
		// プレイヤーの更新
		m_pPlayer->Update();
		for (auto& enemyRush : m_pEnemyRush)
		{
			enemyRush->Update();

			// 敵が画面座標から出たら削除
			if (enemyRush->GetPos().left < 0)
			{
				enemyRush->End();
			}
		}

		if (m_enemyCount == 0)
		{
			m_tempRand = GetRand(2);
		//	printfDx("aaaaaaaaaaaaa");
			switch (m_tempRand)
			{
			case 0:
				m_tempRand = 1;
			case 1:
				m_tempRand = 2;
			case 2:
				m_tempRand = 3;
			case 3:
				m_tempRand = 4;
			case 4:
				m_tempRand = 5;
			default:
				m_tempRand = 1;
				break;
			}
		}
		// 敵を生成(まだ完全なエネミー削除処理なし)
		m_enemyCount++;
		if (m_enemyCount > 60 * m_tempRand)
		{
			m_enemyCount = 0;
			Vec3 pos = { m_pPlayer->GetPosWorld().x,0.0f,0.0f };
			pos.x += 3000;
			m_pEnemyRush.push_back(std::make_shared<EnemyRush>(pos));
		}
	}

	// プレイヤーの操作
	m_pPlayer->UpdateControl();

	// 無敵時間外に敵に当たっているかの判定
	if (!m_isInvincible)
	{
		for (auto & enemyRush : m_pEnemyRush)
		{
			damege(
				m_pPlayer->GetPos().left,//プレイヤーの座標
				m_pPlayer->GetPos().top,
				m_pPlayer->GetPos().right,
				m_pPlayer->GetPos().bottom,
				enemyRush->GetPos().left,// 敵の座標
				enemyRush->GetPos().top,
				enemyRush->GetPos().right,
				enemyRush->GetPos().bottom,
				true,// ダメージを受ける側(プレイヤー : true敵: false）
				enemyRush->GetAttackDamage()
			);	

			//damege(
			//	m_pPlayer->GetPosAttack().left,//プレイヤーの座標
			//	m_pPlayer->GetPosAttack().top,
			//	m_pPlayer->GetPosAttack().right,
			//	m_pPlayer->GetPosAttack().bottom,
			//	enemyRush->GetPos().left,// 敵の座標
			//	enemyRush->GetPos().top,
			//	enemyRush->GetPos().right,
			//	enemyRush->GetPos().bottom,
			//	false,// ダメージを受ける側(プレイヤー : true敵: false）
			//	enemyRush->GetAttackDamage()
			//);

			//if (m_isEnemyDamageHit)
			//{
			//	enemyRush->SetDamage(m_pPlayer->GetAttackDamage());
			//	m_isEnemyDamageHit = false;
			//}
		}

	}
	// 無敵時間の調整
	if (!m_pPlayer->GetInvincible()) m_isInvincible = false;

	// フェイド処理
	UpdateFade();

	return this;
}
// 描画 //
void SceneDebug::Draw()
{
	// 3D空間に2D画像読み込ませる
#if false	

	// 画像の読み込み
	int GrHandle = LoadGraph("Title.png");

	VECTOR pos = { m_pPlayer->GetPosWorld().x,m_pPlayer->GetPosWorld().y,m_pPlayer->GetPosWorld().z };
	pos.z += 200.0f;
	// ３Ｄ空間上に画像を描画
	DrawBillboard3D(pos, 0.5f, 0.5f, 120.0f * 30, 0.0f, GrHandle, true);

//	pos = { 0.0f,0.0f,pos.z };
//	DrawExtendGraph3D(pos.x, pos.y, pos.z, Game::kScreenWidth, Game::kScreenHeight, GrHandle, true);

	//DrawGraph3D(pos.x, pos.y, pos.z, GrHandle,true);

	DeleteGraph(GrHandle);

#endif	
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
	if (left > right1) return true;;
		
	if (right < left1) return true;;
		
	if (top > bottom1) return true;;
		
	if (bottom <top1) return true;;

	if (playerOrEnemy)
	{
		// ダメージ量を渡す
		m_pPlayer->SetDamge(damage);
		// 振動開始
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 60, -1);
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 60, 1);
		// ダメージをくらった
		m_isInvincible = true;
	}
	else
	{
		m_isEnemyDamageHit = true;
	}

	return false;
}

