#include "DrawTitleModel.h"
#include "Model.h"

namespace
{
	// �t�@�C����
	const char* const kFileName = "Data/Model/Player/Robot.mv1";
}

DrawTitleModel::DrawTitleModel():
	posZ(0.0f),
	m_pModel(nullptr)
{
	m_pModel = new Model(kFileName);
	m_pModel->SetAnimation(6, true, true);

	m_pModel->SetPos(VGet(0.0f, 0.0f, 0.0f));

	// �J�����̐ݒ�
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p�i60�j��ݒ�i���W�A���j
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(
		VGet(0.0f,400.0f,-1300.0f),
		VGet(m_pModel->GetModelPos().x,200.0f,m_pModel->GetModelPos().z)
		 );

}

DrawTitleModel::~DrawTitleModel()
{
	delete m_pModel;
}

void DrawTitleModel::Update()
{
	// ���f���̍X�V����
	m_pModel->Update();
	m_pModel->SetPos(VGet(0.0f, 0.0f, posZ));

	posZ -= 10.0f;
}

void DrawTitleModel::Draw()
{
	// ���f���`��
	m_pModel->Draw();
}
