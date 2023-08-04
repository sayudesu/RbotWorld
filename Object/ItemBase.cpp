#include "ItemBase.h"
#include <cassert>
#include "../Util/Sound.h"

namespace
{
	// �A�C�e���̉�]�X�s�[�h
	constexpr float kRotaSpeed = 0.05f;
	// �A�C�e���`��s�ʒu
	constexpr float kErasePosY = 1200.0f;
}

ItemBase::ItemBase(int handle):
	m_hItem(-1),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_size(VGet(0.0f, 0.0f, 0.0f)),
	m_rota(VGet(0.0f, 0.0f, 0.0f)),
	m_isErase(false),
	m_updateFunc(&ItemBase::StartUpdate)
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
	(this->*m_updateFunc)();
}

void ItemBase::StartUpdate()
{
	// �A�C�e���̏�Ԃ�ύX
	ItemState();
	// �A�C�e�����v���C���[�����肷���
	if (m_isErase)
	{
		m_updateFunc = &ItemBase::Erase;
	}
}

// �R�c���f���̕`��
void ItemBase::Draw()
{	
	// �A�C�e���`�拗�����w��
	if(m_pos.y < kErasePosY)MV1DrawModel(m_hItem);
}

void ItemBase::Erase()
{
	// �A�C�e�����㏸������
	m_pos.y += 30.0f;
	// �A�C�e���̏�Ԃ�ύX
	ItemState();
}

void ItemBase::ItemState()
{
	// �ʒu �T�C�Y ��]
	MV1SetPosition(m_hItem, m_pos);
	MV1SetScale(m_hItem, m_size);
	MV1SetRotationXYZ(m_hItem, m_rota);
	UpdateRota();
}

// �I�u�W�F�N�g����]�����܂�
void ItemBase::UpdateRota()
{
	int rotaNo = GetRand(4);
	float speedRand = 0.0f;
	if (rotaNo == 0)
	{
		speedRand = 0.02;
	}
	else if(rotaNo == 1)
	{
		speedRand = 0.04;
	}
	else if (rotaNo == 2)
	{
		speedRand = 0.06;
	}
	else if (rotaNo == 3)
	{
		speedRand = 0.08;
	}
	// 1���W�A������]������
	// 1���W�A���𒴂����0�ŏ�����
	if (m_rota.y < DX_PI_F)
	{
		m_rota.y += kRotaSpeed + speedRand;
	}
	else
	{
		m_rota.y = 0.00f;
	}
}

void ItemBase::SetEraseItem(bool isErase)
{
	m_isErase = isErase;
	Sound::play(Sound::SoundId_Coin);
	// ���ʐݒ�	0~255
	Sound::setVolume(Sound::SoundId_Coin, 100);
}
