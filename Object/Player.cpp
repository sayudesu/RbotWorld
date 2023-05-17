#include "Player.h"
#include<cassert>
#include <Pad.h>
#include "Animation.h"
#include "Util/DrawFunctions.h"


namespace
{
	// モデルパス
	const char* const kModelName = "Data/Model/Player/Robot.mv1";

	// カメラの初期位置
	constexpr VECTOR kCameraPos   { 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f     };

	// 移動速度
	constexpr float kAcc = 0.4f;//プレイヤーの加速度
//	constexpr float kWalkSpeed = 15.0f;
	constexpr float kMaxRunSpeed  = 30.0f;
	constexpr float kMaxRunSpeedDown = 15.0f;

	// 最大HP
	constexpr int kMaxHp = 100;

	// 重力
	constexpr float kGravity = -2.0f;
	// ジャンプ力
	constexpr float kJumpPower = 50.0f;

	//無敵時間
	constexpr int kInvincibleTime = 30;
	// スロー時間
	constexpr float kSlowSpeed = 3.0f;

	// アニメーションナンバー
	constexpr int kAnimNoDead    = 1;	// 死んだ
	constexpr int kAnimNoIdle    = 2;	// 待機
	constexpr int kAnimNoWalk    = 10;	// 歩く
	constexpr int kAnimNoRun     = 6;	// 走る
	constexpr int kAnimNoAttack  = 5;	// 攻撃
	constexpr int kAnimNoJump    = 3;	// ジャンプ
	constexpr int kAnimNoRunJump = 11;	// 走りジャンプ
	constexpr int kAnimNoWave    = 12;	// 手を振る


	// デバッグ用 falseにするとプレイヤーが動き出す
	constexpr bool kIsStopMove = false;
}

Player::Player():
	m_cameraAngle(0.0f),// カメラ角度
	m_idleCountTime(0),// 放置時間カウント
	m_slowSpeed(0.0f),// スロー処理
	m_hp(0),// 体力
	m_jumpAcc(0.0f),// ジャンプ
	m_animNo(kAnimNoIdle),// アニメーション番号
	m_playTime(0.0f),// アニメーション再生スピード
	m_angle(VGet(0.0f,-90.0f,0.0f)),// 角度
	m_isWalk(false),// 歩いているかどうか
	m_isRun(false),// 走っているかどうか
	m_isAttack(false),// 攻撃しているかどうか
	m_attackPunch(0.0f),// 攻撃力
	m_isDead(kIsStopMove),// 死んでいるかどうか
	m_isAnimStop(false),// アニメーションを止めるかどうか
	m_isJump(false),// ジャンプしているかどうか
	m_isJumping(false),// ジャンプできるかどうか
	m_isSecondJumping(false),
	m_isDirection(false),//向いている方向（true:左向き、false:右向き）
	m_pos(0.0f, 0.0f, 0.0f),// プレイヤーの位置
	m_vec(0.0f, 0.0f, 0.0f),// プレイヤー移動量
	m_ScereenPos(VGet(0, 0, 0))// スクリーン座標に変換
{
	// 3Dモデルの生成
	m_pAnimation = std::make_shared<Animation>(kModelName);// モデルのハンドルを渡す
	m_pAnimation->SetAnimation(m_animNo);// モデルの動きをセット

	m_size = {};// ヒットボックス
	m_attackSize = {};// 攻撃ヒットボックス

	m_slowSpeed = 1.0f;

	m_hp = kMaxHp;// 体力
	m_tempHp = 0;// 保存用体力

	m_isDamage = false;// ダメージ受けた場合
	m_isAnimStop = true;// 死んだ場合アニメーションを止める

	m_tempDamage = 0;// 前回受けたダメージを保存する

	m_ultimateTimer = 1;// ダメージをくらった場合の無敵判定用
}

Player::~Player()
{
}

void Player::Init()
{
	m_pAnimation->Init();// アニメーション用初期化関数を実行
}

void Player::End()
{
	m_pAnimation->End();// アニメーション用終了処理を実行
}

// 更新処理 //
void Player::Update()
{
	m_pAnimation->SetPos(m_pos);// プレイヤーを位置をアニメーション関数に渡す
	UpdateCamera();// カメラ類の位置設定

	// 攻撃アニメーションを止める
	if (m_pAnimation->GetAnimeTime())
	{
		m_isAttack = false;
		m_isJump   = false;
		if (m_isDead)
		{
			m_isAnimStop = false;
		}
	}

	if (m_isAnimStop)// アニメーションが停止するまで
	{
		m_pAnimation->Update(m_angle, m_playTime);// アニメーション再生
	}


	UpdateRun();// 走ってる処理

	UpdateJumpGravity();// ジャンプ処理

	m_pos += m_vec;//移動量

	UpdateHitPoint();// 体力の計算処理
	MoveAnimation();// アニメーションを決める

	AttackPos();// 攻撃座標
	UpdateInvincible();// 無敵時間処理
}

// 描画
void Player::Draw()
{
	// UI表示
	DrawUI();

	// 点滅
	if (m_ultimateTimer % 2 == 0)return;

	// モデル表示
	m_pAnimation->Draw();

}

void Player::UpdateControl()
{
	// プレイヤーと敵の動きを遅くする
	if (Pad::isPress(PAD_INPUT_3))
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
		/*else
		{
			m_slowSpeed = 1.0f;
		}*/

	}

	// 攻撃
	/*
	if (!m_isJump)
	{
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_isAttack = true;
		}
	}
	*/

	// ジャンプ
	if (!m_isJumping)
	{
		m_angle.x = 0.0f;
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_jumpAcc = kJumpPower;
			m_isJump = true;// ジャンプしました
			m_isSecondJumping = true;// 二段ジャンプ有効になりました
		}
	}
	else
	{
		// 二段ジャンプが有効になった場合
		if (m_isSecondJumping)
		{
			if (Pad::isTrigger(PAD_INPUT_1))
			{
				m_jumpAcc = kJumpPower;
				m_angle.x += 10.0f;
				m_isSecondJumping = false;
			}
		}
		if (!m_isSecondJumping)
		{
			if (m_angle.x > -360.0f - 10)
			{
				m_angle.x -= 10.0f;
			}
			else
			{
				m_angle.x = -360.0f - 10;
			}
		}
	}
}

// ジャンプ処理 //
void Player::UpdateJumpGravity()
{
	// ジャンプ処理
	m_isJumping = true;
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	// 地面に着地しているかどうか
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;
		m_isJumping = false;

		if (m_angle.x < 0.0f)m_angle.x++;
	}
}

// 走ってる処理 //
void Player::UpdateRun()
{
	// 死んだ場合は動かない
	if (!m_isDead)
	{
		// 攻撃した場合はストップ
		if (!m_isAttack)
		{
			m_vec.x += kAcc;

			if (!GetInvincible())
			{
				//運動量を確認しマックススピードを指定
				if (m_vec.x > kMaxRunSpeed)	m_vec.x = kMaxRunSpeed;

			}
			else
			{
				//運動量を確認しマックススピードを指定
				if (m_vec.x > kMaxRunSpeedDown)	m_vec.x = kMaxRunSpeedDown;
			}
		}
		else// 攻撃してる場合も少し移動可能
		{
			m_vec.x = m_vec.x / 2.0f;//kAcc * 10;
		}
	}
	else// 死んだら動かない
	{
		m_vec.x = 0.0f;
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
			m_isDead = true;
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

bool Player::GetInvincible()
{
	if (m_ultimateTimer != 1)	return true;// 攻撃を受けていたら

	return false;// 受けていなかったら
}

// ダメージを受けた時だけ更新 //
void Player::SetDamge(int damage)
{
	m_isDamage = true;

	m_tempDamage = damage;

	if (m_tempHp != m_hp)// 新しく攻撃を受けたら
	{
		m_ultimateTimer = kInvincibleTime;
	}

	m_tempHp = m_hp;// 一つ前の体力を保存

}

// アニメーションを決める //
void Player::MoveAnimation()
{
	if (m_isDead)
	{
		m_pAnimation->SetAnimation(kAnimNoDead);// モデルの動きをセット
		m_playTime = 0.5f;	
	}
	else if (m_isJump)// ジャンプ
	{
		m_pAnimation->SetAnimation(kAnimNoRunJump);// モデルの動きをセット
		m_idleCountTime = 0;
		m_playTime = 0.4f;
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
		m_angle.y = 0.0f;
	}
	else// 走り
	{
		m_pAnimation->SetAnimation(kAnimNoRun);// モデルの動きをセット
		m_idleCountTime = 0;
		m_playTime = 0.5f;
	}
}

void Player::AttackPos()
{

	// 修正対象 //
	
	// 攻撃左右の位置
	if (m_isAttack)
	{
		if (m_angle.y == -90.0f)
		{
			m_attackSize.left = m_ScereenPos.x - 30.0f + m_attackPunch;
			m_attackSize.top = m_ScereenPos.y - 200.0f;
			m_attackSize.right = m_attackSize.left + 110.0f + m_attackPunch;
			m_attackSize.bottom = m_attackSize.top + 100.0f;
		}
		if (m_angle.y == 90.0f)
		{
			m_attackSize.left = m_ScereenPos.x - 120.0f - (m_attackPunch * 1.5f);
			m_attackSize.top = m_ScereenPos.y - 200.0f;
			m_attackSize.right = m_attackSize.left + 180.0f;// - m_attackPunch;
			m_attackSize.bottom = m_attackSize.top + 100.0f;
		}

	}
	else
	{
		m_attackSize.left = 0;
		m_attackSize.top = 0;
		m_attackSize.right = 0;
		m_attackSize.bottom = 0;

		m_attackPunch = 0;
	}
}

void Player::UpdateCamera()
{
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

void Player::DrawUI()
{
	// ワールド座標からスクリーン座標に変換
	m_ScereenPos = ConvWorldPosToScreenPos({ m_pos.x,m_pos.y,m_pos.z });
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
		100 + 400 * m_hp / kMaxHp, 130 + 20,
		0x0ffff0, true);//メーター
	//長さ * HP / HPMAX

#if _DEBUG	
	// 距離を描画
	DrawFormatString(100, 100, 0xffffff, "%f", m_pos.x);
	if (m_pos.x > 30000)
	{
		DrawString(1000, 1000, "30000達成！",0xffffff);
	}
#endif
}
