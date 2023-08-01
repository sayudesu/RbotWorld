#include "EffekseerDrawer.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <cassert>

EffekseerDrawer::EffekseerDrawer():
	m_hEff(-1),
	m_hPlayEff(-1),
	m_hBg(-1),
	m_time(0)
{
}

EffekseerDrawer::~EffekseerDrawer()
{
}

int EffekseerDrawer::Init()
{
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	m_hEff = LoadEffekseerEffect("goal.efkefc",80.0f);
	assert(m_hEff != -1);
	m_hBg = LoadGraph("Background.png");
	assert(m_hBg != -1);
	return 0;
}

void EffekseerDrawer::End()
{
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
	DeleteEffekseerEffect(m_hEff);
}

void EffekseerDrawer::Update()
{
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();
}

void EffekseerDrawer::Draw(VECTOR pos)
{
	// ����I�ɃG�t�F�N�g���Đ�����
	if (m_time % 60 == 0)
	{
		// �G�t�F�N�g���Đ�����B
		m_hPlayEff = PlayEffekseer3DEffect(m_hEff);
	}
	m_time++;

	// �Đ����̃G�t�F�N�g���ړ�����B
	SetPosPlayingEffekseer3DEffect(m_hPlayEff, pos.x, pos.y , pos.z);

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}
