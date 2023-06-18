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

	/// <summary>
	/// パッド入力の更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// テキストを描画する
	/// </summary>
	void Draw();

	/// <summary>
	/// 選択した番号
	/// </summary>
	/// <returns>何番目を選択しかたを返す</returns>
	int SelectNo() { return selectNo; }
private:
	std::vector<std::shared_ptr<Text>> m_pText;
	// 選択したかどうか
	bool m_isSelect;
	// 選択肢の数
	int selectNum;
	int selectNow;
	int selectNo;
	// 円の半径
	int selectRad;
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

	void SetSelectFrame(bool isSelect);
	void SetSelectRadius(int rad);
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
	// 選択してるかどうか
	bool m_isSelect;
	// 選択後のエフェクト円の大きさ
	int m_rad;
};

