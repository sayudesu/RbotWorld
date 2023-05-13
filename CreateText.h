#pragma once

/// <summary>
/// 文字を描画させるクラス
/// </summary>
class CreateText
{
public:
	CreateText();
	virtual ~CreateText();

	// シンプルなテキスト表示
	// 座標、文字、サイズ、色(何も色を指定しないと白)
	virtual void DrawDef(int x, int y,const char* text,int size,int color = 0xffffff);//文字を表示

	// 揺れながら上に文字が上がって行き徐々に消える
	// 座標、文字、サイズ、色(何も色を指定しないと白)
	virtual void DrawUp(int x, int y, const char* text, int size, int color = 0xffffff);
private:
	// 
	int m_stringUpX;
	int m_stringUpY;
	//
	bool m_isTempPos;
};

