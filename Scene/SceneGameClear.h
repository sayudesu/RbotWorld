#pragma once
#include "SceneBase.h"

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(int score);
	virtual ~SceneGameClear();

	virtual SceneBase* Update() override;
	void Draw();
private:
	int m_score;
};

