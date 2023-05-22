#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "Animation.h"
#include <cassert>

namespace
{
	// ファイル名
	const char* const kFileName = "Data/Model/Player/Robot.mv1";

		// カメラの初期位置
	constexpr VECTOR kCameraPos{ 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f };

	// プレイヤーの移動量
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -30.0f };

	// ジャンプ力
	constexpr float kJumpPower = 50.0f;
	// 重力
	constexpr float kGravity = -2.0f;
	// スロー時間
	constexpr float kSlowSpeed = 3.0f;
	// アニメーション番号
	constexpr int kIdleAnimNo = 2;	// 待機モーション
	constexpr int kWalkAnimNo = 6;	// 移動モーション // 6
	constexpr int kJumpAnimNo = 11;	// 移動モーション // 11
	constexpr int kWaveAnimNo = 12;	// 手を振る
	constexpr int kIdleShootAnimNo = 11;	// 停止している状態でショットを撃つアニメーション

	// アニメーション切り替わりにかかるフレーム数
	constexpr int kAnimChangeFrame = 4;

	// 当たり判定サイズ半径
	constexpr float kColRaidus = 200.0f;

	// HP
	constexpr int kMaxHp = 100;

}

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

	// 点滅
	if (m_ultimateTimer % 2 == 0)return;

	m_pModel->Draw();
}

float Player::GetColRadius()
{
	return kColRaidus;
}

float Player::GetRadius() const
{
	return kColRaidus;
}

void Player::OnDamage(int damage)
{
	m_isDamage = true;

	m_tempDamage = damage;

	if (m_tempHp != m_hp)// 新しく攻撃を受けたら
	{
		m_ultimateTimer = 30;//kInvincibleTime;
	}

	m_tempHp = m_hp;// 一つ前の体力を保存
}

bool Player::GetInvincible()
{
	if (m_ultimateTimer != 1)	return true;// 攻撃を受けていたら

	return false;// 受けていなかったら
}

void Player::UpdateInvincible()
{
	// 点滅処理
	if (m_ultimateTimer > 0 + 1)
	{
		m_ultimateTimer--;
	}
	else
	{
		m_ultimateTimer = 1;
	}
}

void Player::UpdateHitPoint()
{
	// HPバー体力 - ダメージ分を徐々に減らす
	if (m_isDamage)
	{
		// HPUIの枠を超えない様に + 1
		if (m_hp < 0 + 1)
		{
			// HPを0に設定
			m_hp = 0;
			// 死んだ
		//	m_isDead = true;
		}
		else if (m_hp > m_tempHp - m_tempDamage)
		{
			// 減らす
			m_hp--;
		}
		else
		{
			// 減らし終わったら合図
			m_isDamage = false;
		}
	}
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
	// ジャンプ場合
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// ジャンプ時は単純にプレイヤーに服従するのではなく
	//プレイヤーの立っていた位置を見るようにする

	VECTOR cameraTrans = { m_pos.x,0.0f,m_pos.z };

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
	//	m_pModel->ChangeAnimation(kWalkAnimNo, true, true, 4);
	}

	UpdateMove();
	UpdateCamera();
}

void Player::UpdateMove()
{
	UpdateHitPoint();// 体力の計算処理
	UpdateInvincible();// 無敵時間処理
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
		m_lastPos,
		VGet(m_lastPos.x, m_lastPos.y + kColRaidus, m_lastPos.z),
		100.0f,
		8,
		0xffffff,
		0xffffff,
		true);

	//radcounter++;

	//rad = radcounter / 180 * DX_PI;

	//m_lastPos.x = cos(rad);	
	//m_lastPos.y = sin(rad);
	//

	//	m_lastPos.x++;
	//	printfDx("%f\n", m_lastPos.x);

}
