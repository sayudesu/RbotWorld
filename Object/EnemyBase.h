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
	int GetAttackDamage() { return m_hitDamage; }

	// プレイヤーの位置を取得する
	Vec3 GetPos() const { return m_pos; }

protected:
	Vec3 m_pos = {0.0f,0.0f ,0.0f };// 位置

	VECTOR m_angle;// 角度

	int m_hitDamage = 0;//与えるダメージ
};

