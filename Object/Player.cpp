#include "Player.h"
#include <DxLib.h>
#include "../Util/Pad.h"
#include "../Util/Model.h"
#include "../Util/game.h"
#include <cassert>
#include "../Util/GraphAnimation.h"
#include "../Util/Sound.h"
#include <cmath>

namespace
{
	// ファイル名
	const char* const kFileName = "Data/Model/Player/RobotT.mv1";

	// カメラの初期位置
	constexpr VECTOR kCameraPos{ 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f };
	// ゴールした場合のカメラ
	constexpr VECTOR kPlayerRotaGoal{ 0.0f,90.0f * DX_PI_F * 180.0f ,0.0f };
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
	constexpr float kColRaidus = 50.0f;

	// HP
	constexpr int kMaxHp = 100;

}

Player::Player():
	m_hJump(-1),
	m_hGoal(-1),
	m_goalX(0),
	m_goalY(-Game::kScreenHeight),
	m_updateFunc(&Player::UpdateRun),
	m_isJumping(false),
	m_animNo(kWalkAnimNo),
	m_frameCount(0),
	m_pos(VGet(0.0f,300.0f,0.0f)),
	m_posColl(VGet(0.0f, 100.0f, 0.0f)),
	m_size(VGet(0.0f, 100.0f, 0.0f)),
	m_jumpAcc(0.0f),
	m_isFastJumping(false),
	m_isSecondJumping(false),
	m_angle(0.0f),
	m_cameraAngle(m_angle),
	m_slowSpeed(0.0f),
	m_isDead(false),// 死んでいるかどうか
	m_hp(kMaxHp),
	m_damageFrame(0),
	m_isClear(false),
	m_isClearSceneChange(false),
	m_goalCameraPos(200.0f),
	m_count(0)

{
	// 3Dモデルの生成
	m_pModel = std::make_shared<Model>(kFileName);
	m_pModel->SetAnimation(m_animNo, true, true);

	// スロースピード設定(1は標準スピード)
	m_slowSpeed = 1.0f;

	// 回転角度
	m_rad = 90.0f * DX_PI_F / 180.0f;

	m_pGraphAnimation = new GraphAnimation;

	// 動けます
	m_isMove = true;
}

Player::~Player()
{
}

void Player::Init()
{
	// ジャンプエフェクト用画像をロード
	m_hJump = DxLib::LoadGraph("Data/Img/jumpEffect.png");
	m_hGoal = DxLib::LoadGraph("Data/Img/Goal.png");
}

void Player::End()
{
	// ハンドルを削除
	DxLib::DeleteGraph(m_hJump);
	DxLib::DeleteGraph(m_hGoal);

	delete m_pGraphAnimation;
}

void Player::Update()
{	
	(this->*m_updateFunc)();
}

void Player::Draw()
{	
	// ジャンプのエフェクトを表示
	if (m_isJumpImg)
	{
		int imgX = 140;
		int imgY = 50;
		int size = 5;
		float rota = DX_PI / 180.0f;

		DrawRectRotaGraph
		(
			screenPos.x, screenPos.y - 100.0f,// 画像位置
			m_jumpImgX, 0,					  // 画像の左上
			imgX, imgY,						  // 画像の右下
			size,							  // サイズ
			rota,							  // 角度
			m_hJump,					      // 画像ハンドル
			true							  // 透過
		);
	}


	// 点滅
	if (m_ultimateTimer % 2 != 0)
	{
		// プレイヤーモデルの描画
		m_pModel->Draw();
	}

	DrawRotaGraph(m_goalX, m_goalY,1, DX_PI_F * 180.0f, m_hGoal, true);
}

float Player::GetRadius() const
{
	return kColRaidus;
}

// 点滅処理 //
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

// ジャンプエフェクト //
void Player::JumpEffect()
{
	constexpr int imageSizeX    = 140; // 画像1枚の大きさ
	constexpr int imageNum      = 6;   // 画像描画数
	constexpr int frameCountMax = 3;   // 画像を読み込みフレーム

	// ジャンプをしているかどうか
	if (m_isFastJumping)
	{
		// ジャンプした一度だけその場の位置を取得
		// ワールド座標からスクリーン座標に変換
		if (m_isJumpPos)
		{
			pos = { m_pModel->GetModelPos().x,m_pModel->GetModelPos().y ,m_pModel->GetModelPos().z };
			screenPos = ConvWorldPosToScreenPos(pos);
			m_isJumpPos = false;
		}

		// 画像表示させる
		m_isJumpImg = true;

		// アニメーションを再生
		m_jumpImgCount++;
		
		// 画像内の位置を調整
		// 表示用カウントの初期化
		if (m_jumpImgCount == frameCountMax)
		{
			m_pGraphAnimation->Animation(m_jumpImgX, imageSizeX, imageNum);
			m_jumpImgCount = 0;
		}
	}
	else
	{
		m_jumpImgX = 0;
		m_isJumpImg = false;
	}

	// 画像が同じ位置にとどまらない様に
	screenPos.x -= 30.0f;
}

// 操作処理 //
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
	if (Pad::isTrigger(PAD_INPUT_1))// XBox : A
	{
		// 音量設定	0~255
		if (!m_isFastJumping)
		{
			Sound::play(Sound::SoundId_Jump);
			Sound::setVolume(Sound::SoundId_Jump, 100);
		}
		m_isFastJumping = true;
		m_isJumpPos = true;
	}
}

// プレイヤーを追跡するカメラの設定 //
void Player::UpdateCamera()
{
	// ジャンプ場合
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// ジャンプ時は単純にプレイヤーに服従するのではなく
	//プレイヤーの立っていた位置を見るようにする
	VECTOR cameraTrans = { m_pos.x + m_goalCameraPos,0.0f,m_pos.z };
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
	// ショットアニメ以外でこのupdateは呼ばれない
	assert(m_animNo == kWalkAnimNo);

	// モデルの更新
	m_pModel->Update();

	// ジャンプできるかどうか
	if(m_isFastJumping)
	{
		// ジャンプ力
		m_jumpAcc = kJumpPower;
		// ジャンプアニメーションに変更
		m_animNo = kJumpAnimNo;
		// アニメーションを変更する
		m_pModel->ChangeAnimation(m_animNo, false, false, 4);
		// Jump関数に移動する
		m_updateFunc = &Player::UpdateJump;
	}
	else
	{
		UpdateHitField();//地面に当たった場合の処理
	}

	// 走るアニメだったら走るアニメに変更
	if (m_animNo == kWalkAnimNo)
	{
		m_animNo = kWalkAnimNo;
		m_pModel->ChangeAnimation(m_animNo, true, false, 4);
	}

	if (m_isClear)
	{
		// ジャンプアニメーションに変更
		m_animNo = kWaveAnimNo;
		// アニメーションを変更する
		m_pModel->ChangeAnimation(m_animNo, true, true, 4);
		// ゲームクリア条件が揃うとクリア関数に移動
		m_updateFunc = &Player::Goal;
	}
	static int count = 0;
	count++;
	if (count == 20)
	{
		Sound::play(Sound::SoundId_Run);
		Sound::setVolume(Sound::SoundId_Run, 100);
		count = 0;
	}



	UpdateMove();// 移動用関数
	UpdateCamera();// カメラ用関数
	UpdateGravity();//重力系管理用関数
	UpdateInvincible();// 無敵時間処理
	UpdateRot();// 角度用関数
}

// ジャンプした場合の処理 //
void Player::UpdateJump()
{
	// ショットアニメ以外でこのupdateは呼ばれない
	assert(m_animNo == kJumpAnimNo);

	// モデルの更新
	m_pModel->Update();

	// 飛んでいない場合
	if (m_jumpAcc <= 0)
	{
		// 地面に当たったら
		if(m_isFieldHit)
		{
			// 走るアニメに変更する
			m_animNo = kWalkAnimNo;
			m_pModel->ChangeAnimation(m_animNo, true, true, 4);
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
		}
	}

	// 二段階ジャンプ時の回転処理
	if (m_isSecondJumping)
	{
		if (m_angle > -360.0f)m_angle -= 10.0f;
		if (m_rad   > -4.5f)m_rad -= 0.2f;
	}

	UpdateMove();// 移動用関数
	UpdateCamera();// カメラ用関数
	UpdateGravity();//重力系管理用関数
	UpdateHitField();//地面に当たった場合の処理
	UpdateInvincible();// 無敵時間処理
	UpdateRot();// 角度用関数
	JumpEffect();// エフェクト描画
}

void Player::Goal()
{
	// 手を振るアニメ以外でこのupdateは呼ばれない
	assert(m_animNo == kWaveAnimNo);

	

	// クリア画面に移行よう処理
	// カメラの位置を変更する
	if (m_goalCameraPos > -200.0f)
	{
		m_goalCameraPos -= 3.5f;
	}
	else
	{
		if (m_goalX < Game::kScreenWidth / 2)m_goalX += 30;
		if (m_goalY < Game::kScreenHeight / 2)m_goalY += 30;
	}

	m_count++;
	if (m_count > 60 * 5)
	{
		m_isClearSceneChange = true;
	}

	// モデルの更新
	m_pModel->Update();
	m_pModel->SetRot(kPlayerRotaGoal);

	// 手を振るアニメだったら手を振るアニメに変更
	if (m_animNo == kWaveAnimNo)
	{
		m_animNo = kWaveAnimNo;
		m_pModel->ChangeAnimation(m_animNo, true, false, 4);
	}


	// カメラ
	UpdateCamera();
}

void Player::UpdateMove()
{
	// プレイヤーの進行方向
	MATRIX playerRotMtx = MGetRotY(-90 * DX_PI_F / 180.0f);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);
	if (m_isMove)
	{
		//移動量
		m_pos = VAdd(m_pos, move);
		// プレイヤーの位置
		m_pModel->SetPos(m_pos);
	}

	// 当たり判定用サイズ
	m_posColl = { m_pos.x - 25.0f, m_pos.y + 50.0f,      m_pos.z };
	m_size = { m_posColl.x,     m_posColl.y + 300.0f, m_posColl.z };

	// カプセルの座標を計算
	m_size.x = m_posColl.x + cosf(m_rad) * 100.0f;
	m_size.y = (m_posColl.y + sinf(m_rad) * 100.0f) + 100.0f;
	m_size.z = m_posColl.z;
}

// 角度管理用関数 //
void Player::UpdateRot()
{
	// プレイヤーの角度
	m_pModel->SetRot(
		VGet(
			m_angle * DX_PI_F / 180.0f, //x
			-90.0f * DX_PI_F  / 180.0f, //y
			0.0f					    //z
			)					    
	);
}

// 地面に当たった場合の処理 //
void Player::UpdateHitField()
{
	if (m_jumpAcc <= 0)
	{
		// 地面に触れているかどうか
		// 地面に当たったら
		if (m_isFieldHit)
		{
			// 座標を地面に戻す
			m_pos.y = m_fieldPosY + 100.0f;
			// ジャンプ加速をなくす
			m_jumpAcc = 0.0f;
			// 次にまたジャンプ出来るようにする
			m_isFastJumping = false;
			m_isSecondJumping = false;

			// X軸の角度を0に戻す
			m_angle = 0.0f;
			// 当たり判定の回転角度
			m_rad = 90.0f * DX_PI_F / 180.0f;
		}
	}
}

// 重力系管理用関数 //
void Player::UpdateGravity()
{
	// 重力
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
}

