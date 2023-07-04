#include "StringFunction.h"
#include <DxLib.h>

//////////////////
// テキスト設定 //
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
	// 呼び出された回数分インスタンス作成
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
// テキスト作成 //
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
	LPCTSTR font_path = reinterpret_cast<LPCTSTR>("Data/Fonts/851letrogo_007.ttf"); // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	//フォントの読み込みが失敗したら読み込み失敗を出す
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	// フォントハンドルデータ格納
	m_fontHandle = CreateFontToHandle("851レトロゴ", m_size, 3);
}

AddString::~AddString()
{
	// フォントハンドルデータのメモリ解放
	DeleteFontToHandle(m_fontHandle);
}

void AddString::Update(int x,int y)
{
	m_x = x;
	m_y = y;
}

void AddString::Draw()
{
	// 描画
	DrawStringToHandle(m_x, m_y, m_text, m_color, m_fontHandle);
}
