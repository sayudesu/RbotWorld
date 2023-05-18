#include "EnemyRush.h"
#include "Animation.h"


namespace
{
	const char* const kModelName = "Data/Model/Enemy/uploads_files_2381754_Striker.mv1";
	// �����ʒu
	constexpr VECTOR kDefaultPos = { 1500.0f,0.0f,0.0f };

	// �����̑���
	constexpr float kSpeedIdle = 3.0f;

	constexpr float kRushSpeed = 15.0f;

	// �ő�HP
	constexpr int kMaxHp = 100;

	// �A�j���[�V�����i���o�[
	constexpr int kAnimNoView = 0;	// ��������
	constexpr int kAnimNoDead = 1;	// ����
	constexpr int kAnimNoIdle = 2;	// �ҋ@
	constexpr int kAnimNoRush = 3;	// ����

}

EnemyRush::EnemyRush(Vec3 pos)/*:
	m_upddateFunc(&EnemyRush::Update)*/
{
	//VECTOR pos{};

	// 3D���f���̐���
	m_pAnimation = std::make_shared<Animation>(kModelName);// ���f���̃n���h����n��
	m_pAnimation->SetAnimation(kAnimNoRush,true,true);// ���f���̓������Z�b�g

	m_pos = pos;

	// ���f���̌���
	m_angle.x = 90.0f;
	m_angle.y = 90.0f;

//	m_size = {};

//	m_posPlayer = {};

	m_hp = kMaxHp;

	m_isDead = false;

}

EnemyRush::~EnemyRush()
{
	
}

void EnemyRush::Init()
{
	m_pAnimation->Init();
}

void EnemyRush::End()
{
	m_pAnimation->End();
}

void EnemyRush::Update()
{
	m_pAnimation->SetPos(VGet(m_pos.x, m_pos.y, m_pos.z));
	m_pAnimation->Update();//m_angle,1.0f
	
	m_pos.x -= kRushSpeed;

	VECTOR size = { 0.2f,0.2f ,0.2f };
//	m_pAnimation->SetSize(size);

	m_pAnimation->SetSize(VGet(0.3f, 0.3f, 0.3f));
	m_pAnimation->SetRot(VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	if (m_hp == 0)printfDx("����ł��܂��B\n");
}

void EnemyRush::Draw()
{
	m_pAnimation->Draw();
	DrawUI();
}

void EnemyRush::Dead()
{

}

void EnemyRush::DrawUI()
{
	if (!m_isDead)
	{
		const VECTOR pos = ConvWorldPosToScreenPos({m_pos.x,m_pos.y ,m_pos.z});

		//m_size.left   = pos.x- 50.0f;
		//m_size.top    = pos.y - 130.0f;
		//m_size.right  = m_size.left  + 110.0f;
		//m_size.bottom = m_size.top   + 130.0f;

		//DrawFormatString(m_size.left, m_size.top, 0xffffff, "EnemyRush");
		//DrawBox(m_size.left, m_size.top, m_size.right, m_size.bottom, 0xff0000, false);

		////�̗͂�`��
		//DrawBox(m_size.left - 1, m_size.top - 1,
		//	m_size.left + 100 + 1, m_size.top + 1 + 20,
		//	0x0000ff, true);//�O�g
		//DrawBox(m_size.left, m_size.top,
		//	m_size.left + 100 * m_hp / kMaxHp, m_size.top + 20,
		//	0x0ffff0, true);//���[�^�[
		////���� * HP / HPMAX
	}
	else
	{
	/*	m_size.left   = NULL;
		m_size.top    = NULL;
		m_size.right  = NULL;
		m_size.bottom = NULL;*/
	}

}
