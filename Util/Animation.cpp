#include "Animation.h"
#include <cassert>

Animation::Animation(const char* modelName, Vec3 pos) :
	m_modelHandle(-1),
	m_playTime(0.0f),
	m_attachIndex(0), m_totalTime(0),
	m_saveAnimNo(2),
	m_isAnimTime(false)
{
	m_modelHandle = MV1LoadModel(modelName);
	assert(m_modelHandle != -1);

	VECTOR DxPos = { pos.x, pos.y, pos.z };
	MV1SetPosition(m_modelHandle, DxPos);
}

Animation::Animation(const char* modelName):
	m_modelHandle(-1),
	m_playTime(0.0f),
	m_attachIndex(0), m_totalTime(0),
	m_saveAnimNo(2),
	m_isAnimTime(false)
{
	m_modelHandle = MV1LoadModel(modelName);
	assert(m_modelHandle != -1);
}

Animation::~Animation()
{
}

void Animation::Init()
{
	// �R�c���f���̂O�Ԗڂ̃A�j���[�V�������A�^�b�`����
	m_attachIndex = MV1AttachAnim(m_modelHandle, m_saveAnimNo, -1, FALSE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	m_totalTime = static_cast<int>(MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex));

	// �W�����C�g�𖳌��ɂ���
	SetLightEnable(true);
}

void Animation::End()
{
	MV1DeleteModel(m_modelHandle);
}

void Animation::Update(VECTOR rota,float animTime)
{
	// �Đ����Ԃ�i�߂�
	m_playTime += animTime;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (m_playTime > m_totalTime)
	{
		m_playTime = 0.0f;
		m_isAnimTime = true;
	}
	else
	{
		m_isAnimTime = false;
	}

	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(m_modelHandle, m_attachIndex, m_playTime);
	// ���f���̌������Z�b�g����
	MV1SetRotationXYZ(m_modelHandle, VGet(rota.x * DX_PI_F / 180.0f,
										  rota.y * DX_PI_F / 180.0f,
		                                  rota.z * DX_PI_F / 180.0f));
}

void Animation::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void Animation::SetAnimation(int animNo)
{
//	if (m_isAnimTime) return;

	int tempIndex = m_attachIndex;

	// �O��Ƃ͈Ⴄ�A�j���[�V������������
	if (m_saveAnimNo != animNo)
	{
		// �A�j���[�V���������폜
		MV1DetachAnim(m_modelHandle, m_attachIndex);
		// �A�j���[�V�����Đ����Ԃ�������
		m_playTime = 0.0f;
		// �V�����A�j���[�V�������
		MV1SetAttachAnimTime(m_modelHandle, animNo, m_playTime);
		// �R�c���f����animNo�Ԗڂ̃A�j���[�V�������A�^�b�`����
		m_attachIndex = MV1AttachAnim(m_modelHandle, animNo, -1, FALSE);
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);
		// �A�j���[�V�����L�^
		m_saveAnimNo = animNo;
	}

	//// �A�j���[�V�����ω��̃t���[�����ɉ������u�����h����ݒ肷��
	//float rate = static_cast<float>(m_animChangeFrame) / static_cast<float>(m_animChangeFrameTotal);
	//if (rate > 1.0f)	rate = 1.0f;

	//MV1SetAttachAnimBlendRate(m_modelHandle, tempIndex, 1.0f - rate);
	//MV1SetAttachAnimBlendRate(m_modelHandle, m_attachIndex, rate);
}

void Animation::ChangeAnimation(int animNo, bool isLoop)
{
	// �A�j���[�V���������폜
	MV1DetachAnim(m_modelHandle, m_attachIndex);
	// �A�j���[�V�����Đ����Ԃ�������
	m_playTime = 0.0f;
	// �A�j���[�V�����L�^
	m_saveAnimNo = animNo;
	// �V�����A�j���[�V�������
	MV1SetAttachAnimTime(m_modelHandle, m_saveAnimNo, m_playTime);
	// �R�c���f����animNo�Ԗڂ̃A�j���[�V�������A�^�b�`����
	m_attachIndex = MV1AttachAnim(m_modelHandle, m_saveAnimNo, -1, FALSE);
	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);

}

void Animation::SetPos(Vec3 pos)
{
	// �ʒu���擾����
	VECTOR dxPos = { pos.x, pos.y, pos.z };
	MV1SetPosition(m_modelHandle, dxPos);
}

void Animation::SetSize(VECTOR size)
{
	// �R�c���f���̃X�P�[����x�������ɂQ�{�ɂ���
	MV1SetScale(m_modelHandle, size);
}
