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
	// 一度だけ保存
	if (!m_isTempDef)
	{
		m_hDef = CreateFontToHandle(NULL, size, -1);
		m_isTempDef = true;
	}

	// 表示
	DrawStringToHandle(pos.x, pos.y, text, color, m_hDef);
}

void CreateText::DrawUp(Vec3 pos, const char* text, int size,float speedUp, int color)
{
	// 一度だけ保存
	if (!m_isTempUp)
	{
		m_posUp.x = pos.x;
		m_posUp.y = pos.y;
		m_hTextUp = CreateFontToHandle(NULL, size, -1);
		m_isTempUp = true;
	}

	// 上昇
	m_posUp.y -= speedUp;

	m_posUp.x += GetRand(3) + 1;
	m_posUp.x -= GetRand(3) + 1;

	// 画面外に出るまで表示
	if (m_posUp.y > 0 - size)
	{
		// 表示
		DrawStringToHandle(m_posUp.x, m_posUp.y, text, color, m_hTextUp);
	}
}
