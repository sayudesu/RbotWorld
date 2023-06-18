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
	m_rota(VGet(0.0f, 0.0f, 0.0f))
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
	// 位置 サイズ 回転
	MV1SetPosition(m_hItem, m_pos);
	MV1SetScale(m_hItem, m_size);
	MV1SetRotationXYZ(m_hItem, m_rota);

	// オブジェクトを回転させます
	UpdateRota();
}

// ３Ｄモデルの描画
void ItemBase::Draw()
{	
	MV1DrawModel(m_hItem);
}

// オブジェクトを回転させます
void ItemBase::UpdateRota()
{
	// 1ラジアン分回転させる
	// 1ラジアンを超えると0で初期化
	if (m_rota.y < DX_PI_F)
	{
		m_rota.y += kRotaSpeed;
	}
	else
	{
		m_rota.y = 0.00f;
	}
}
