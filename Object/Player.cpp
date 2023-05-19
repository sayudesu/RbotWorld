#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "Animation.h"
#include <cassert>




Player::Player():
	m_updateFunc(&Player::UpdateRun),
	m_animNo(kWalkAnimNo),
	m_frameCount(0),
	m_pos(VGet(0.0f,0.0f,0.0f)),
	m_jumpAcc(0.0f),
	m_isFastJumping(false),
	m_isSecondJumping(false),
	m_angle(0.0f),
	m_cameraAngle(m_angle),
	m_slowSpeed(0.0f),
	m_hp(kMaxHp),
	m_damageFrame(0)

{
	// 3Dモデルの生成
	m_pModel = std::make_shared<Animation>(kFileName);
	m_pModel->SetAnimation(m_animNo, true, true);

	m_slowSpeed = 1.0f;

}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{

}
void Player::Update()
{	
	(this->*m_updateFunc)();
}

void Player::Draw()
{
	//体力を描画
	DrawBox(100 - 1, 130 - 1,
		100 + 400 + 1, 130 + 1 + 20,
		0xff0000, true);//外枠
	DrawBox(100 - 1, 130 - 1,
		100 + 400 + 1, 130 + 1 + 20,
		0xffff00, false);//外枠
	DrawBox(100, 130,
		100 + 400 * m_hp / kMaxHp, 130 + 20,
		0x0ffff0, true);//メーター
	//長さ * HP / HPMAX

	if (m_damageFrame > 0)
	{
		//if (m_damageFrame % 2)return;
	}

	m_pModel->Draw();
}

float Player::GetColRadius()
{
	return kColRaidus;
}

void Player::OnDamage(int damage)
{
	if (m_damageFrame > 0) return;
	m_hp -= damage;
	m_damageFrame = 60 * 2;
}

void Player::UpdateControl()
{


	// プレイヤーと敵の動きを遅くする
	if (Pad::isPress(PAD_INPUT_2))
	{
		if (m_slowSpeed < kSlowSpeed)
		{
			m_slowSpeed += 0.5f;
		}
	}
	else
	{
		if (m_slowSpeed > 1.0f)
		{
			m_slowSpeed -= 0.5f;
		}
		else
		{
			m_slowSpeed = 1.0f;
		}
	}

	// ジャンプする
//	m_isFastJumping = false;
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isFastJumping = true;
	}
	
}

void Player::UpdateCamera()
{
	/*
	// m_cameraAngle = m_angle;
	m_cameraAngle = (m_cameraAngle * 0.8f) + (m_angle * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// ジャンプ時は単純にプレイヤーに追従するのではなく
	// プレイヤーの立っていた位置を見るようにする
	VECTOR cameraTrans = m_pos;
	// cameraTrans.y = 0.0f;
	cameraTrans.y = m_pos.y * 0.3f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	
	// プレイヤーの回転に合わせてカメラ位置、注視点を回転させる
	// プレイヤーの回転情報と平行移動情報を合成
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	// カメラの設定
	// どこまで表示するか
	// SetCameraNearFar(5.0f, 2800.0f);
	 SetCameraNearFar(5.0f, 3500.0f);
	// カメラの視野角(ラジアン)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこからどこを見ているかを設定
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
	*/
	// ジャンプ場合
//	m_cameraAngle = (m_cameraAngle * 0.8f) + (0 * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// ジャンプ時は単純にプレイヤーに服従するのではなく
	//プレイヤーの立っていた位置を見るようにする

	VECTOR cameraTrans = { m_pos.x,0.0f,m_pos.z };
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
	// カメラの視野角（60）を設定（ラジアン）
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこを見ているかを設定する
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
	//SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(300.0f, 0.0f, 300.0f));
}

void Player::UpdateRun()
{
	// アニメーションを進める
	m_pModel->Update();

	m_damageFrame--;
	if (m_damageFrame <= 0) { m_damageFrame = 0; }

	// ジャンプできるかどうか
	if (!m_isJumping)
	{
		// 1ボタンでジャンプ
		if(m_isFastJumping)
		{
			// ジャンプ力
			m_jumpAcc = kJumpPower;

			// ジャンプアニメーションに変更
			m_animNo = kJumpAnimNo;
			m_pModel->ChangeAnimation(m_animNo, false, false, 4);
			m_updateFunc = &Player::UpdateJump;
		}
	}

	if (m_animNo == kWalkAnimNo)
	{
		// 走るアニメに変更
		m_animNo = kWalkAnimNo;
		m_pModel->ChangeAnimation(m_animNo, true, false, 4);
	}

	UpdateMove();
	UpdateCamera();
}

void Player::UpdateJump()
{
	m_damageFrame--;
	if (m_damageFrame <= 0) { m_damageFrame = 0; }

	// ショットアニメ以外でこのupdateは呼ばれない
	assert(m_animNo == kJumpAnimNo);
	m_pModel->Update();

	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;

	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;

		m_isFastJumping = false;
		m_isSecondJumping = false;

		// 走るアニメに変更する
		m_animNo = kWalkAnimNo;
		m_angle = 0.0f;// X軸の角度を0に戻す
		m_pModel->ChangeAnimation(kWalkAnimNo, true, true, 4);
		// updateを待機に
		m_updateFunc = &Player::UpdateRun;
	}
	else
	{
		if (!m_isSecondJumping)
		{
			//////////////////////////////////////////////////
			// ここスローモーション中でも動ける様に工夫待ち //
			//////////////////////////////////////////////////
			
			// 二段ジャンプが有効になった場合
			if (Pad::isTrigger(PAD_INPUT_1))
			{
				m_jumpAcc = kJumpPower;

				m_isSecondJumping = true;
			}
			
		}
		else
		{
			// X軸の角度を変更する
			if (m_angle > -360.0f)m_angle -= 10.0;
		}
	}

	if (m_pModel->IsAnimEnd())
	{
	//	printfDx("終わりました。\n");
	}

	UpdateMove();
	UpdateCamera();
}

void Player::UpdateMove()
{
	// プレイヤーの進行方向
	MATRIX playerRotMtx = MGetRotY(-90 * DX_PI_F / 180.0f);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);

	//移動量
	m_pos = VAdd(m_pos, move);
	// プレイヤーの角度
	m_pModel->SetRot(VGet(
		m_angle * DX_PI_F / 180.0f,
		-90.0f * DX_PI_F / 180.0f,
		0.0f));
	// プレイヤーの位置
	m_pModel->SetPos(m_pos);

	// まっすぐ進む
	m_lastPos = m_pos;

	DrawCapsule3D(
		m_pos,
		VGet(m_pos.x, m_pos.y + kSize, m_pos.z),
		100.0f,
		8,
		0xffffff,
		0xffffff,
		true);

	//	m_lastPos.x++;
	//	printfDx("%f\n", m_lastPos.x);

}
