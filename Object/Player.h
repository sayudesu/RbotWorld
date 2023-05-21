#pragma once
#include <DxLib.h>
#include <memory>

class SceneTest;
class Animation;

namespace
{
	// �t�@�C����
	const char* const kFileName = "Data/Model/Player/Robot.mv1";
	//  const char* const kFileName = "Data/Model/Player/Robot2.mv1";
	//	const char* const kFileName = "Data/Model/Player/RobotScond.mv1";

		// �J�����̏����ʒu
	constexpr VECTOR kCameraPos{ 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f };

	// �v���C���[�̈ړ���
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -30.0f };
	// �V���b�g�̑��x
	constexpr float kShotSpeed = 10.0f;
	// �W�����v��
	constexpr float kJumpPower = 50.0f;
	// �d��
	constexpr float kGravity = -2.0f;
	// �X���[����
	constexpr float kSlowSpeed = 3.0f;
	// �A�j���[�V�����ԍ�
	constexpr int kIdleAnimNo = 2;	// �ҋ@���[�V����
	constexpr int kWalkAnimNo = 6;	// �ړ����[�V���� // 6
	constexpr int kJumpAnimNo = 11;	// �ړ����[�V���� // 11
	constexpr int kWaveAnimNo = 12;	// ���U��
	constexpr int kIdleShootAnimNo = 11;	// ��~���Ă����ԂŃV���b�g�����A�j���[�V����

	// �A�j���[�V�����؂�ւ��ɂ�����t���[����
	constexpr int kAnimChangeFrame = 4;

	// �����蔻��T�C�Y���a
	constexpr float kColRaidus = 100.0f;

	// HP
	constexpr int kMaxHp = 100;

}

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

	// �O�̃t���[��
	VECTOR GetLastPos()const { return m_lastPos; }
	// ���a�̎擾
	float GetRadius()const { return kColRaidus; }

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
	// 1�t���[���O�̈ʒu
	VECTOR m_lastPos;

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

