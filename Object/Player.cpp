#include "Player.h"
#include <DxLib.h>
#include "../Util/Pad.h"
#include "../Util/Model.h"
#include "../Util/game.h"
#include <cassert>
#include "../Util/GraphAnimation.h"
#include "../Util/Sound.h"
#include <cmath>

namespace
{
	// �t�@�C����
	const char* const kFileName = "Data/Model/Player/RobotT.mv1";

	// �J�����̏����ʒu
	constexpr VECTOR kCameraPos{ 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f };
	// �S�[�������ꍇ�̃J����
	constexpr VECTOR kPlayerRotaGoal{ 0.0f,90.0f * DX_PI_F * 180.0f ,0.0f };
	// �v���C���[�̈ړ���
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -30.0f };

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
	constexpr float kColRaidus = 50.0f;

	// HP
	constexpr int kMaxHp = 100;

}

Player::Player():
	m_hJump(-1),
	m_hGoal(-1),
	m_goalX(0),
	m_goalY(-Game::kScreenHeight),
	m_updateFunc(&Player::UpdateRun),
	m_isJumping(false),
	m_animNo(kWalkAnimNo),
	m_frameCount(0),
	m_pos(VGet(0.0f,300.0f,0.0f)),
	m_posColl(VGet(0.0f, 100.0f, 0.0f)),
	m_size(VGet(0.0f, 100.0f, 0.0f)),
	m_jumpAcc(0.0f),
	m_isFastJumping(false),
	m_isSecondJumping(false),
	m_angle(0.0f),
	m_cameraAngle(m_angle),
	m_slowSpeed(0.0f),
	m_isDead(false),// ����ł��邩�ǂ���
	m_hp(kMaxHp),
	m_damageFrame(0),
	m_isClear(false),
	m_isClearSceneChange(false),
	m_goalCameraPos(200.0f),
	m_count(0)

{
	// 3D���f���̐���
	m_pModel = std::make_shared<Model>(kFileName);
	m_pModel->SetAnimation(m_animNo, true, true);

	// �X���[�X�s�[�h�ݒ�(1�͕W���X�s�[�h)
	m_slowSpeed = 1.0f;

	// ��]�p�x
	m_rad = 90.0f * DX_PI_F / 180.0f;

	m_pGraphAnimation = new GraphAnimation;

	// �����܂�
	m_isMove = true;
}

Player::~Player()
{
}

void Player::Init()
{
	// �W�����v�G�t�F�N�g�p�摜�����[�h
	m_hJump = DxLib::LoadGraph("Data/Img/jumpEffect.png");
	m_hGoal = DxLib::LoadGraph("Data/Img/Goal.png");
}

void Player::End()
{
	// �n���h�����폜
	DxLib::DeleteGraph(m_hJump);
	DxLib::DeleteGraph(m_hGoal);

	delete m_pGraphAnimation;
}

void Player::Update()
{	
	(this->*m_updateFunc)();
}

void Player::Draw()
{	
	// �W�����v�̃G�t�F�N�g��\��
	if (m_isJumpImg)
	{
		int imgX = 140;
		int imgY = 50;
		int size = 5;
		float rota = DX_PI / 180.0f;

		DrawRectRotaGraph
		(
			screenPos.x, screenPos.y - 100.0f,// �摜�ʒu
			m_jumpImgX, 0,					  // �摜�̍���
			imgX, imgY,						  // �摜�̉E��
			size,							  // �T�C�Y
			rota,							  // �p�x
			m_hJump,					      // �摜�n���h��
			true							  // ����
		);
	}


	// �_��
	if (m_ultimateTimer % 2 != 0)
	{
		// �v���C���[���f���̕`��
		m_pModel->Draw();
	}

	DrawRotaGraph(m_goalX, m_goalY,1, DX_PI_F * 180.0f, m_hGoal, true);
}

float Player::GetRadius() const
{
	return kColRaidus;
}

// �_�ŏ��� //
void Player::UpdateInvincible()
{
	// �_�ŏ���
	if (m_ultimateTimer > 0 + 1)
	{
		m_ultimateTimer--;
	}
	else
	{
		m_ultimateTimer = 1;
	}
}

// �W�����v�G�t�F�N�g //
void Player::JumpEffect()
{
	constexpr int imageSizeX    = 140; // �摜1���̑傫��
	constexpr int imageNum      = 6;   // �摜�`�搔
	constexpr int frameCountMax = 3;   // �摜��ǂݍ��݃t���[��

	// �W�����v�����Ă��邩�ǂ���
	if (m_isFastJumping)
	{
		// �W�����v������x�������̏�̈ʒu���擾
		// ���[���h���W����X�N���[�����W�ɕϊ�
		if (m_isJumpPos)
		{
			pos = { m_pModel->GetModelPos().x,m_pModel->GetModelPos().y ,m_pModel->GetModelPos().z };
			screenPos = ConvWorldPosToScreenPos(pos);
			m_isJumpPos = false;
		}

		// �摜�\��������
		m_isJumpImg = true;

		// �A�j���[�V�������Đ�
		m_jumpImgCount++;
		
		// �摜���̈ʒu�𒲐�
		// �\���p�J�E���g�̏�����
		if (m_jumpImgCount == frameCountMax)
		{
			m_pGraphAnimation->Animation(m_jumpImgX, imageSizeX, imageNum);
			m_jumpImgCount = 0;
		}
	}
	else
	{
		m_jumpImgX = 0;
		m_isJumpImg = false;
	}

	// �摜�������ʒu�ɂƂǂ܂�Ȃ��l��
	screenPos.x -= 30.0f;
}

// ���쏈�� //
void Player::UpdateControl()
{
	// �v���C���[�ƓG�̓�����x������
	if (Pad::isPress(PAD_INPUT_2))
	{
		if (m_slowSpeed < kSlowSpeed)
		{
			m_slowSpeed += 0.5f;
		}
	}
	else
	{
		if (m_slowSpeed > 1.0f)
		{
			m_slowSpeed -= 0.5f;
		}
		else
		{
			m_slowSpeed = 1.0f;
		}
	}

	// �W�����v����
	if (Pad::isTrigger(PAD_INPUT_1))// XBox : A
	{
		// ���ʐݒ�	0~255
		if (!m_isFastJumping)
		{
			Sound::play(Sound::SoundId_Jump);
			Sound::setVolume(Sound::SoundId_Jump, 100);
		}
		m_isFastJumping = true;
		m_isJumpPos = true;
	}
}

// �v���C���[��ǐՂ���J�����̐ݒ� //
void Player::UpdateCamera()
{
	// �W�����v�ꍇ
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// �W�����v���͒P���Ƀv���C���[�ɕ��]����̂ł͂Ȃ�
	//�v���C���[�̗����Ă����ʒu������悤�ɂ���
	VECTOR cameraTrans = { m_pos.x + m_goalCameraPos,0.0f,m_pos.z };
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	// �v���C���[�̉�]�ɍ��킹�ăJ�����ʒu�A�����_����]������
	// �v���C���[�̉�]���ƕ��s�ړ���������
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	// �J�����̐ݒ�
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p�i60�j��ݒ�i���W�A���j
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);

	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
}

void Player::UpdateRun()
{
	// �V���b�g�A�j���ȊO�ł���update�͌Ă΂�Ȃ�
	assert(m_animNo == kWalkAnimNo);

	// ���f���̍X�V
	m_pModel->Update();

	// �W�����v�ł��邩�ǂ���
	if(m_isFastJumping)
	{
		// �W�����v��
		m_jumpAcc = kJumpPower;
		// �W�����v�A�j���[�V�����ɕύX
		m_animNo = kJumpAnimNo;
		// �A�j���[�V������ύX����
		m_pModel->ChangeAnimation(m_animNo, false, false, 4);
		// Jump�֐��Ɉړ�����
		m_updateFunc = &Player::UpdateJump;
	}
	else
	{
		UpdateHitField();//�n�ʂɓ��������ꍇ�̏���
	}

	// ����A�j���������瑖��A�j���ɕύX
	if (m_animNo == kWalkAnimNo)
	{
		m_animNo = kWalkAnimNo;
		m_pModel->ChangeAnimation(m_animNo, true, false, 4);
	}

	if (m_isClear)
	{
		// �W�����v�A�j���[�V�����ɕύX
		m_animNo = kWaveAnimNo;
		// �A�j���[�V������ύX����
		m_pModel->ChangeAnimation(m_animNo, true, true, 4);
		// �Q�[���N���A�����������ƃN���A�֐��Ɉړ�
		m_updateFunc = &Player::Goal;
	}
	static int count = 0;
	count++;
	if (count == 20)
	{
		Sound::play(Sound::SoundId_Run);
		Sound::setVolume(Sound::SoundId_Run, 100);
		count = 0;
	}



	UpdateMove();// �ړ��p�֐�
	UpdateCamera();// �J�����p�֐�
	UpdateGravity();//�d�͌n�Ǘ��p�֐�
	UpdateInvincible();// ���G���ԏ���
	UpdateRot();// �p�x�p�֐�
}

// �W�����v�����ꍇ�̏��� //
void Player::UpdateJump()
{
	// �V���b�g�A�j���ȊO�ł���update�͌Ă΂�Ȃ�
	assert(m_animNo == kJumpAnimNo);

	// ���f���̍X�V
	m_pModel->Update();

	// ���ł��Ȃ��ꍇ
	if (m_jumpAcc <= 0)
	{
		// �n�ʂɓ���������
		if(m_isFieldHit)
		{
			// ����A�j���ɕύX����
			m_animNo = kWalkAnimNo;
			m_pModel->ChangeAnimation(m_animNo, true, true, 4);
			// update��ҋ@��
			m_updateFunc = &Player::UpdateRun;
		}
		else
		{
			if (!m_isSecondJumping)
			{
				//////////////////////////////////////////////////
				// �����X���[���[�V�������ł�������l�ɍH�v�҂� //
				//////////////////////////////////////////////////
			
				// ��i�W�����v���L���ɂȂ����ꍇ
				if (Pad::isTrigger(PAD_INPUT_1))
				{
					m_jumpAcc = kJumpPower;

					m_isSecondJumping = true;
				}			
			}
		}
	}

	// ��i�K�W�����v���̉�]����
	if (m_isSecondJumping)
	{
		if (m_angle > -360.0f)m_angle -= 10.0f;
		if (m_rad   > -4.5f)m_rad -= 0.2f;
	}

	UpdateMove();// �ړ��p�֐�
	UpdateCamera();// �J�����p�֐�
	UpdateGravity();//�d�͌n�Ǘ��p�֐�
	UpdateHitField();//�n�ʂɓ��������ꍇ�̏���
	UpdateInvincible();// ���G���ԏ���
	UpdateRot();// �p�x�p�֐�
	JumpEffect();// �G�t�F�N�g�`��
}

void Player::Goal()
{
	// ���U��A�j���ȊO�ł���update�͌Ă΂�Ȃ�
	assert(m_animNo == kWaveAnimNo);

	

	// �N���A��ʂɈڍs�悤����
	// �J�����̈ʒu��ύX����
	if (m_goalCameraPos > -200.0f)
	{
		m_goalCameraPos -= 3.5f;
	}
	else
	{
		if (m_goalX < Game::kScreenWidth / 2)m_goalX += 30;
		if (m_goalY < Game::kScreenHeight / 2)m_goalY += 30;
	}

	m_count++;
	if (m_count > 60 * 5)
	{
		m_isClearSceneChange = true;
	}

	// ���f���̍X�V
	m_pModel->Update();
	m_pModel->SetRot(kPlayerRotaGoal);

	// ���U��A�j������������U��A�j���ɕύX
	if (m_animNo == kWaveAnimNo)
	{
		m_animNo = kWaveAnimNo;
		m_pModel->ChangeAnimation(m_animNo, true, false, 4);
	}


	// �J����
	UpdateCamera();
}

void Player::UpdateMove()
{
	// �v���C���[�̐i�s����
	MATRIX playerRotMtx = MGetRotY(-90 * DX_PI_F / 180.0f);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);
	if (m_isMove)
	{
		//�ړ���
		m_pos = VAdd(m_pos, move);
		// �v���C���[�̈ʒu
		m_pModel->SetPos(m_pos);
	}

	// �����蔻��p�T�C�Y
	m_posColl = { m_pos.x - 25.0f, m_pos.y + 50.0f,      m_pos.z };
	m_size = { m_posColl.x,     m_posColl.y + 300.0f, m_posColl.z };

	// �J�v�Z���̍��W���v�Z
	m_size.x = m_posColl.x + cosf(m_rad) * 100.0f;
	m_size.y = (m_posColl.y + sinf(m_rad) * 100.0f) + 100.0f;
	m_size.z = m_posColl.z;
}

// �p�x�Ǘ��p�֐� //
void Player::UpdateRot()
{
	// �v���C���[�̊p�x
	m_pModel->SetRot(
		VGet(
			m_angle * DX_PI_F / 180.0f, //x
			-90.0f * DX_PI_F  / 180.0f, //y
			0.0f					    //z
			)					    
	);
}

// �n�ʂɓ��������ꍇ�̏��� //
void Player::UpdateHitField()
{
	if (m_jumpAcc <= 0)
	{
		// �n�ʂɐG��Ă��邩�ǂ���
		// �n�ʂɓ���������
		if (m_isFieldHit)
		{
			// ���W��n�ʂɖ߂�
			m_pos.y = m_fieldPosY + 100.0f;
			// �W�����v�������Ȃ���
			m_jumpAcc = 0.0f;
			// ���ɂ܂��W�����v�o����悤�ɂ���
			m_isFastJumping = false;
			m_isSecondJumping = false;

			// X���̊p�x��0�ɖ߂�
			m_angle = 0.0f;
			// �����蔻��̉�]�p�x
			m_rad = 90.0f * DX_PI_F / 180.0f;
		}
	}
}

// �d�͌n�Ǘ��p�֐� //
void Player::UpdateGravity()
{
	// �d��
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
}

