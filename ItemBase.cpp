#include "ItemBase.h"
#include <cassert>

namespace
{
	// �A�C�e���̉�]�X�s�[�h
	constexpr float kRotaSpeed = 0.05f;
}

ItemBase::ItemBase(int handle):
	m_hItem(-1),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_size(VGet(0.0f, 0.0f, 0.0f)),
	m_rota(VGet(0.0f, 0.0f, 0.0f))
{
	m_hItem = MV1DuplicateModel(handle);
	assert(m_hItem != -1);
}

ItemBase::~ItemBase()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(m_hItem);
}

void ItemBase::Update()
{
	// �ʒu �T�C�Y ��]
	MV1SetPosition(m_hItem, m_pos);
	MV1SetScale(m_hItem, m_size);
	MV1SetRotationXYZ(m_hItem, m_rota);

	// �I�u�W�F�N�g����]�����܂�
	UpdateRota();
}

// �R�c���f���̕`��
void ItemBase::Draw()
{	
	MV1DrawModel(m_hItem);
}

// �I�u�W�F�N�g����]�����܂�
void ItemBase::UpdateRota()
{
	// 1���W�A������]������
	// 1���W�A���𒴂����0�ŏ�����
	if (m_rota.y < DX_PI_F)
	{
		m_rota.y += kRotaSpeed;
	}
	else
	{
		m_rota.y = 0.00f;
	}
}
