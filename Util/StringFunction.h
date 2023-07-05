#pragma once
#include <vector>
#include <memory>

class AddString;

//////////////////
// テキスト設定 //
//////////////////
class StringFunction
{
public:
	StringFunction();
	virtual ~StringFunction();
	virtual void InitFont(const char* fontPath, const char* fontName);
	/// <summary>
	/// 文字を追加する
	/// </summary>
	/// <param name="x">座標</param>
	/// <param name="y">座標</param>
	/// <param name="text">文字</param>
	/// <param name="color">色</param>
	/// <param name="size">大きさ</param>
	/// <param name="font">フォントパス</param>
	virtual void Add(int x, int y, const char* text, int color, int size);

	virtual void AddStatic(int x, int y, const char* text,int num, int color, int size);
	/// <summary>
	/// 文字の位置変更
	/// </summary>
	/// <param name="addNo">変更したい文字番号</param>
	/// <param name="x">座標</param>
	/// <param name="y">座標</param>
	virtual void Update(int addNo,int x, int y);
	/// <summary>
	/// 描画させる
	/// </summary>
	/// <param name="addNo">描画してい文字番号</param>
	virtual void Draw(int addNo);
	virtual void DrawStatic(int addNo);

private:
	const char* m_fontName;
	const char* m_fontPathName;
	std::vector<std::shared_ptr<AddString>>m_pAddString;
};

//////////////////
// テキスト作成 //
//////////////////
class AddString
{
public:
	/// <summary>
	/// 文字を追加する
	/// </summary>
	/// <param name="x">座標</param>
	/// <param name="y">座標</param>
	/// <param name="text">文字</param>
	/// <param name="color">色</param>
	/// <param name="size">大きさ</param>
	/// <param name="font">フォントパス</param>//
	AddString(int x, int y, const char* text, int color, int size, const char* fontPath, const char* font);
	AddString(int x, int y, const char* text, int num, int color, int size, const char* fontPath, const char* font);
	virtual ~AddString();
	/// <summary>
	/// 文字の位置
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	virtual void UpdateCharenge(int x, int y);
	virtual void UpdateStatic(int x, int y);
	virtual void Draw();
	virtual void DrawStatic();
private:
	int m_x;
	int m_y;
	const char* m_text;
	int m_color;
	int m_size;
	const char* m_font;
	int m_fontHandle;

	int m_xStatic;
	int m_yStatic;
	int m_num;
};

