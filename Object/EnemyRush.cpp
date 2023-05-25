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
	
	constexpr int kDamagePower = 30;

	// �A�j���[�V�����i���o�[
	constexpr int kAnimNoView = 0;	// ��������
	constexpr int kAnimNoDead = 1;	// ����
	constexpr int kAnimNoIdle = 2;	// �ҋ@
	constexpr int kAnimNoRush = 3;	// ����

}

EnemyRush::EnemyRush(Vec3 pos)
{
	// 3D���f���̐���
	m_pAnimation = std::make_shared<Animation>(kModelName);// ���f���̃n���h����n��
	m_pAnimation->SetAnimation(kAnimNoRush,true,true);// ���f���̓������Z�b�g

	m_pos = pos;

	// ���f���̌���
	m_angle.x = 90.0f;
	m_angle.y = 90.0f;

	m_hitDamage = kDamagePower;

	m_pAnimation->SetUseCollision(true, true);

}

EnemyRush::~EnemyRush()
{
	printfDx("�����܂���\n");
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
}

void EnemyRush::Draw()
{
	m_pAnimation->Draw();
}

int EnemyRush::GetModelHandle()
{
	return m_pAnimation->GetModelHandle();
}

int EnemyRush::GetColFrameIndex() const
{
	return m_pAnimation->GetColFrameIndex();
}