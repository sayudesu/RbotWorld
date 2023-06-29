#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "ItemName.h"

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
	void CreateCoin(std::vector<int> coinPosX, std::vector<int>coinPosY, int coinNum);
	/// <summary>
	/// ダイヤの作成
	/// </summary>
	/// <param name="coinPosX">ダイヤのX位置</param>
	/// <param name="coinPosY">ダイヤのY位置</param>
	/// <param name="coinNum"> ダイヤの数   </param>
	void CreateDiamond(std::vector<int> diamondPosX, std::vector<int>diamondPosY, int diamondNum);

	void Delete();
	void Update();
	void Draw();

	// アイテムが当たった場合その番号を返す
	void SetEraseNo(Item name, int eraseNo);

	bool isErase(Item name,int eraseNo);

private:
	// モデルハンドル
	int m_hItem[2];
	// 位置
	VECTOR m_pos;
	// サイズ
	VECTOR m_size;
	// 角度
	VECTOR m_rota;

	// コインの位置を一時的に受け取る
	std::vector<int>m_coinPosX;
	std::vector<int>m_coinPosY;

	// ダイヤの位置を一時的に受け取る
	std::vector<int>m_diamondPosX;
	std::vector<int>m_diamondPosY;

	// コインクラス
	std::vector<std::shared_ptr<ItemBase>> m_pCoin;
	std::vector<std::shared_ptr<ItemBase>> m_pDiamond;
	std::vector<bool>m_isErase;
};
