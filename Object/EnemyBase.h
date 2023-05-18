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
	int GetAttackDamage() { return 30; }

	// �v���C���[�̈ʒu���擾����
	Vec3 GetPos() const { return m_pos; }

	// �T�C�Y
//	RECT GetPos() { return m_size; }
	// �U�����󂯂��ꍇ
	void SetDamage(int damage);
	// �v���C���[�̈ʒu���擾
//	void SetPosPlayer(RECT playerPos) { m_posPlayer = playerPos; }
protected:
	int m_hp = 100;// �̗�

	int m_saveDamage = 0;

	VECTOR m_angle;// �p�x

	Vec3 m_pos = {0.0f,0.0f ,0.0f };// �ʒu

//	RECT m_size = { 0.0f,0.0f ,0.0f ,0.0f};// �L�����N�^�[�T�C�Y

//	RECT m_posPlayer = { 0.0f,0.0f ,0.0f ,0.0f};// �v���C���[�̃T�C�Y���擾

	bool m_isStep = false;

	bool m_isDead = false;// ����ł��邩�ǂ���
};

