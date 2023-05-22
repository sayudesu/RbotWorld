#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "Animation.h"
#include <cassert>

namespace
{
	// �t�@�C����
	const char* const kFileName = "Data/Model/Player/Robot.mv1";

		// �J�����̏����ʒu
	constexpr VECTOR kCameraPos{ 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f };

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
	constexpr float kColRaidus = 200.0f;

	// HP
	constexpr int kMaxHp = 100;

}

Player::Player():
	m_updateFunc(&Player::UpdateRun),
	m_animNo(kWalkAnimNo),
	m_frameCount(0),
	m_pos(VGet(0.0f,0.0f,0.0f)),
	m_jumpAcc(0.0f),
	m_isFastJumping(false),
	m_isSecondJumping(false),
	m_angle(0.0f),
	m_cameraAngle(m_angle),
	m_slowSpeed(0.0f),
	m_hp(kMaxHp),
	m_damageFrame(0)

{
	// 3D���f���̐���
	m_pModel = std::make_shared<Animation>(kFileName);
	m_pModel->SetAnimation(m_animNo, true, true);

	m_slowSpeed = 1.0f;

}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{

}
void Player::Update()
{	
	(this->*m_updateFunc)();
}

void Player::Draw()
{
	//�̗͂�`��
	DrawBox(100 - 1, 130 - 1,
		100 + 400 + 1, 130 + 1 + 20,
		0xff0000, true);//�O�g
	DrawBox(100 - 1, 130 - 1,
		100 + 400 + 1, 130 + 1 + 20,
		0xffff00, false);//�O�g
	DrawBox(100, 130,
		100 + 400 * m_hp / kMaxHp, 130 + 20,
		0x0ffff0, true);//���[�^�[
	//���� * HP / HPMAX

	// �_��
	if (m_ultimateTimer % 2 == 0)return;

	m_pModel->Draw();
}

float Player::GetColRadius()
{
	return kColRaidus;
}

float Player::GetRadius() const
{
	return kColRaidus;
}

void Player::OnDamage(int damage)
{
	m_isDamage = true;

	m_tempDamage = damage;

	if (m_tempHp != m_hp)// �V�����U�����󂯂���
	{
		m_ultimateTimer = 30;//kInvincibleTime;
	}

	m_tempHp = m_hp;// ��O�̗̑͂�ۑ�
}

bool Player::GetInvincible()
{
	if (m_ultimateTimer != 1)	return true;// �U�����󂯂Ă�����

	return false;// �󂯂Ă��Ȃ�������
}

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

void Player::UpdateHitPoint()
{
	// HP�o�[�̗� - �_���[�W�������X�Ɍ��炷
	if (m_isDamage)
	{
		// HPUI�̘g�𒴂��Ȃ��l�� + 1
		if (m_hp < 0 + 1)
		{
			// HP��0�ɐݒ�
			m_hp = 0;
			// ����
		//	m_isDead = true;
		}
		else if (m_hp > m_tempHp - m_tempDamage)
		{
			// ���炷
			m_hp--;
		}
		else
		{
			// ���炵�I������獇�}
			m_isDamage = false;
		}
	}
}

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
//	m_isFastJumping = false;
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isFastJumping = true;
	}
	
}

void Player::UpdateCamera()
{
	// �W�����v�ꍇ
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// �W�����v���͒P���Ƀv���C���[�ɕ��]����̂ł͂Ȃ�
	//�v���C���[�̗����Ă����ʒu������悤�ɂ���

	VECTOR cameraTrans = { m_pos.x,0.0f,m_pos.z };

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
	// �A�j���[�V������i�߂�
	m_pModel->Update();

	m_damageFrame--;
	if (m_damageFrame <= 0) { m_damageFrame = 0; }

	// �W�����v�ł��邩�ǂ���
	if (!m_isJumping)
	{
		// 1�{�^���ŃW�����v
		if(m_isFastJumping)
		{
			// �W�����v��
			m_jumpAcc = kJumpPower;

			// �W�����v�A�j���[�V�����ɕύX
			m_animNo = kJumpAnimNo;
			m_pModel->ChangeAnimation(m_animNo, false, false, 4);
			m_updateFunc = &Player::UpdateJump;
		}
	}

	if (m_animNo == kWalkAnimNo)
	{
		// ����A�j���ɕύX
		m_animNo = kWalkAnimNo;
		m_pModel->ChangeAnimation(m_animNo, true, false, 4);
	}

	UpdateMove();
	UpdateCamera();
}

void Player::UpdateJump()
{
	m_damageFrame--;
	if (m_damageFrame <= 0) { m_damageFrame = 0; }

	// �V���b�g�A�j���ȊO�ł���update�͌Ă΂�Ȃ�
	assert(m_animNo == kJumpAnimNo);
	m_pModel->Update();

	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;

	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;

		m_isFastJumping = false;
		m_isSecondJumping = false;

		// ����A�j���ɕύX����
		m_animNo = kWalkAnimNo;
		m_angle = 0.0f;// X���̊p�x��0�ɖ߂�
		m_pModel->ChangeAnimation(kWalkAnimNo, true, true, 4);
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
		else
		{
			// X���̊p�x��ύX����
			if (m_angle > -360.0f)m_angle -= 10.0;
		}
	}

	if (m_pModel->IsAnimEnd())
	{
	//	m_pModel->ChangeAnimation(kWalkAnimNo, true, true, 4);
	}

	UpdateMove();
	UpdateCamera();
}

void Player::UpdateMove()
{
	UpdateHitPoint();// �̗͂̌v�Z����
	UpdateInvincible();// ���G���ԏ���
	// �v���C���[�̐i�s����
	MATRIX playerRotMtx = MGetRotY(-90 * DX_PI_F / 180.0f);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);

	//�ړ���
	m_pos = VAdd(m_pos, move);
	// �v���C���[�̊p�x
	m_pModel->SetRot(VGet(
		m_angle * DX_PI_F / 180.0f,
		-90.0f * DX_PI_F / 180.0f,
		0.0f));
	// �v���C���[�̈ʒu
	m_pModel->SetPos(m_pos);

	// �܂������i��
	m_lastPos = m_pos;

	DrawCapsule3D(
		m_lastPos,
		VGet(m_lastPos.x, m_lastPos.y + kColRaidus, m_lastPos.z),
		100.0f,
		8,
		0xffffff,
		0xffffff,
		true);

	//radcounter++;

	//rad = radcounter / 180 * DX_PI;

	//m_lastPos.x = cos(rad);	
	//m_lastPos.y = sin(rad);
	//

	//	m_lastPos.x++;
	//	printfDx("%f\n", m_lastPos.x);

}
