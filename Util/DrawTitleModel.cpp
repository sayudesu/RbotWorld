#include "DrawTitleModel.h"
#include "Model.h"

namespace
{
	// �t�@�C����
	const char* const kFileName = "Data/Model/Player/Robot.mv1";
	constexpr float kModelSpeed = 30.0f;
}

TitleDrawModeler::TitleDrawModeler():
	m_posY(-1000.0f),
	m_pModel(nullptr),
	m_isMoveSelect(false),
	m_isSceneChange(false)

{
	m_pModel = new Model(kFileName);
	m_pModel->SetAnimation(6, true, true);

	// ���f���̏�ԏ����ݒ�
	m_pModel->SetPos(VGet(-1000.0f, 0.0f, 0.0f));
	m_pModel->SetRot(VGet(0.0f, -90 * DX_PI_F / 180.0f, 0.0f));

	// �J�����̐ݒ�
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p�i60�j��ݒ�i���W�A���j
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(
		VGet(0.0f,400.0f,-1300.0f),
		VGet(0.0f,200.0f, 0.0f)
		 );

}

TitleDrawModeler::~TitleDrawModeler()
{
	// ���������
	delete m_pModel;
}

void TitleDrawModeler::Update()
{
	// ���f���̍X�V����
	m_pModel->Update();
	m_pModel->SetPos(VGet(m_posY, 0.0f, 0.0f));

	// -1000��
	// 0�@�@��
	// 1000�E
	// ��ʐ^�񒆈ʂ܂ňړ�����
	if(m_posY < 0.0f)m_posY += kModelSpeed;

	// ����{�^�����������Ă���E�Ɉړ��n�߂�
	if (m_isMoveSelect)m_posY += kModelSpeed;
	// ��ʉE�܂ňړ��������ǂ���
	if (m_posY > 1000.0f)m_isSceneChange = true;
}

void TitleDrawModeler::Draw()
{
	// ���f���`��
	m_pModel->Draw();
}
