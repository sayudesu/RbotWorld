#include "SceneGameClear.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "game.h"
#include "Util/Pad.h"

SceneGameClear::SceneGameClear(int score):
	m_score(score)
{
}

SceneGameClear::~SceneGameClear()
{
}

SceneBase* SceneGameClear::Update()
{

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return new SceneTitle;
	}

	return this;
}

void SceneGameClear::Draw()
{
	DrawFormatString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 0xffffff, "今回のスコア！＜%d＞", m_score);
}
