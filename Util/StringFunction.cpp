#include "StringFunction.h"
#include <DxLib.h>

//////////////////
// �e�L�X�g�ݒ� //
//////////////////
StringFunction::StringFunction()
{

}

StringFunction::~StringFunction()
{
	for (auto& test : m_pAddString)
	{
		test.reset();
	}
}

void StringFunction::Add(int x, int y, const char* text, int color, int size, const char* font)
{
	// �Ăяo���ꂽ�񐔕��C���X�^���X�쐬
	m_pAddString.push_back(std::make_shared<AddString>(x,y,text,color,size,font));
}

void StringFunction::Update(int addNo,int x,int y)
{
	m_pAddString[addNo]->Update(x, y);
}

void StringFunction::Draw(int addNo)
{
	m_pAddString[addNo]->Draw();
}

//////////////////
// �e�L�X�g�쐬 //
//////////////////
AddString::AddString(int x, int y, const char* text, int color, int size, const char* font) :
	m_x(x),
	m_y(y),
	m_text(text),
	m_color(color),
	m_size(size),
	m_font(font),
	m_fontHandle(-1)
{
	LPCTSTR font_path = reinterpret_cast<LPCTSTR>("Data/Fonts/851letrogo_007.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	//�t�H���g�̓ǂݍ��݂����s������ǂݍ��ݎ��s���o��
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	// �t�H���g�n���h���f�[�^�i�[
	m_fontHandle = CreateFontToHandle("851���g���S", m_size, 3);
}

AddString::~AddString()
{
	// �t�H���g�n���h���f�[�^�̃��������
	DeleteFontToHandle(m_fontHandle);
}

void AddString::Update(int x,int y)
{
	m_x = x;
	m_y = y;
}

void AddString::Draw()
{
	// �`��
	DrawStringToHandle(m_x, m_y, m_text, m_color, m_fontHandle);
}
