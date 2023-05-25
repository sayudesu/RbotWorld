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

	void UpdateControl();// ���쏈��

	// �v���C���[�̈ʒu���擾����
	VECTOR GetPos()     const { return m_pos;     }
	// �v���C���[�̓����蔻��p�ʒu���擾����
	VECTOR GetPosColl() const { return m_posColl; }
	VECTOR GetSize()    const { return m_size;    }

	int GetSlowWorld() { return static_cast<int>(m_slowSpeed); }// �X���[�̉�����n��

	// �n�ʂɓ������Ă��邩�ǂ������擾����
	void FieldCheckHit(bool hit) { m_isFieldHit = hit; }

	// �n�ʂ�y���W���擾����
	void FieldPosY(float posY) { m_fieldPosY = posY; }

	// �O�̃t���[��
	// �����蔻��̔��a
	float GetRadius()const;

	// �_���[�W���󂯂�
	void OnDamage(int damage);
	bool GetInvincible();// ���G����

private:
	void UpdateInvincible();// 
	void UpdateHitPoint();// �̗͊Ǘ�
private:
	// �J�����̍X�V
	void UpdateCamera();
	// �����S�̂̍X�V�p�֐�
	void UpdateRun();
	// �W�����v����p�֐�
	void UpdateJump();
	// �ړ��p�֐�
	void UpdateMove();
	// �p�x�Ǘ��p�֐�
	void UpdateRot();
	// �d�͌n�Ǘ��p�֐�
	void UpdateGravity();
	// �n�ʂɓ��������ꍇ�̏���
	void UpdateHitField();
private:
	// 
	SceneTest* m_pScene;

	// �����o�֐��|�C���^
	void (Player::*m_updateFunc)();

	// �v���C���[�̃��f��
	std::shared_ptr<Animation> m_pModel;
	
	// �W�����v�ł��邩�ǂ���
	// (true : �W�����v�ł���, false : �W�����v�ł��Ȃ�)
	bool m_isJumping;

	// �Đ����Ă���A�j���[�V�����ԍ�
	int m_animNo;

	// �t���[���J�E���g
	int m_frameCount;

	// �v���C���[�̈ʒu
	VECTOR m_pos;
	// �����蔻��p�ʒu
	VECTOR m_posColl;
	VECTOR m_size;

	// �W�����v�����p�����x
	float m_jumpAcc;

	// �W�����v�����Ă��邩�ǂ���
	// (true �W�����v�ł��Ȃ� : false �W�����v�ł��� )
	bool m_isFastJumping;
	bool m_isSecondJumping;

	// �n�ʂɓ������Ă��邩�ǂ���
	// (true : �������Ă���, false : �������Ă��Ȃ�)
	bool m_isFieldHit = false;
	// �n�ʔ���p��Y���W�擾�p
	float m_fieldPosY;

	// �v���C���[�̌����Ă������
	float m_angle;

	// �J�����̌����Ă������
	float m_cameraAngle;

	// �X���[����
	float m_slowSpeed;

	// HP
	int m_hp;
	// ���G����
	int m_damageFrame;

	//float rad = 0.0f;
	//float radcounter = 0.0f;

	bool m_isDamage = false;// �_���[�W���󂯂����ǂ���
	int m_tempDamage = 0;// �O��󂯂��_���[�W��ۑ�����
	int m_tempHp = 0;// �ۑ��p�̗�
	int m_ultimateTimer = 1;// �_���[�W����������ꍇ�̖��G����p

	// ��]�p�x���X�V
	float m_rad = 0.0f;

	VECTOR startPos = { 0.0f,0.0f ,0.0f };
	VECTOR endPos   = { 0.0f,0.0f ,0.0f };

	int m_tempScreenH = 0;
	int handle = 0;
};

