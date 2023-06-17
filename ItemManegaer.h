#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

class ItemBase;
class ItemManegaer
{
public:
	ItemManegaer();
	virtual ~ItemManegaer();

	void Load();

	/// <summary>
	/// コインの作成
	/// </summary>
	/// <param name="coinPosX">コインのX位置</param>
	/// <param name="coinPosY">コインのY位置</param>
	/// <param name="coinNum"> コインの数   </param>
	void CreateCoin(int coinPosX[], int coinPosY[], int coinNum);

	void Delete();
	void Update();
	void Draw();

private:
	// モデルハンドル
	int m_hItem;
	// 位置
	VECTOR m_pos;
	// サイズ
	VECTOR m_size;
	// 角度
	VECTOR m_rota;

	std::vector<int>m_coinPosX;
	std::vector<int>m_coinPosY;

	// コインクラス
	std::vector<std::shared_ptr<ItemBase>> m_pCoin;
};
