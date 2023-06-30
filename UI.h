#pragma once
#include "ItemName.h"

class UI
{
public:
	UI();
	virtual ~UI();

	// 更新処理
	void Update();
	// 描画
	void Draw();
	/// <summary>
	/// アイテムを何個取得しているか
	/// </summary>
	/// <param name="name">アイテムの名前</param>
	/// <param name="num">アイテムの数</param>
	void SetItemNum(Item  name, int num);
	/// <summary>
	/// アイテムの最大数
	/// </summary>
	/// <param name="name">アイテムの名前</param>
	/// <param name="num">アイテム最大の数</param>
	void SetItemMaxNum(Item  name, int num);

	// スコアを返す
	int GetScore() { return m_score; }
private:
	void Score();
private:
	// 現在のアイテム取得数
	int m_itemNum[static_cast<int>(Item::itemMaxNum)];
	// 最大アイテム数
	int m_itemMaxNum[static_cast<int>(Item::itemMaxNum)];
	// スコア用
	int m_score;
	// 描画処理関係
	int drawCount[3];
	bool m_isCharenge[3];
};

