#include "ItemManegaer.h"
#include <cassert>
#include "Coin.h"
#include <DxLib.h>


ItemManegaer::ItemManegaer():
	m_hItem(),
	m_pos(VGet(0.0f,0.0f, 0.0f)),
	m_size(VGet(0.0f,0.0f, 0.0f)),
	m_rota(VGet(0.0f,0.0f, 0.0f))
{
	m_hItem[0] = -1;
	m_hItem[1] = -1;
}

ItemManegaer::~ItemManegaer()
{
}

void ItemManegaer::Load()
{
}

void ItemManegaer::CreateCoin(std::vector<int> coinPosX, std::vector<int>coinPosY, int coinNum)
{
	// コインのモデルハンドル
	m_hItem[0] = MV1LoadModel("Data/Model/Item/CoinCrown.mv1");
	assert(m_hItem[0] != -1);
	
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

		m_pCoin.push_back(std::make_shared<Coin>(m_hItem[0]));

		m_pCoin[i]->SetPos(m_pos);
		m_pCoin[i]->SetSize(m_size);
		m_pCoin[i]->SetRota(m_rota);
	}
}

void ItemManegaer::CreateDiamond(std::vector<int> diamondPosX, std::vector<int>diamondPosY, int diamondNum)
{
	// ダイヤのモデルハンドル
	m_hItem[1] = MV1LoadModel("Data/Model/Item/Diamond.mv1");
	assert(m_hItem[1] != -1);

	// ダイヤの数分要素を追加
	// ダイヤの位置を取得
	// ダイヤの状態を取得
	// ダイヤクラスのインスタンスを作成(コインのモデルハンドル)
	// ダイヤに状態を渡す
	for (int i = 0; i < diamondNum; i++)
	{
		m_diamondPosX.push_back(0);
		m_diamondPosY.push_back(0);

		m_diamondPosX[i] = diamondPosX[i];
		m_diamondPosY[i] = diamondPosY[i];

		m_pos = VGet(m_diamondPosX[i], m_diamondPosY[i] + 150.0f, 0.0f);
		m_size = VGet(10.0f, 10.0f, 10.0f);
		m_rota = VGet(0.0f, 0.0f, 0.0f);

		m_pDiamond.push_back(std::make_shared<Coin>(m_hItem[1]));

		m_pDiamond[i]->SetPos(m_pos);
		m_pDiamond[i]->SetSize(m_size);
		m_pDiamond[i]->SetRota(m_rota);
	}
}

// メモリの解放
void ItemManegaer::Delete()
{
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(m_hItem[i]);
	}
}

void ItemManegaer::Update()
{
	for (auto& coin : m_pCoin)
	{
		coin->Update();
	}
	for (auto& coin : m_pDiamond)
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
	for (auto& coin : m_pDiamond)
	{
		coin->Draw();
	}
}

// アイテムが当たった場合その番号を返す
void ItemManegaer::SetEraseNo(Item name, int eraseNo)
{
	// 当たったらtrue
	if (name == Item::coin)m_pCoin[eraseNo]->SetEraseItem(true);
	if (name == Item::diamond)m_pDiamond[eraseNo]->SetEraseItem(true);
}

bool ItemManegaer::isErase(Item name ,int eraseNo)
{
	if (name == Item::coin)return m_pCoin[eraseNo]->isGetItem();
	if (name == Item::diamond)return m_pDiamond[eraseNo]->isGetItem();
}



