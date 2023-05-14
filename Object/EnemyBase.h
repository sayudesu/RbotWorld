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
	// �U����
	int GetAttackDamage() { return 30; }
	// �T�C�Y
	RECT GetPos() { return m_size; }
	// �U�����󂯂��ꍇ
	void SetDamage(bool damage);
	// �v���C���[�̈ʒu���擾
	void SetPosPlayer(RECT playerPos) { m_posPlayer = playerPos; }
protected:
	int m_hp = 100;// �̗�

	int m_saveDamage = 0;

	VECTOR m_angle;// �p�x

	VECTOR m_pos;// �ʒu

	RECT m_size;// �L�����N�^�[�T�C�Y

	RECT m_posPlayer;// �v���C���[�̃T�C�Y���擾

	bool m_isStep;

	bool m_isDead = false;// ����ł��邩�ǂ���
};

