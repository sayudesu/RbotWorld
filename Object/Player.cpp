#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "Animation.h"
#include <cassert>




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

	if (m_damageFrame > 0)
	{
		//if (m_damageFrame % 2)return;
	}

	m_pModel->Draw();
}

float Player::GetColRadius()
{
	return kColRaidus;
}

void Player::OnDamage(int damage)
{
	if (m_damageFrame > 0) return;
	m_hp -= damage;
	m_damageFrame = 60 * 2;
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
	/*
	// m_cameraAngle = m_angle;
	m_cameraAngle = (m_cameraAngle * 0.8f) + (m_angle * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// �W�����v���͒P���Ƀv���C���[�ɒǏ]����̂ł͂Ȃ�
	// �v���C���[�̗����Ă����ʒu������悤�ɂ���
	VECTOR cameraTrans = m_pos;
	// cameraTrans.y = 0.0f;
	cameraTrans.y = m_pos.y * 0.3f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	
	// �v���C���[�̉�]�ɍ��킹�ăJ�����ʒu�A�����_����]������
	// �v���C���[�̉�]���ƕ��s�ړ���������
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	// �J�����̐ݒ�
	// �ǂ��܂ŕ\�����邩
	// SetCameraNearFar(5.0f, 2800.0f);
	 SetCameraNearFar(5.0f, 3500.0f);
	// �J�����̎���p(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
	*/
	// �W�����v�ꍇ
//	m_cameraAngle = (m_cameraAngle * 0.8f) + (0 * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// �W�����v���͒P���Ƀv���C���[�ɕ��]����̂ł͂Ȃ�
	//�v���C���[�̗����Ă����ʒu������悤�ɂ���

	VECTOR cameraTrans = { m_pos.x,0.0f,m_pos.z };
	//cameraTrans.y = m_pos.y * 0.0f;
	//cameraTrans.y = m_pos.y * 0.2f;
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
	//SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(300.0f, 0.0f, 300.0f));
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
	//	printfDx("�I���܂����B\n");
	}

	UpdateMove();
	UpdateCamera();
}

void Player::UpdateMove()
{
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
		m_pos,
		VGet(m_pos.x, m_pos.y + kSize, m_pos.z),
		100.0f,
		8,
		0xffffff,
		0xffffff,
		true);

	//	m_lastPos.x++;
	//	printfDx("%f\n", m_lastPos.x);

}
