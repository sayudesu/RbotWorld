#include "UI.h"
#include <DxLib.h>

UI::UI() :
	m_coinNum(0),
	m_diamondNum(0),
	m_coinMaxNum(0),
	m_diamondMaxNum(0)
{
	for (int i = 0; i < 3; i++)
	{
		drawCount[i] = 60 * 3;
		m_isCoinCharenge[i] = false;
	}
}

UI::~UI()
{

}

void UI::Update()
{
	if (m_coinNum > 100 && drawCount[0] < 60 * 5)
	{
		m_isCoinCharenge[0] = true;
		drawCount[0]++;
	}
	else
	{
		m_isCoinCharenge[0] = false;
		drawCount[0] = 0;
	}

	if (m_coinNum == m_coinMaxNum && drawCount[1] < 60 * 5)
	{
		m_isCoinCharenge[1] = true;
		drawCount[1]++;
	}
	else
	{
		m_isCoinCharenge[1] = false;
		drawCount[1] = 0;
	}

	if (m_diamondNum == m_diamondMaxNum && drawCount[2] < 60 * 5)
	{
		m_isCoinCharenge[2] = true;
		drawCount[2]++;
	}
	else
	{
		m_isCoinCharenge[2] = false;
		drawCount[2] = 0;
	}
}

void UI::Draw()
{
	DrawFormatString(200, 200, 0xffffff, "コイン取得数 = %d", m_coinNum);
	DrawFormatString(200, 300, 0xffffff, "ダイヤ取得数 = %d", m_diamondNum);

	if(m_isCoinCharenge[0])DrawFormatString(500, 200, 0xffffff, "コイン100枚達成した！");
	if(m_isCoinCharenge[1])DrawFormatString(500, 200, 0xffffff, "コインを全て回収した！");
	if(m_isCoinCharenge[2])DrawFormatString(500, 200, 0xffffff, "ダイヤを全て回収した！");
}

void UI::SetItemNum(Item name, int num)
{
	if (name == Item::coin)m_coinNum = num;
	if (name == Item::diamond)m_diamondNum = num;
}

void UI::SetItemMaxNum(Item name, int num)
{
	if (name == Item::coin)m_coinMaxNum = num;
	if (name == Item::diamond)m_diamondMaxNum = num;
}
