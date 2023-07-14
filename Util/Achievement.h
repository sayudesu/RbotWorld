#pragma once
#include <vector>
#include <memory>

class AddString;

////////////////////
// 実績描画クラス //
/////////////////////
class Achievement
{
public:
	Achievement();
	virtual ~Achievement();
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

private:
	const char* m_fontName;
	const char* m_fontPathName;
	std::vector<std::shared_ptr<AddString>>m_pAddString;
};

class StringStatic
{
public:
	StringStatic();
	virtual ~StringStatic();
	// フォントの初期化(まだここでは初期はしていない別の場所でしている)
	virtual void InitFont(const char* fontPath, const char* fontName);
	// 文字を追加する
	virtual void AddStatic(int x, int y, const char* text, int num, int color, int size);
	// 文字位置の変更、描画したい数字を入力(文字の位置は変更できないようにする)
	virtual void UpdateStatic(int addNo, int x, int y, int num);
	// 描画
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
	virtual void Draw();

	// 動きが無い文字用関数
	virtual void UpdateStatic(int x, int y, int num);
	virtual void DrawStatic();
private:
	int m_x;
	int m_y;
	const char* m_text;
	int m_color;
	int m_size;
	const char* m_font;
	int m_fontHandle;

	int m_num;
};

