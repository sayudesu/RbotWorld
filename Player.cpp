#include "Player.h"
#include<cassert>
#include <Pad.h>
#include "Animation.h"
#include "Util/DrawFunctions.h"

#include <list>

#include <algorithm>
#include <iostream>
#include <string>

#include <memory>//「スマートポインタ」を使うためのinclude
#include <array>//配列用
#include <list>

namespace
{
	const char* const kModelName = "Data/Model/Player/Robot.mv1";

	// カメラの初期位置
	constexpr VECTOR kCameraPos   { 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f     };

	// 移動速度
	constexpr float kWalkSpeed = 15.0f;
	constexpr float kRunSpeed  = 30.0f;

	// 最大HP
	constexpr int kMaxHp = 100;

	// 重力
	constexpr float kGravity = -1.5f;
	// ジャンプ力
	constexpr float kJumpPower = 30.0f;

	//無敵時間
	constexpr int kInvincibleTime = 30;

	// アニメーションナンバー
	constexpr int kAnimNoDead    = 1;	// 死んだ
	constexpr int kAnimNoIdle    = 2;	// 待機
	constexpr int kAnimNoWalk    = 10;	// 歩く
	constexpr int kAnimNoRun     = 6;	// 走る
	constexpr int kAnimNoAttack  = 5;	// 攻撃
	constexpr int kAnimNoJump    = 3;	// ジャンプ
	constexpr int kAnimNoRunJump = 11;	// 走りジャンプ
	constexpr int kAnimNoWave    = 12;	// 手を振る
}

Player::Player():
	m_cameraAngle(0.0f),
	m_idleCountTime(0),
	m_Hp(0),
	m_jumpAcc(0.0f),
	m_animNo(kAnimNoIdle),
	m_playTime(0.0f),
	angle(-90.0f),
	m_isWalk(false),
	m_isRun(false),
	m_isAttack(false),
	m_attackPunch(0.0f),
	m_isDead(false),
	m_isJump(false),
	m_isDirection(false),
	m_pos(VGet(0,0,0)),
	m_ScereenPos(VGet(0, 0, 0))
{
	// 3Dモデルの生成
	m_pAnimation = std::make_shared<Animation>(kModelName);// モデルのハンドルを渡す
	m_pAnimation->SetAnimation(m_animNo);// モデルの動きをセット

	m_size = {};
	m_attackSize = {};

	m_Hp = kMaxHp;

	m_ultimateTimer = 1;
}

Player::~Player()
{
}

void Player::Init()
{
	m_pAnimation->Init();
}

void Player::End()
{
	m_pAnimation->End();
}

// 更新処理 //
void Player::Update()
{
	UpdateCamera();

	m_pAnimation->Update(0.0f,angle, 0.0f, m_playTime);
	m_pAnimation->SetPos(m_pos);

	// 攻撃アニメーションを止める
	if (m_pAnimation->GetAnimeTime())
	{
		m_isAttack = false;
		m_isJump   = false;
	}
	// 攻撃した場合はストップ
	if (!m_isAttack)
	{
		m_pos.x += kRunSpeed;
	}
	else// 攻撃してる場合も少し移動可能
	{
		m_pos.x += 5.0f;
	}

	// ジャンプ処理
	bool isJumping = true;
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	// 地面に着地しているかどうか
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;
		isJumping = false;
	}

	// ジャンプ
	if (!isJumping)
	{
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_jumpAcc = kJumpPower;
			m_isJump = true;
		}
	}

	// 攻撃
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_isAttack = true;
	}

	//m_isWalk = false;
	//m_isRun  = false;
	/*
	if (Pad::isPress(PAD_INPUT_LEFT))// 右に移動
	{
		if (Pad::isPress(PAD_INPUT_3))// ダッシュ
		{
			m_isRun = true;
			m_pos.x -= kRunSpeed;
		}
		else
		{
			m_isWalk = true;
			m_pos.x -= kWalkSpeed;
		}
		m_isDirection = false;// 左向き
		angle = 90.0f;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))// 左に移動
	{
		if (Pad::isPress(PAD_INPUT_3))// ダッシュ
		{
			m_isRun = true;
			m_pos.x += kRunSpeed;
		}
		else
		{
			m_isWalk = true;
			m_pos.x += kWalkSpeed;
		}
		m_isDirection = true;// 右向き
		angle = -90.0f;
	}
	*/
	MoveAnimation();// アニメーションを決める
	AttackPos();// 攻撃座標

	if (m_ultimateTimer > 1)
	{
		m_ultimateTimer--;
	}
	else
	{
		m_ultimateTimer = 1;
	}
}

// 描画 //
void Player::Draw()
{
	DrawUI();

	// 点滅
	if (m_ultimateTimer % 2 == 0)
	{
		return;
	}

	m_pAnimation->Draw();

}

bool Player::GetInvincible()
{
	if (m_ultimateTimer != 1)	return true;// 攻撃を受けていたら

	return false;// 受けていなかったら
}

void Player::SetDamge(int damage)
{
	int tempHp = m_Hp;// 一つ前の体力を保存
	if(m_Hp > 0)m_Hp -= damage;

	if (tempHp != m_Hp)// 新しく攻撃を受けたら
	{
		m_ultimateTimer = kInvincibleTime;
	}

}

// アニメーションを決める //
void Player::MoveAnimation()
{
	if (m_Hp <= 0)
	{
		m_pAnimation->SetAnimation(kAnimNoDead);// モデルの動きをセット
		m_playTime = 0.5f;
		m_isDead = true;
	}
	else if (m_isJump)// ジャンプ
	{
		m_pAnimation->SetAnimation(kAnimNoRunJump);// モデルの動きをセット
		m_idleCountTime = 0;
		m_playTime = 0.4f;
		/*
		if (m_isRun)
		{
			m_pAnimation->SetAnimation(kAnimNoRunJump);// モデルの動きをセット
			m_idleCountTime = 0;
			m_playTime = 0.3f;
		}
		else
		{
			m_pAnimation->SetAnimation(kAnimNoJump);// モデルの動きをセット
			m_idleCountTime = 0;
			m_playTime = 0.4f;
		}
		*/
	}
	else if (m_isWalk)// 移動
	{
		m_pAnimation->SetAnimation(kAnimNoWalk);// モデルの動きをセット
		m_isAttack = false;
		m_idleCountTime = 0;
		m_playTime = 0.5f;
	}
	else if (m_isAttack)// 攻撃
	{
		m_pAnimation->SetAnimation(kAnimNoAttack);// モデルの動きをセット
		m_idleCountTime = 0;
		m_playTime = 0.7f;

		m_attackPunch += 10.0f;
		if (m_attackPunch > 65.0f)
		{
			m_attackPunch = 65.0f;
		}
	}
	else if (m_idleCountTime >= 60 * 5)
	{
		m_pAnimation->SetAnimation(kAnimNoWave);// モデルの動きをセット
		angle = 0.0f;
	}
	else// 待機
	{
		m_pAnimation->SetAnimation(kAnimNoRun);// モデルの動きをセット
		m_isAttack = false;
		m_idleCountTime = 0;
		m_playTime = 0.5f;
	}
}

void Player::AttackPos()
{
	// 攻撃左右の位置
	if (m_isAttack)
	{
		if (angle == -90.0f)
		{
			m_attackSize.left = m_ScereenPos.x - 30.0f + m_attackPunch;
			m_attackSize.top = m_ScereenPos.y - 200.0f;
			m_attackSize.right = m_attackSize.left + 110.0f + m_attackPunch;
			m_attackSize.bottom = m_attackSize.top + 100.0f;
		}
		if (angle == 90.0f)
		{
			m_attackSize.left = m_ScereenPos.x - 120.0f - (m_attackPunch * 1.5f);
			m_attackSize.top = m_ScereenPos.y - 200.0f;
			m_attackSize.right = m_attackSize.left + 180.0f;// - m_attackPunch;
			m_attackSize.bottom = m_attackSize.top + 100.0f;
		}
	}
	else
	{
		m_attackSize.left = NULL;
		m_attackSize.top = NULL;
		m_attackSize.right = NULL;
		m_attackSize.bottom = NULL;

		m_attackPunch = NULL;
	}
}

void Player::UpdateCamera()
{
	// ジャンプ場合
	m_cameraAngle = (m_cameraAngle * 0.8f) + (0 * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// ジャンプ時は単純にプレイヤーに服従するのではなく
	//プレイヤーの立っていた位置を見るようにする
	VECTOR cameraTrans = m_pos;
	//cameraTrans.y = m_pos.y * 0.0f;
	//cameraTrans.y = m_pos.y * 0.2f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	// プレイヤーの回転に合わせてカメラ位置、注視点を回転させる
	// プレイヤーの回転情報と平行移動情報を合成
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	// カメラの設定
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// カメラの視野角を設定（ラジアン）
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこを見ているかを設定する
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
}

void Player::DrawUI()
{
	// ワールド座標からスクリーン座標に変換
	m_ScereenPos = ConvWorldPosToScreenPos(m_pos);
	m_size.left   = m_ScereenPos.x - 60.0f;
	m_size.top    = m_ScereenPos.y - 300.0f;
	m_size.right  = m_size.left    + 140.0f;
	m_size.bottom = m_size.top     + 300.0f;

	// IDを表示
	DrawFormatString(m_size.left, m_size.top, 0xffffff, "Player");
	//ヒットボックス
	DrawBox(m_size.left, m_size.top,
		m_size.right, m_size.bottom,
		0xff0000, false);

	// 攻撃位置
	DrawBox(m_attackSize.left, m_attackSize.top,
		m_attackSize.right, m_attackSize.bottom,
		0xff00ff, false);

	//体力を描画
	DrawBox(100 - 1, 130 - 1,
		100 + 400 + 1, 130 + 1 + 20,
		0xff0000, true);//外枠
	DrawBox(100 - 1, 130 - 1,
		100 + 400 + 1, 130 + 1 + 20,
		0xffff00, false);//外枠
	DrawBox(100, 130,
		100 + 400 * m_Hp / kMaxHp, 130 + 20,
		0x0ffff0, true);//メーター
	//長さ * HP / HPMAX
}
