#include "SceneBase.h"
#include <DxLib.h>
#include "game.h"

namespace
{
	// �t�F�[�h���x
	constexpr int kFadeSpeed = 8;

	constexpr int kSliderSpeed = 15;
}

SceneBase::SceneBase()
{
	// �����ݒ�̓t�F�[�h�A�E�g���
	m_fadeColor = GetColor(0, 0, 0);
	m_fadeBright = 255;
	m_fadeSpeed = -kFadeSpeed;

	// �X���C�_�[�֘A
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
	// �X���C�h���J����
	if (!open)
	{
		if (SceneBase::UpdateSliderOpen())
		{
			open = true;
		}
	}
}

// �X���C�h���J����Ƃ�
bool SceneBase::UpdateSliderOpen()
{
	// ��ʂ̒[�ŃX���C�h���~�߂�
	if (m_sliderPos < Game::kScreenWidth / 2)
	{
		m_sliderPos += kSliderSpeed;
		return false;
	}
	return true;
}

// �X���C�h�����Ƃ�
bool SceneBase::UpdateSliderClose()
{
	if (m_sliderPos > 0)
	{
		m_sliderPos -= kSliderSpeed;
		return false;
	}

	return true;
}

// �X���C�h�֘A
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
