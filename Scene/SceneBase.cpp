#include "SceneBase.h"
#include <DxLib.h>
#include "game.h"

namespace
{
	// スライドスピード
	constexpr int kSliderSpeed = 15;
}

SceneBase::SceneBase()
{
	// スライダー関連
	m_hDoor = LoadGraph("Data/Img/DoorH.png");
	m_sliderPos = 0;
	m_pos = { 0.0f,0.0f ,0.0f };
	m_isSliderOpen = false;
}

void SceneBase::UpdateSlider(bool &open)
{
	// スライドを開ける
	if (!open)
	{
		if (SceneBase::UpdateSliderOpen())
		{
			open = true;
		}
	}
}

// スライドを開けるとき
bool SceneBase::UpdateSliderOpen()
{
	// 画面の端でスライドを止める
	if (m_sliderPos < Game::kScreenWidth / 2)
	{
		m_sliderPos += kSliderSpeed;
		return false;
	}
	return true;
}

// スライドを閉じるとき
bool SceneBase::UpdateSliderClose()
{
	if (m_sliderPos > 0)
	{
		m_sliderPos -= kSliderSpeed;
		return false;
	}

	return true;
}

// スライド関連
void SceneBase::DrawSliderDoor()
{
	DrawRotaGraph(Game::kScreenWidth / 2 - ((Game::kScreenWidth / 2) / 2) - m_sliderPos,
		Game::kScreenHeight / 2,
		1, DX_PI_F * 180.0f,
		m_hDoor, true, false);

	DrawRotaGraph(Game::kScreenWidth / 2 + ((Game::kScreenWidth / 2) / 2) + m_sliderPos,
		Game::kScreenHeight / 2,
		1, DX_PI_F * 180.0f,
		m_hDoor, true, true);
}
