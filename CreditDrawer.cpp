#include "CreditDrawer.h"
#include <DxLib.h>

CreditDrawer::CreditDrawer():
	m_handle(0),
	m_x(0),
	m_y(0)
{
}

CreditDrawer::~CreditDrawer()
{
	DeleteGraph(m_handle);
}

void CreditDrawer::Init()
{
	m_handle = LoadGraph("Data/Img/Credit.png");
}

void CreditDrawer::Update(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CreditDrawer::Draw()
{
	// ˜g•\Ž¦
	DrawBox(m_x - 700 - 1, m_y - 400 - 1, m_x + 700 + 1, m_y + 400 + 1, 0x0000ff, false);
	DrawBox(m_x - 700, m_y - 400, m_x + 700, m_y + 400, 0xffffff, true);
	// ‰æ‘œ•\Ž¦
	DrawRotaGraph(m_x, m_y,
		1,
		DX_PI_F * 180.0f,
		m_handle,
		true);
}
