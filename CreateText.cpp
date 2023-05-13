#include "CreateText.h"
#include <DxLib.h>

CreateText::CreateText():
	m_stringUpX(0),
	m_stringUpY(0),
	m_isTempPos(false)
{
}

CreateText::~CreateText()
{
	SetFontSize(17);
}

void CreateText::DrawDef(int x, int y,const char* text, int size,int color)
{
	SetFontSize(size);
	DrawString(x, y, text, color);
}

void CreateText::DrawUp(int x, int y, const char* text, int size, int color)
{
	// ��x�����ۑ�
	if (!m_isTempPos)
	{
		m_stringUpX = x;
		m_stringUpY = y;
		m_isTempPos = true;
	}

	// �㏸
	m_stringUpY -= 8;

	m_stringUpX += GetRand(3) + 1;
	m_stringUpX -= GetRand(3) + 1;

	// ��ʊO�ɏo��܂ŕ\��
	if (m_stringUpY > 0)
	{
		SetFontSize(size);
		DrawString(m_stringUpX, m_stringUpY, text, color);
	}
}
