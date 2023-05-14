#pragma once
#include <DxLib.h>
#include <memory>

class Animation;// アニメーション再生用
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();// 初期化
	void End();// 終了処理

	void Update();// 更新
	void Draw();// 描画

	void UpdateControl();// 操作処理

	void UpdateJumpGravity();// ジャンプ処理

	void UpdateRun();// 走ってる処理

	void UpdateHitPoint();// 体力の計算処理

	void UpdateInvincible();// 無敵時間処理

	bool GetInvincible();// 無敵時間

	int GetSlowWorld() { return static_cast<int>(m_slowSpeed); }// スローの加減を渡す

	int GetAttackDamage() const { return 100; }// 攻撃力
	bool GetDirection() { return m_isDirection; }// 攻撃力

	RECT GetPos() { return m_size; }// 位置
	RECT GetPosAttack() { return m_attackSize; }// 攻撃判定
	VECTOR GetPosWorld() { return m_pos; }

	void SetDamge(int damage);// 体力管理

private:
	void MoveAnimation();// アニメーション再生命令
	void AttackPos();// 攻撃位置を計算
	void UpdateCamera();// カメラ位置を計算
	void DrawUI();// UIを表示
private:

	float m_cameraAngle;// カメラ角度

	int m_idleCountTime;// 放置時間カウント

	float m_slowSpeed;// スロー処理

	int m_hp;// 体力

	int m_tempHp;// 保存用体力

	bool m_isDamage;// 受けたダメージ

	int m_tempDamage;

	float m_jumpAcc;// ジャンプ

	bool m_isJumping;// ジャンプできるかどうか

	float angle;// 角度

	int m_animNo;// アニメーション番号

	float m_playTime;// アニメーション再生スピード

	bool m_isWalk;// 歩いているかどうか

	bool m_isRun;// 走っているかどうか

	bool m_isAttack;// 攻撃しているかどうか

	float m_attackPunch;// 攻撃力

	bool m_isAnimStop;// アニメーションを止めるかどうか

	bool m_isDead;// 死んでいるかどうか

	bool m_isJump;// ジャンプしているかどうか

	bool m_isDirection;//向いている方向（true:左向き、false:右向き）

	int m_ultimateTimer;

	RECT m_size;// ヒットボックス

	RECT m_attackSize;// 攻撃ヒットボックス

	VECTOR m_pos;// プレイヤーの位置
	
	VECTOR m_ScereenPos;// スクリーン座標に変換

	std::shared_ptr<Animation> m_pAnimation;// アニメーション再生用

};

