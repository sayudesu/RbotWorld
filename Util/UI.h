#pragma once
#include "ItemName.h"
#include "Vec3.h"

#define DEBUG_ false;

namespace
{
	// チャレンジの数
	constexpr int kCharengeNum = 2;
	// アイテムの最大値
	constexpr int kItemNum = static_cast<int>(Item::itemMaxNum);
}

class Achievement;
class StringStatic;


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
	// チャレンジ-----------------------------------
	void ItemMaxCharenge();// アイテムマックスチャレンジ	

	// スコア用-------------------------------------
	void Score();// スコアの計算
private:
	// アイテム管理----------------------------------
	int m_itemNum[kItemNum];// 現在のアイテム取得数
	int m_itemMaxNum[kItemNum];// 最大アイテム数

	// チャレンジ用---------------------------------
	Vec3 m_charengePos[kCharengeNum];// 位置
	int m_drawCount[kCharengeNum];// 描画時間カウント
	int m_charengeColor[kCharengeNum];// 色指定
	bool m_isCharenge[kCharengeNum];// 文字描画処理
	bool m_isCharengeDraw[kCharengeNum];// 文字を描画
	const char* m_charengeString[kCharengeNum];// 文字

	// スコア用-------------------------------------
	int m_score;

	// 文字描画クラス-------------------------------
	Achievement* m_pString;
	StringStatic* m_pStringStatic;

	//----------------------------------------------

#if DEBUG_
	Vec3 m_scorePos[kItemNum];// 位置
	const char* m_scoreString[kItemNum];// 文字
#endif
};

