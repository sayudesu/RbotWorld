#include "CreateText.h"
#include <DxLib.h>

CreateText::CreateText():
	m_posUp(0.0f, 0.0f, 0.0f),
	m_isTempDef(false),
	m_isTempUp(false)
{

}

CreateText::~CreateText()
{
	SetFontSize(17);
}

void CreateText::DrawDef(Vec3 pos,const char* text, int size,int color)
{
	// ��x�����ۑ�
	if (!m_isTempDef)
	{
		m_hDef = CreateFontToHandle(NULL, size, -1);
		m_isTempDef = true;
	}

	// �\��
	DrawStringToHandle(pos.x, pos.y, text, color, m_hDef);
}

void CreateText::DrawUp(Vec3 pos, const char* text, int size,float speedUp, int color)
{
	// ��x�����ۑ�
	if (!m_isTempUp)
	{
		m_posUp.x = pos.x;
		m_posUp.y = pos.y;
		m_hTextUp = CreateFontToHandle(NULL, size, -1);
		m_isTempUp = true;
	}

	// �㏸
	m_posUp.y -= speedUp;

	m_posUp.x += GetRand(3) + 1;
	m_posUp.x -= GetRand(3) + 1;

	// ��ʊO�ɏo��܂ŕ\��
	if (m_posUp.y > 0 - size)
	{
		// �\��
		DrawStringToHandle(m_posUp.x, m_posUp.y, text, color, m_hTextUp);
	}
}
