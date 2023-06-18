#include "CreateText.h"
#include <DxLib.h>

//////////////////////
// CreateText�N���X //
//////////////////////
CreateText::CreateText()
{

}

CreateText::~CreateText()
{

}

void CreateText::Add(int x, int y, const char* text, int color, int size,bool frame)
{
	// �C���X�^���X���쐬
	m_pText.push_back(std::make_shared<Text>(x,y,text,color,size,frame));
}

void CreateText::Update()
{
	
}

void CreateText::Draw()
{
	for (auto& text : m_pText)
	{
		text->Draw();
	}
}

////////////////
// Text�N���X //
////////////////
Text::Text(int x, int y, const char* text, int color, int size, bool frame) :
	m_x(x),
	m_y(y),
	m_text(text),
	m_color(color),
	m_isFrame(frame)
{
	// �t�H���g�f�[�^���쐬
	m_fontHandle = CreateFontToHandle(NULL, size, 3);
}

Text::~Text()
{
}

void Text::Draw()
{
	if (m_isFrame)
	{
		DrawBox(m_x - 1, m_y - 1, m_x + 500 + 1, m_y + 50 + 1, 0xff0000, true);
		DrawBox(m_x, m_y, m_x + 500, m_y + 50, 0xffffff, true);
	}
	
	// �t�H���g�f�[�^���g��������`��
	DrawStringToHandle(m_x, m_y, m_text, m_color, m_fontHandle);
}
