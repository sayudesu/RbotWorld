#include "SceneBase.h"
#include <DxLib.h>
#include "game.h"

namespace
{
	// フェード速度
	constexpr int kFadeSpeed = 8;

	constexpr int kSliderSpeed = 15;
}

SceneBase::SceneBase()
{
	// 初期設定はフェードアウト状態
	m_fadeColor = GetColor(0, 0, 0);
	m_fadeBright = 255;
	m_fadeSpeed = -kFadeSpeed;

	// スライダー関連
	m_hDoor = LoadGraph("Data/Img/DoorH.png");
	m_sliderPos = 0;
	m_pos = { 0.0f,0.0f ,0.0f };
	m_isSliderOpen = false;
}

void SceneBase::UpdateFade()
{
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		if (m_fadeSpeed > 0)
		{
			m_fadeSpeed = 0;
		}
	}
	if (m_fadeBright <= 0)
	{
		m_fadeBright = 0;
		if (m_fadeSpeed < 0)
		{
			m_fadeSpeed = 0;
		}
	}
}

void SceneBase::DrawFade() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeBright);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool SceneBase::IsFadingIn() const
{
	if (m_fadeSpeed < 0)	return true;
	return false;
}

bool SceneBase::IsFadingOut() const
{
	if (m_fadeSpeed > 0)	return true;
	return false;
}

void SceneBase::StartFadeOut()
{
	m_fadeSpeed = kFadeSpeed;
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
