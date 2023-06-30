#include "GraphAnimation.h"

GraphAnimation::GraphAnimation()
{
}

GraphAnimation::~GraphAnimation()
{
}

void GraphAnimation::Animation(int& imgX, int imgSizeX, int imgNumMax)
{
	// 現在の画像が画像の右端より小さかったら画像表示位置を右にずらす
	// 右端まで到達したら画像描画をしない
	if (imgX < imgSizeX * imgNumMax)
	{
		imgX += imgSizeX;
	}
}
