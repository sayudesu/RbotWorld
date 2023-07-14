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
	// 次のシーンに移行するかどうか
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isChangeScene = true;
		m_isSliderOpen = true;
	}

	// スライドを閉じてシーンを切り替える
	if (m_isChangeScene)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneTitle;	
		}
	}

	// スライドを開ける
	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneGameOver::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);

	// スライドを描画
	SceneBase::DrawSliderDoor();
}
