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
	// �U����
	int GetAttackDamage() { return m_hitDamage; }

	// �v���C���[�̈ʒu���擾����
	Vec3 GetPos() const { return m_pos; }

protected:
	Vec3 m_pos = {0.0f,0.0f ,0.0f };// �ʒu

	VECTOR m_angle;// �p�x

	int m_hitDamage = 0;//�^����_���[�W
};

