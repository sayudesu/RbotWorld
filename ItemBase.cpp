#include "ItemBase.h"
#include <cassert>

namespace
{
	// アイテムの回転スピード
	constexpr float kRotaSpeed = 0.05f;
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
	ItemState();

	if (m_isErase)
	{
		m_updateFunc = &ItemBase::Erase;
	}
}

// ３Ｄモデルの描画
void ItemBase::Draw()
{	
	MV1DrawModel(m_hItem);
}

void ItemBase::Erase()
{
	m_pos.y += 30.0f;
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
	int a = GetRand(4);
	float speedRand = 0.0f;
	if (a == 0)
	{
		speedRand = 0.02;
	}
	else if(a == 1)
	{
		speedRand = 0.04;
	}
	else if (a == 2)
	{
		speedRand = 0.06;
	}
	else if (a == 3)
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
