#include "StringFunction.h"
#include <DxLib.h>
#include <cassert>

//////////////////
// テキスト設定 //
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
	// 呼び出された回数分インスタンス作成
	m_pAddString.push_back(std::make_shared<AddString>(x,y,text,color,size, m_fontPathName, m_fontName));
}

void StringFunction::AddStatic(int x, int y, const char* text,int num, int color, int size)
{
	// 呼び出された回数分インスタンス作成 
	m_pAddString.push_back(std::make_shared<AddString>(x, y, text, color, size,num, m_fontPathName, m_fontName));
}

void StringFunction::Update(int addNo,int x,int y)
{
	// 配列番号で指定した文字の位置を変える
	m_pAddString[addNo]->UpdateCharenge(x, y);
}

void StringFunction::Draw(int addNo)
{
	// 配列番号で指定した場所を表示している
	m_pAddString[addNo]->Draw();
}

void StringFunction::DrawStatic(int addNo)
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

	LPCTSTR font_path = reinterpret_cast<LPCTSTR>(fontPath); // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	//フォントの読み込みが失敗したら読み込み失敗を出す
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	// フォントハンドルデータ格納
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

	LPCTSTR font_path = reinterpret_cast<LPCTSTR>(fontPath); // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	//フォントの読み込みが失敗したら読み込み失敗を出す
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

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

void AddString::UpdateStatic(int x, int y)
{
	m_xStatic = x;
	m_yStatic = y;
}

void AddString::Draw()
{
	// 文字描画
	DrawStringToHandle(m_x, m_y, m_text, m_color, m_fontHandle);	
}

void AddString::DrawStatic()
{
	// 数字付き文字描画
	DrawFormatStringToHandle(m_xStatic, m_yStatic, m_color, m_fontHandle, "%d", m_num);
}
