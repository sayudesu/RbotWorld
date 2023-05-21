#pragma once
#include <DxLib.h>
#include <memory>

class SceneTest;
class Animation;

namespace
{
	// ファイル名
	const char* const kFileName = "Data/Model/Player/Robot.mv1";
	//  const char* const kFileName = "Data/Model/Player/Robot2.mv1";
	//	const char* const kFileName = "Data/Model/Player/RobotScond.mv1";

		// カメラの初期位置
	constexpr VECTOR kCameraPos{ 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f };

	// プレイヤーの移動量
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -30.0f };
	// ショットの速度
	constexpr float kShotSpeed = 10.0f;
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
	constexpr float kColRaidus = 100.0f;

	// HP
	constexpr int kMaxHp = 100;

}

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	// プレイヤーの位置を取得する
	VECTOR GetPos() const { return m_pos; }

	int GetSlowWorld() { return static_cast<int>(m_slowSpeed); }// スローの加減を渡す

	// 当たり判定の半径
	float GetColRadius();

	// 前のフレーム
	VECTOR GetLastPos()const { return m_lastPos; }
	// 半径の取得
	float GetRadius()const { return kColRaidus; }

	// ダメージを受けた
	void OnDamage(int damage);

	void UpdateControl();// 操作処理
private:

	// カメラの更新
	void UpdateCamera();

	// 動き全体の更新用関数
	void UpdateRun();
	// ジャンプする用関数
	void UpdateJump();
	// 移動用関数
	void UpdateMove();

private:
	// 
	SceneTest* m_pScene;

	// メンバ関数ポインタ
	void (Player::*m_updateFunc)();

	// プレイヤーのモデル
	std::shared_ptr<Animation> m_pModel;
	
	bool m_isJumping;

	// 再生しているアニメーション番号
	int m_animNo;

	// フレームカウント
	int m_frameCount;

	// プレイヤーの位置
	VECTOR m_pos;
	// 1フレーム前の位置
	VECTOR m_lastPos;

	// ジャンプ処理用加速度
	float m_jumpAcc;

	// ジャンプをしているかどうか(true ジャンプできない	:	false ジャンプできる )
	bool m_isFastJumping;
	bool m_isSecondJumping;

	// プレイヤーの向いている方向
	float m_angle;

	// カメラの向いている方向
	float m_cameraAngle;

	float m_slowSpeed;// スロー処理

	// HP
	int m_hp;
	// 無敵時間
	int m_damageFrame;
};

