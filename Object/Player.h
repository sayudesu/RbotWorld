#pragma once
#include <DxLib.h>
#include <memory>

class SceneTest;
class Animation;
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

