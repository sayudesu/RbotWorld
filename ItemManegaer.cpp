#include "ItemManegaer.h"
#include <cassert>
#include "Coin.h"

ItemManegaer::ItemManegaer():
	m_hItem(-1),
	m_pos(VGet(0.0f,0.0f, 0.0f)),
	m_size(VGet(0.0f,0.0f, 0.0f)),
	m_rota(VGet(0.0f,0.0f, 0.0f))
{
}

ItemManegaer::~ItemManegaer()
{
}

void ItemManegaer::Load()
{
}

void ItemManegaer::Create()
{
	m_hItem = MV1LoadModel("Data/Model/Item/CoinCrown.mv1");
	assert(m_hItem != 0);

	m_pCoin = std::make_shared<Coin>(m_hItem);

	m_pCoin->SetPos (m_pos);
	m_pCoin->SetSize(m_size);
	m_pCoin->SetRota(m_rota);

}

void ItemManegaer::Delete()
{
	DeleteGraph(m_hItem);
}

void ItemManegaer::Update()
{
	m_pCoin->Update();
}

void ItemManegaer::Draw()
{
	m_pCoin->Draw();
}
