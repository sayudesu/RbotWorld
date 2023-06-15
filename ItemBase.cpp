#include "ItemBase.h"
#include <cassert>

ItemBase::ItemBase(int handle):
	m_hItem(0),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_size(VGet(0.0f, 0.0f, 0.0f)),
	m_rota(VGet(0.0f, 0.0f, 0.0f))
{
	m_hItem = MV1LoadModel("Data/Model/Item/CoinCrown.mv1");
	assert(m_hItem != 0);

	m_hItem = MV1DuplicateModel(handle);
}

ItemBase::~ItemBase()
{
	// モデルのアンロード.
	MV1DeleteModel(m_hItem);
}

void ItemBase::Update()
{

	MV1SetPosition(m_hItem, m_pos);
	MV1SetScale(m_hItem, m_size);
	MV1SetRotationXYZ(m_hItem, m_rota);

	//TODO : Y軸で回転させる処理
//	printfDx("%f\n", m_pos.x);
}

void ItemBase::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_hItem);
}
