#include "ButtonDrawer.h"
#include <DxLib.h>

namespace
{
	// 画像パス
	const char* kImagePath = "Data/Img/Controller.png";
	// 戻るボタン文字
	const char* kBackString = "　えーぼたんでとじる";
}

ButtonDrawer::ButtonDrawer():
	m_handle(-1),
	m_x(0),
	m_y(0)
{
}

ButtonDrawer::~ButtonDrawer()
{
	// メモリ解放
	DeleteGraph(m_handle);
}

void ButtonDrawer::Init()
{
	m_handle = LoadGraph(kImagePath);
}

void ButtonDrawer::Update(int x, int y)
{
	m_x = x;
	m_y = y;
}

void ButtonDrawer::Draw()
{
	// 枠表示
	DrawBox(m_x - 700 - 1, m_y - 300 - 1, m_x + 500 + 1, m_y + 300 + 1, 0x0000ff, false);
	DrawBox(m_x - 700, m_y - 300, m_x + 500, m_y + 300, 0xffffff, true);
	// 画像表示
	DrawRotaGraph(m_x, m_y,
		1,
		DX_PI_F * 180.0f,
		m_handle,
		true);
	// 説明表示
	DrawString(m_x + 100, m_y + 200, kBackString, 0x000000);
}
