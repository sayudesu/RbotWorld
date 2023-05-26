#pragma once
#include "SceneBase.h"

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear();
	virtual ~SceneGameClear();

	virtual SceneBase* Update() override;
	void Draw();
private:
};

