#include "UI.h"
#include <DxLib.h>

UI::UI() :
	m_score(0)
{
	for (int i = 0; i < static_cast<int>(Item::itemMaxNum); i++)
	{
		drawCount[i] = 60 * 3;
		m_isCharenge[i] = false;
	}
}

UI::~UI()
{

}

void UI::Update()
{
	// アイテムの数分
	// 現在のアイテムの数が最大数と同じになって
	// 文字を表示させる
	// カウントを進める
	// 一定時間表示させると消える
	for (int i = 0; i < static_cast<int>(Item::itemMaxNum); i++)
	{
		if (m_itemNum[i] == m_itemMaxNum[i] && drawCount[i] < 60 * 5)
		{
			m_isCharenge[i] = true;
			drawCount[i]++;
		}
		else
		{
			m_isCharenge[i] = false;				
		}
	}

	// 
	if (m_itemNum[static_cast<int>(Item::coin)] > 100 && drawCount[0] < 60 * 5)
	{
		m_isCharenge[0] = true;
		drawCount[0]++;
	}
	else
	{
		m_isCharenge[0] = false;
		
	}

	Score();
}

void UI::Draw()
{
	// アイテム個々の取得数
	DrawFormatString(200, 200, 0xffffff, "コイン取得数 = %d", m_itemNum[static_cast<int>(Item::coin)]);
	DrawFormatString(200, 230, 0xffffff, "ダイヤ取得数 = %d", m_itemNum[static_cast<int>(Item::diamond)]);
	// アイテム個々の得点
	DrawFormatString(200, 260, 0xffffff, "コイン得点 = %d", m_itemNum[static_cast<int>(Item::coin)] * 5);
	DrawFormatString(200, 290, 0xffffff, "ダイヤ得点 = %d", m_itemNum[static_cast<int>(Item::diamond)] * 5);
	// スコア
	DrawFormatString(200, 320, 0xffffff, "得点 = %d", m_score);
	// チャレンジ
	if(m_isCharenge[0])DrawFormatString(500, 200, 0xffffff, "コイン100枚達成した！");

	if(m_isCharenge[1])DrawFormatString(500, 230, 0xffffff, "コインを全て回収した！");
	if(m_isCharenge[2])DrawFormatString(500, 300, 0xffffff, "ダイヤを全て回収した！");
}

void UI::SetItemNum(Item name, int num)
{
	if (name == Item::coin)   m_itemNum[static_cast<int>(Item::coin)]    = num;
	if (name == Item::diamond)m_itemNum[static_cast<int>(Item::diamond)] = num;
}

void UI::SetItemMaxNum(Item name, int num)
{
	if (name == Item::coin)   m_itemMaxNum[static_cast<int>(Item::coin)]    = num;
	if (name == Item::diamond)m_itemMaxNum[static_cast<int>(Item::diamond)] = num;
}

void UI::Score()
{
	// スコア計算
	m_score = ((m_itemNum[static_cast<int>(Item::coin)] * 5 +
		m_itemNum[static_cast<int>(Item::diamond)] * 5)) * 15;
}
