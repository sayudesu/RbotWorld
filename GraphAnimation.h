#pragma once

// 画像アニメーション用クラス
class GraphAnimation
{
public:
	GraphAnimation();
	virtual ~GraphAnimation();

	/// <summary>
	/// 画像をアニメーションさせる
	/// </summary>
	/// <param name="imgX">      画像左上	        </param>
	/// <param name="imgSizeX">  画像１枚分の大きさ </param>
	/// <param name="imgNumMax"> 読み込ませる画像の </param>
	void Animation(int& imgX, int imgSizeX, int imgNumMax);
};

