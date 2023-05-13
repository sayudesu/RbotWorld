#pragma once
#include "Util/Vec2.h"
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
	virtual void DrawDef(Vec2 pos,const char* text,int size,int color = 0xffffff);//文字を表示

	// 揺れながら上に文字が上がって行き徐々に消える
	// 座標、文字、サイズ、上昇する速さ、色(何も色を指定しないと白)
	virtual void DrawUp(Vec2 pos, const char* text, int size,float speedUp, int color = 0xffffff);
private:
	// 文字の位置
	Vec2 m_posUp;

	int m_hDef;
	int m_hTextUp;

	// 一度だけの処理
	bool m_isTempDef;
	bool m_isTempUp;
};

