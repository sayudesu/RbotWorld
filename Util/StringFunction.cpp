#include "StringFunction.h"
#include <DxLib.h>
#include <cassert>

//////////////////
// �e�L�X�g�ݒ� //
//////////////////
StringFunction::StringFunction():
	m_fontName("")
{

}

StringFunction::~StringFunction()
{
	for (auto& test : m_pAddString)
	{
		test.reset();
	}
}

void StringFunction::InitFont(const char* fontPath,const char* fontName)
{
	m_fontPathName = fontPath;
	m_fontName = fontName;
}

void StringFunction::Add(int x, int y, const char* text, int color, int size)
{
	// �Ăяo���ꂽ�񐔕��C���X�^���X�쐬
	m_pAddString.push_back(std::make_shared<AddString>(x,y,text,color,size, m_fontPathName, m_fontName));
}

void StringFunction::AddStatic(int x, int y, const char* text,int num, int color, int size)
{
	// �Ăяo���ꂽ�񐔕��C���X�^���X�쐬 
	m_pAddString.push_back(std::make_shared<AddString>(x, y, text, color, size,num, m_fontPathName, m_fontName));
}

void StringFunction::Update(int addNo,int x,int y)
{
	// �z��ԍ��Ŏw�肵�������̈ʒu��ς���
	m_pAddString[addNo]->UpdateCharenge(x, y);
}

void StringFunction::Draw(int addNo)
{
	// �z��ԍ��Ŏw�肵���ꏊ��\�����Ă���
	m_pAddString[addNo]->Draw();
}

void StringFunction::DrawStatic(int addNo)
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

	LPCTSTR font_path = reinterpret_cast<LPCTSTR>(fontPath); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	//�t�H���g�̓ǂݍ��݂����s������ǂݍ��ݎ��s���o��
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	// �t�H���g�n���h���f�[�^�i�[
	m_fontHandle = CreateFontToHandle(m_font, m_size, 3);
	assert(m_fontHandle != -1);
}

AddString::AddString(int x, int y, const char* text,int num, int color, int size, const char* fontPath, const char* font) :
	m_xStatic(x),
	m_yStatic(y),
	m_text(text),
	m_color(color),
	m_size(size),
	m_font(font),
	m_fontHandle(-1),
	m_num(num)
{

	LPCTSTR font_path = reinterpret_cast<LPCTSTR>(fontPath); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	//�t�H���g�̓ǂݍ��݂����s������ǂݍ��ݎ��s���o��
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

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

void AddString::UpdateStatic(int x, int y)
{
	m_xStatic = x;
	m_yStatic = y;
}

void AddString::Draw()
{
	// �����`��
	DrawStringToHandle(m_x, m_y, m_text, m_color, m_fontHandle);	
}

void AddString::DrawStatic()
{
	// �����t�������`��
	DrawFormatStringToHandle(m_xStatic, m_yStatic, m_color, m_fontHandle, "%d", m_num);
}
