#pragma once
#include "Util/Vec3.h"
#include <vector>
#include <memory>
class Text;
/// <summary>
/// 文字を描画させるクラス
/// </summary>
class CreateText
{
public:
	CreateText();
	virtual ~CreateText();

	/// <summary>
	/// テキストの数分のTextクラスをインスタンスを作成する
	/// </summary>
	/// <param name="x">    位置  </param>
	/// <param name="y">    位置  </param>
	/// <param name="text"> 文字  </param>
	/// <param name="color">色	  </param>
	/// <param name="size"> サイズ</param>
	/// <param name="frame">枠　　</param>
	void Add(int x,int y,const char* text,int color,int size, bool frame);
	void Update();
	/// <summary>
	/// テキストを描画する
	/// </summary>
	void Draw();
private:
	std::vector<std::shared_ptr<Text>> m_pText;
};

class Text
{
public:
	/// <summary>
	/// テキスト作成
	/// </summary>
	/// <param name="x">    位置  </param>
	/// <param name="y">    位置  </param>
	/// <param name="text"> 文字  </param>
	/// <param name="color">色    </param>
	/// <param name="size"> サイズ</param>
	/// <param name="frame">枠　　</param>
	Text(int x, int y, const char* text, int color, int size,bool frame);
	virtual ~Text();

	void Draw();
private:
	// 位置
	int m_x;
	int m_y;
	// 文字
	const char* m_text;
	// 色
	int m_color;
	// 枠を表示するかどうか
	bool m_isFrame;
	// 文字データ
	int m_fontHandle;
};

