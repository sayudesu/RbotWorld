#include "Achievement.h"
#include <DxLib.h>
#include <cassert>

//////////////////
// テキスト設定 //
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
	// 呼び出された回数分インスタンス作成
	m_pAddString.push_back(std::make_shared<AddString>(x,y,text,color,size, m_fontPathName, m_fontName));
}

void Achievement::Update(int addNo,int x,int y)
{
	// 配列番号で指定した文字の位置を変える
	m_pAddString[addNo]->UpdateCharenge(x, y);
}

void Achievement::Draw(int addNo)
{
	// 配列番号で指定した場所を表示している
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
	// 呼び出された回数分インスタンス作成 
	m_pAddString.push_back(std::make_shared<AddString>(x, y, text, num,color, size, m_fontPathName, m_fontName));
}

void StringStatic::UpdateStatic(int addNo,int x ,int y,int num)
{
	m_pAddString[addNo]->UpdateStatic(x,y,num);
}

void StringStatic::DrawStatic(int addNo)
{
	// 配列番号で指定した場所を表示している
	m_pAddString[addNo]->DrawStatic();
}

//////////////////
// テキスト作成 //
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

	// フォントハンドルデータ格納
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

	// フォントハンドルデータ格納
	m_fontHandle = CreateFontToHandle(m_font, m_size, 3);
	assert(m_fontHandle != -1);
}

AddString::~AddString()
{
	// フォントハンドルデータのメモリ解放
	DeleteFontToHandle(m_fontHandle);

}

void AddString::UpdateCharenge(int x,int y)
{
	m_x = x;
	m_y = y;
}

void AddString::Draw()
{
	// 文字描画
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
	// 数字付き文字描画
	DrawFormatStringToHandle(m_x, m_y, m_color, m_fontHandle, m_text, m_num);
}
