#pragma once
#include <DxLib.h>
#include <memory>

class Animation;// �A�j���[�V�����Đ��p
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();// ������
	void End();// �I������

	void Update();// �X�V
	void Draw();// �`��

	void UpdateControl();// ���쏈��

	void UpdateJumpGravity();// �W�����v����

	void UpdateRun();// �����Ă鏈��

	void UpdateHitPoint();// �̗͂̌v�Z����

	void UpdateInvincible();// ���G���ԏ���

	bool GetInvincible();// ���G����

	int GetSlowWorld() { return static_cast<int>(m_slowSpeed); }// �X���[�̉�����n��

	int GetAttackDamage() const { return 100; }// �U����
	bool GetDirection() { return m_isDirection; }// �U����

	RECT GetPos() { return m_size; }// �ʒu
	RECT GetPosAttack() { return m_attackSize; }// �U������
	VECTOR GetPosWorld() { return m_pos; }

	void SetDamge(int damage);// �̗͊Ǘ�

private:
	void MoveAnimation();// �A�j���[�V�����Đ�����
	void AttackPos();// �U���ʒu���v�Z
	void UpdateCamera();// �J�����ʒu���v�Z
	void DrawUI();// UI��\��
private:

	float m_cameraAngle;// �J�����p�x

	int m_idleCountTime;// ���u���ԃJ�E���g

	float m_slowSpeed;// �X���[����

	int m_hp;// �̗�

	int m_tempHp;// �ۑ��p�̗�

	bool m_isDamage;// �󂯂��_���[�W

	int m_tempDamage;

	float m_jumpAcc;// �W�����v

	bool m_isJumping;// �W�����v�ł��邩�ǂ���

	float angle;// �p�x

	int m_animNo;// �A�j���[�V�����ԍ�

	float m_playTime;// �A�j���[�V�����Đ��X�s�[�h

	bool m_isWalk;// �����Ă��邩�ǂ���

	bool m_isRun;// �����Ă��邩�ǂ���

	bool m_isAttack;// �U�����Ă��邩�ǂ���

	float m_attackPunch;// �U����

	bool m_isAnimStop;// �A�j���[�V�������~�߂邩�ǂ���

	bool m_isDead;// ����ł��邩�ǂ���

	bool m_isJump;// �W�����v���Ă��邩�ǂ���

	bool m_isDirection;//�����Ă�������itrue:�������Afalse:�E�����j

	int m_ultimateTimer;

	RECT m_size;// �q�b�g�{�b�N�X

	RECT m_attackSize;// �U���q�b�g�{�b�N�X

	VECTOR m_pos;// �v���C���[�̈ʒu
	
	VECTOR m_ScereenPos;// �X�N���[�����W�ɕϊ�

	std::shared_ptr<Animation> m_pAnimation;// �A�j���[�V�����Đ��p

};

