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

void ItemManegaer::CreateCoin(int coinPosX[], int coinPosY[], int coinNum)
{
	// コインのモデルハンドル
	m_hItem = MV1LoadModel("Data/Model/Item/CoinCrown.mv1");

	// コインの数分要素を追加
	// コインの位置を取得
	// コインの状態を取得
	// コインクラスのインスタンスを作成(コインのモデルハンドル)
	// コインに状態を渡す
	for (int i = 0; i < coinNum; i++)
	{
		m_coinPosX.push_back(0);
		m_coinPosY.push_back(0);

		m_coinPosX[i] = coinPosX[i];
		m_coinPosY[i] = coinPosY[i];

		m_pos = VGet(m_coinPosX[i], m_coinPosY[i] + 150.0f, 0.0f);
		m_size = VGet(10.0f, 10.0f, 10.0f);
		m_rota = VGet(-90 * DX_PI_F / 180.0f, 0.0f, 0.0f);

		m_pCoin.push_back(std::make_shared<Coin>(m_hItem));

		m_pCoin[i]->SetPos(m_pos);
		m_pCoin[i]->SetSize(m_size);
		m_pCoin[i]->SetRota(m_rota);
	}
}

void ItemManegaer::Delete()
{
	DeleteGraph(m_hItem);
}

void ItemManegaer::Update()
{
	for (auto& coin : m_pCoin)
	{
		coin->Update();
	}
}

void ItemManegaer::Draw()
{
	for (auto& coin : m_pCoin)
	{
		coin->Draw();
	}
}


