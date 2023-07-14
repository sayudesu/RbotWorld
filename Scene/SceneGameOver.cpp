#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "Util/game.h"
#include "Util/Pad.h"


SceneGameOver::SceneGameOver():
	m_isChangeScene(false)
{
}

SceneGameOver::~SceneGameOver()
{
}

SceneBase* SceneGameOver::Update()
{
	// ���̃V�[���Ɉڍs���邩�ǂ���
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isChangeScene = true;
		m_isSliderOpen = true;
	}

	// �X���C�h����ăV�[����؂�ւ���
	if (m_isChangeScene)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneTitle;	
		}
	}

	// �X���C�h���J����
	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneGameOver::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);

	// �X���C�h��`��
	SceneBase::DrawSliderDoor();
}
