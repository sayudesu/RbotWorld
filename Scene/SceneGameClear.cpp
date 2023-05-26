#include "SceneGameClear.h"
#include "SceneTitle.h"
#include "SceneDebug.h"

SceneGameClear::SceneGameClear()
{
}

SceneGameClear::~SceneGameClear()
{
}

SceneBase* SceneGameClear::Update()
{
	return new SceneTitle;
}

void SceneGameClear::Draw()
{
}
