#pragma once
#include <DxLib.h>
#include "Util/Vec3.h"

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

	// プレイヤーの位置を取得する
	Vec3 GetPos() const { return m_pos; }

	// サイズ
//	RECT GetPos() { return m_size; }
	// 攻撃を受けた場合
	void SetDamage(int damage);
	// プレイヤーの位置を取得
//	void SetPosPlayer(RECT playerPos) { m_posPlayer = playerPos; }
protected:
	int m_hp = 100;// 体力

	int m_saveDamage = 0;

	VECTOR m_angle;// 角度

	Vec3 m_pos = {0.0f,0.0f ,0.0f };// 位置

//	RECT m_size = { 0.0f,0.0f ,0.0f ,0.0f};// キャラクターサイズ

//	RECT m_posPlayer = { 0.0f,0.0f ,0.0f ,0.0f};// プレイヤーのサイズを取得

	bool m_isStep = false;

	bool m_isDead = false;// 死んでいるかどうか
};

