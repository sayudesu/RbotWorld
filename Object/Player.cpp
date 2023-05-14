#include "Player.h"
#include<cassert>
#include <Pad.h>
#include "Animation.h"
#include "Util/DrawFunctions.h"


namespace
{
	// ���f���p�X
	const char* const kModelName = "Data/Model/Player/Robot.mv1";

	// �J�����̏����ʒu
	constexpr VECTOR kCameraPos   { 300.0f,300.0f, -1300.0f };
	constexpr VECTOR kCameraTarget{ 300.0f,300.0f, 0.0f     };

	// �ړ����x
	constexpr float kAcc = 0.3f;//�v���C���[�̉����x
//	constexpr float kWalkSpeed = 15.0f;
	constexpr float kMaxRunSpeed  = 30.0f;
	constexpr float kMaxRunSpeedDown = 20.0f;

	// �ő�HP
	constexpr int kMaxHp = 100;

	// �d��
	constexpr float kGravity = -1.5f;
	// �W�����v��
	constexpr float kJumpPower = 35.0f;

	//���G����
	constexpr int kInvincibleTime = 30;
	// �X���[����
	constexpr float kSlowSpeed = 3.0f;

	// �A�j���[�V�����i���o�[
	constexpr int kAnimNoDead    = 1;	// ����
	constexpr int kAnimNoIdle    = 2;	// �ҋ@
	constexpr int kAnimNoWalk    = 10;	// ����
	constexpr int kAnimNoRun     = 6;	// ����
	constexpr int kAnimNoAttack  = 5;	// �U��
	constexpr int kAnimNoJump    = 3;	// �W�����v
	constexpr int kAnimNoRunJump = 11;	// ����W�����v
	constexpr int kAnimNoWave    = 12;	// ���U��
}

Player::Player():
	m_cameraAngle(0.0f),
	m_idleCountTime(0),
	m_slowSpeed(0.0f),
	m_hp(0),
	m_jumpAcc(0.0f),
	m_animNo(kAnimNoIdle),
	m_playTime(0.0f),
	angle(-90.0f),
	m_isWalk(false),
	m_isRun(false),
	m_isAttack(false),
	m_attackPunch(0.0f),
	m_isDead(false),
	m_isAnimStop(false),
	m_isJump(false),
	m_isJumping(false),
	m_isDirection(false),
	m_pos(0.0f, 0.0f, 0.0f),
	m_vec(0.0f, 0.0f, 0.0f),
	m_ScereenPos(VGet(0, 0, 0))
{
	// 3D���f���̐���
	m_pAnimation = std::make_shared<Animation>(kModelName);// ���f���̃n���h����n��
	m_pAnimation->SetAnimation(m_animNo);// ���f���̓������Z�b�g

	m_size = {};
	m_attackSize = {};

	m_slowSpeed = 1.0f;

	m_hp = kMaxHp;
	m_tempHp = 0;

	m_isDamage = false;
	m_isAnimStop = true;

	m_tempDamage = 0;

	m_ultimateTimer = 1;
}

Player::~Player()
{
}

void Player::Init()
{
	m_pAnimation->Init();
}

void Player::End()
{
	m_pAnimation->End();
}

// �X�V���� //
void Player::Update()
{
	m_pAnimation->SetPos(m_pos);
	UpdateCamera();

	// �U���A�j���[�V�������~�߂�
	if (m_pAnimation->GetAnimeTime())
	{
		m_isAttack = false;
		m_isJump   = false;
		if (m_isDead)
		{
			m_isAnimStop = false;
		}
	}

	if (m_isAnimStop)// �A�j���[�V��������~����܂�
	{
		m_pAnimation->Update(0.0f, angle, 0.0f, m_playTime);// �A�j���[�V�����Đ�
	}


	UpdateRun();// �����Ă鏈��

	UpdateJumpGravity();// �W�����v����

	m_pos += m_vec;//�ړ���

	UpdateHitPoint();// �̗͂̌v�Z����
	MoveAnimation();// �A�j���[�V���������߂�

	AttackPos();// �U�����W
	UpdateInvincible();// ���G���ԏ���
}

// �`��
void Player::Draw()
{
	// UI�\��
	DrawUI();

	// �_��
	if (m_ultimateTimer % 2 == 0)return;

	// ���f���\��
	m_pAnimation->Draw();

}

void Player::UpdateControl()
{
	// �v���C���[�ƓG�̓�����x������
	if (Pad::isPress(PAD_INPUT_3))
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
		/*else
		{
			m_slowSpeed = 1.0f;
		}*/

	}

	// �U��
	if (!m_isJump)
	{
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_isAttack = true;
		}
	}

	// �W�����v
	if (!m_isJumping)
	{
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_jumpAcc = kJumpPower;
			m_isJump = true;
		}
	}


}

// �W�����v���� //
void Player::UpdateJumpGravity()
{
	// �W�����v����
	m_isJumping = true;
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	// �n�ʂɒ��n���Ă��邩�ǂ���
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;
		m_isJumping = false;
	}
}

// �����Ă鏈�� //
void Player::UpdateRun()
{
	// ���񂾏ꍇ�͓����Ȃ�
	if (!m_isDead)
	{
		// �U�������ꍇ�̓X�g�b�v
		if (!m_isAttack)
		{
			m_vec.x += kAcc;

			if (!GetInvincible())
			{
				//�^���ʂ��m�F���}�b�N�X�X�s�[�h���w��
				if (m_vec.x > kMaxRunSpeed)	m_vec.x = kMaxRunSpeed;

			}
			else
			{
				//�^���ʂ��m�F���}�b�N�X�X�s�[�h���w��
				if (m_vec.x > kMaxRunSpeedDown)	m_vec.x = kMaxRunSpeedDown;
			}
		}
		else// �U�����Ă�ꍇ�������ړ��\
		{
			m_vec.x = m_vec.x / 2.0f;//kAcc * 10;
		}
	}
	else// ���񂾂瓮���Ȃ�
	{
		m_vec.x = 0.0f;
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
			m_isDead = true;
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

bool Player::GetInvincible()
{
	if (m_ultimateTimer != 1)	return true;// �U�����󂯂Ă�����

	return false;// �󂯂Ă��Ȃ�������
}

// �_���[�W���󂯂��������X�V //
void Player::SetDamge(int damage)
{
	m_isDamage = true;

	m_tempDamage = damage;

	if (m_tempHp != m_hp)// �V�����U�����󂯂���
	{
		m_ultimateTimer = kInvincibleTime;
	}

	m_tempHp = m_hp;// ��O�̗̑͂�ۑ�

}

// �A�j���[�V���������߂� //
void Player::MoveAnimation()
{
	if (m_isDead)
	{
		m_pAnimation->SetAnimation(kAnimNoDead);// ���f���̓������Z�b�g
		m_playTime = 0.5f;	
	}
	else if (m_isJump)// �W�����v
	{
		m_pAnimation->SetAnimation(kAnimNoRunJump);// ���f���̓������Z�b�g
		m_idleCountTime = 0;
		m_playTime = 0.4f;
	}
	else if (m_isWalk)// �ړ�
	{
		m_pAnimation->SetAnimation(kAnimNoWalk);// ���f���̓������Z�b�g
		m_isAttack = false;
		m_idleCountTime = 0;
		m_playTime = 0.5f;
	}
	else if (m_isAttack)// �U��
	{
		m_pAnimation->SetAnimation(kAnimNoAttack);// ���f���̓������Z�b�g
		m_idleCountTime = 0;
		m_playTime = 0.7f;

		m_attackPunch += 10.0f;
		if (m_attackPunch > 65.0f)
		{
			m_attackPunch = 65.0f;
		}
	}
	else if (m_idleCountTime >= 60 * 5)
	{
		m_pAnimation->SetAnimation(kAnimNoWave);// ���f���̓������Z�b�g
		angle = 0.0f;
	}
	else// ����
	{
		m_pAnimation->SetAnimation(kAnimNoRun);// ���f���̓������Z�b�g
		m_idleCountTime = 0;
		m_playTime = 0.5f;
	}
}

void Player::AttackPos()
{
	// �U�����E�̈ʒu
	if (m_isAttack)
	{
		if (angle == -90.0f)
		{
			m_attackSize.left = m_ScereenPos.x - 30.0f + m_attackPunch;
			m_attackSize.top = m_ScereenPos.y - 200.0f;
			m_attackSize.right = m_attackSize.left + 110.0f + m_attackPunch;
			m_attackSize.bottom = m_attackSize.top + 100.0f;
		}
		if (angle == 90.0f)
		{
			m_attackSize.left = m_ScereenPos.x - 120.0f - (m_attackPunch * 1.5f);
			m_attackSize.top = m_ScereenPos.y - 200.0f;
			m_attackSize.right = m_attackSize.left + 180.0f;// - m_attackPunch;
			m_attackSize.bottom = m_attackSize.top + 100.0f;
		}

	}
	else
	{
		m_attackSize.left = 0;
		m_attackSize.top = 0;
		m_attackSize.right = 0;
		m_attackSize.bottom = 0;

		m_attackPunch = 0;
	}
}

void Player::UpdateCamera()
{
	// �W�����v�ꍇ
	m_cameraAngle = (m_cameraAngle * 0.8f) + (0 * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	// �W�����v���͒P���Ƀv���C���[�ɕ��]����̂ł͂Ȃ�
	//�v���C���[�̗����Ă����ʒu������悤�ɂ���

	VECTOR cameraTrans = { m_pos.x,m_pos.y,m_pos.z };
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
	// �J�����̎���p��ݒ�i���W�A���j
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
}

void Player::DrawUI()
{
	// ���[���h���W����X�N���[�����W�ɕϊ�
	m_ScereenPos = ConvWorldPosToScreenPos({ m_pos.x,m_pos.y,m_pos.z });
	m_size.left   = m_ScereenPos.x - 60.0f;
	m_size.top    = m_ScereenPos.y - 300.0f;
	m_size.right  = m_size.left    + 140.0f;
	m_size.bottom = m_size.top     + 300.0f;

	// ID��\��
	DrawFormatString(m_size.left, m_size.top, 0xffffff, "Player");
	//�q�b�g�{�b�N�X
	DrawBox(m_size.left, m_size.top,
		m_size.right, m_size.bottom,
		0xff0000, false);

	// �U���ʒu
	DrawBox(m_attackSize.left, m_attackSize.top,
		m_attackSize.right, m_attackSize.bottom,
		0xff00ff, false);

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

	// ������`��
	DrawFormatString(100, 100, 0xffffff, "%f", m_pos.x);
	if (m_pos.x > 30000)
	{
		DrawString(1000, 1000, "30000�B���I",0xffffff);
	}
}
