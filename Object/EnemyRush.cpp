#include "EnemyRush.h"
#include "Model.h"


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
	m_pModel = std::make_shared<Model>(kModelName);// ���f���̃n���h����n��
	m_pModel->SetAnimation(kAnimNoRush,true,true);// ���f���̓������Z�b�g

	m_pos = pos;

	// ���f���̌���
	m_angle.x = 90.0f;
	m_angle.y = 90.0f;

	m_hitDamage = kDamagePower;

	m_pModel->SetUseCollision(true, true);

}

EnemyRush::~EnemyRush()
{
	printfDx("�����܂���\n");
}

void EnemyRush::Init()
{
	m_pModel->Init();
}

void EnemyRush::End()
{
	m_pModel->End();
}

void EnemyRush::Update()
{
	m_pModel->SetPos(VGet(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Update();//m_angle,1.0f
	
	m_pos.x -= kRushSpeed;

	VECTOR size = { 0.2f,0.2f ,0.2f };
//	m_pAnimation->SetSize(size);

	m_pModel->SetSize(VGet(0.3f, 0.3f, 0.3f));
	m_pModel->SetRot(VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
}

void EnemyRush::Draw()
{
	m_pModel->Draw();
}

int EnemyRush::GetModelHandle()
{
	return m_pModel->GetModelHandle();
}

int EnemyRush::GetColFrameIndex() const
{
	return m_pModel->GetColFrameIndex();
}