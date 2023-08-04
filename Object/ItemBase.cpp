#include "ItemBase.h"
#include <cassert>
#include "../Util/Sound.h"

namespace
{
	// アイテムの回転スピード
	constexpr float kRotaSpeed = 0.05f;
	// アイテム描画不可位置
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
	// モデルのアンロード.
	MV1DeleteModel(m_hItem);
}

void ItemBase::Update()
{
	(this->*m_updateFunc)();
}

void ItemBase::StartUpdate()
{
	// アイテムの状態を変更
	ItemState();
	// アイテムをプレイヤーが入手すると
	if (m_isErase)
	{
		m_updateFunc = &ItemBase::Erase;
	}
}

// ３Ｄモデルの描画
void ItemBase::Draw()
{	
	// アイテム描画距離を指定
	if(m_pos.y < kErasePosY)MV1DrawModel(m_hItem);
}

void ItemBase::Erase()
{
	// アイテムを上昇させる
	m_pos.y += 30.0f;
	// アイテムの状態を変更
	ItemState();
}

void ItemBase::ItemState()
{
	// 位置 サイズ 回転
	MV1SetPosition(m_hItem, m_pos);
	MV1SetScale(m_hItem, m_size);
	MV1SetRotationXYZ(m_hItem, m_rota);
	UpdateRota();
}

// オブジェクトを回転させます
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
	// 1ラジアン分回転させる
	// 1ラジアンを超えると0で初期化
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
	// 音量設定	0~255
	Sound::setVolume(Sound::SoundId_Coin, 100);
}
