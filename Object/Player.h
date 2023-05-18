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

	// �v���C���[�̈ʒu���擾����
	VECTOR GetPos() const { return m_pos; }

	int GetSlowWorld() { return static_cast<int>(m_slowSpeed); }// �X���[�̉�����n��

	// �����蔻��̔��a
	float GetColRadius();

	// �_���[�W���󂯂�
	void OnDamage(int damage);

	void UpdateControl();// ���쏈��
private:

	// �J�����̍X�V
	void UpdateCamera();

	// �����S�̂̍X�V�p�֐�
	void UpdateRun();
	// �W�����v����p�֐�
	void UpdateJump();
	// �ړ��p�֐�
	void UpdateMove();

private:
	// 
	SceneTest* m_pScene;

	// �����o�֐��|�C���^
	void (Player::*m_updateFunc)();

	// �v���C���[�̃��f��
	std::shared_ptr<Animation> m_pModel;
	
	bool m_isJumping;

	// �Đ����Ă���A�j���[�V�����ԍ�
	int m_animNo;

	// �t���[���J�E���g
	int m_frameCount;

	// �v���C���[�̈ʒu
	VECTOR m_pos;
	// �W�����v�����p�����x
	float m_jumpAcc;

	// �W�����v�����Ă��邩�ǂ���(true �W�����v�ł��Ȃ�	:	false �W�����v�ł��� )
	bool m_isFastJumping;
	bool m_isSecondJumping;

	// �v���C���[�̌����Ă������
	float m_angle;

	// �J�����̌����Ă������
	float m_cameraAngle;

	float m_slowSpeed;// �X���[����

	// HP
	int m_hp;
	// ���G����
	int m_damageFrame;
};

