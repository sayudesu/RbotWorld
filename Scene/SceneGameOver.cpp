#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "SceneDebug.h"

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
