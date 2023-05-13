#include "SceneTitle.h"
#include "SceneDebug.h"
#include <DxLib.h>
#include "CreateText.h"
#include "game.h"
#include "Pad.h"

namespace
{
	const char* const kTextTitle = "[RobotWorld]";
	const char* const kTextStart = "「 A 」ボタンで開始！";

	const char* const kTextTest = "揺れながら文字を上昇して消える～";
}

SceneTitle::SceneTitle():
	m_pText(nullptr)
{
	m_pText = new CreateText;
}

SceneTitle::~SceneTitle()
{
	delete m_pText;
}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return(new SceneDebug);
	}

	return this;
}

void SceneTitle::Draw()
{
	int x = Game::kScreenWidth / 2 - 250;
	int y = Game::kScreenHeight / 2 - 300;
	int size = 100;
	int color = 0xffff00;

	m_pText->DrawDef(x,y,
		kTextTitle, size, color);

	x = Game::kScreenWidth / 2 - 200;
	y = Game::kScreenHeight / 2 + 300;
	size = 32;
	color = 0xff0000;

	m_pText->DrawDef(x, y,
		kTextStart, size, color);

	x = Game::kScreenWidth / 2 - 200;
	y = Game::kScreenHeight / 2 + 300;
	size = 32;
	color = 0xff0000;

	m_pText->DrawUp(x, y,
		kTextTest, size, color);
}
