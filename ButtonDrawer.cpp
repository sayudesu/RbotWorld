#include "ButtonDrawer.h"
#include <DxLib.h>

namespace
{
	// �摜�p�X
	const char* kImagePath = "Data/Img/Controller.png";
	// �߂�{�^������
	const char* kBackString = "�@���[�ڂ���łƂ���";
}

ButtonDrawer::ButtonDrawer():
	m_handle(-1),
	m_x(0),
	m_y(0)
{
}

ButtonDrawer::~ButtonDrawer()
{
	// ���������
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
	// �g�\��
	DrawBox(m_x - 700 - 1, m_y - 300 - 1, m_x + 500 + 1, m_y + 300 + 1, 0x0000ff, false);
	DrawBox(m_x - 700, m_y - 300, m_x + 500, m_y + 300, 0xffffff, true);
	// �摜�\��
	DrawRotaGraph(m_x, m_y,
		1,
		DX_PI_F * 180.0f,
		m_handle,
		true);
	// �����\��
	DrawString(m_x + 100, m_y + 200, kBackString, 0x000000);
}
