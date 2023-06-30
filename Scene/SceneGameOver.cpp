#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "SceneMain.h"

SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

SceneBase* SceneGameOver::Update()
{
	return new SceneTitle;
}

void SceneGameOver::Draw()
{
}
