#pragma once
#include <DxLib.h>

class EnemyBase
{
public:
	EnemyBase() {}
	virtual ~EnemyBase(){}

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	// 攻撃力
	int GetAttackDamage() { return 30; }
	// サイズ
	RECT GetPos() { return m_size; }
	// 攻撃を受けた場合
	void SetDamage(bool damage);
	// プレイヤーの位置を取得
	void SetPosPlayer(RECT playerPos) { m_posPlayer = playerPos; }
protected:
	int m_hp = 100;// 体力

	int m_saveDamage = 0;

	VECTOR m_angle;// 角度

	VECTOR m_pos;// 位置

	RECT m_size;// キャラクターサイズ

	RECT m_posPlayer;// プレイヤーのサイズを取得

	bool m_isStep;

	bool m_isDead = false;// 死んでいるかどうか
};

