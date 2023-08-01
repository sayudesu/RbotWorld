#include "Achievement.h"
#include <DxLib.h>
#include <cassert>

//////////////////
// �e�L�X�g�ݒ� //
//////////////////
Achievement::Achievement():
	m_fontName(""),
	m_fontPathName("")
{

}

Achievement::~Achievement()
{
	for (auto& test : m_pAddString)
	{
		test.reset();
	}
}

void Achievement::InitFont(const char* fontPath,const char* fontName)
{
	m_fontPathName = fontPath;
	m_fontName = fontName;
}

void Achievement::Add(int x, int y, const char* text, int color, int size)
{
	// �Ăяo���ꂽ�񐔕��C���X�^���X�쐬
	m_pAddString.push_back(std::make_shared<AddString>(x,y,text,color,size, m_fontPathName, m_fontName));
}

void Achievement::Update(int addNo,int x,int y)
{
	// �z��ԍ��Ŏw�肵�������̈ʒu��ς���
	m_pAddString[addNo]->UpdateCharenge(x, y);
}

void Achievement::Draw(int addNo)
{
	// �z��ԍ��Ŏw�肵���ꏊ��\�����Ă���
	m_pAddString[addNo]->Draw();
}


StringStatic::StringStatic() :
	m_fontName(""),
	m_fontPathName("")
{
}

StringStatic::~StringStatic()
{
	
}

void StringStatic::InitFont(const char* fontPath, const char* fontName)
{
	m_fontPathName = fontPath;
	m_fontName = fontName;
}

void StringStatic::AddStatic(int x, int y, const char* text, int num, int color, int size)
{
	// �Ăяo���ꂽ�񐔕��C���X�^���X�쐬 
	m_pAddString.push_back(std::make_shared<AddString>(x, y, text, num,color, size, m_fontPathName, m_fontName));
}

void StringStatic::UpdateStatic(int addNo,int x ,int y,int num)
{
	m_pAddString[addNo]->UpdateStatic(x,y,num);
}

void StringStatic::DrawStatic(int addNo)
{
	// �z��ԍ��Ŏw�肵���ꏊ��\�����Ă���
	m_pAddString[addNo]->DrawStatic();
}

//////////////////
// �e�L�X�g�쐬 //
//////////////////
AddString::AddString(int x, int y, const char* text, int color, int size, const char* fontPath, const char* font) :
	m_x(x),
	m_y(y),
	m_text(text),
	m_color(color),
	m_size(size),
	m_font(font),
	m_fontHandle(-1),
	m_num(0)
{

	// �t�H���g�n���h���f�[�^�i�[
	m_fontHandle = CreateFontToHandle(m_font, m_size, 3);
	assert(m_fontHandle != -1);
}

AddString::AddString(int x, int y, const char* text,int num, int color, int size, const char* fontPath, const char* font) :
	m_x(x),
	m_y(y),
	m_text(text),
	m_color(color),
	m_size(size),
	m_font(font),
	m_fontHandle(-1),
	m_num(num)
{

	// �t�H���g�n���h���f�[�^�i�[
	m_fontHandle = CreateFontToHandle(m_font, m_size, 3);
	assert(m_fontHandle != -1);
}

AddString::~AddString()
{
	// �t�H���g�n���h���f�[�^�̃��������
	DeleteFontToHandle(m_fontHandle);

}

void AddString::UpdateCharenge(int x,int y)
{
	m_x = x;
	m_y = y;
}

void AddString::Draw()
{
	// �����`��
	DrawStringToHandle(m_x, m_y, m_text, m_color, m_fontHandle);	
}

void AddString::UpdateStatic(int x,int y,int num)
{
	m_x = x;
	m_y = y;
	m_num = num;
}

void AddString::DrawStatic()
{
	// �����t�������`��
	DrawFormatStringToHandle(m_x, m_y, m_color, m_fontHandle, m_text, m_num);
}
