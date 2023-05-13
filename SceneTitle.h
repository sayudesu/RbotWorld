#pragma once
#include "SceneBase.h"

class CreateText;
class SceneTitle:public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual void End();
	virtual SceneBase* Update() override;
	virtual void Draw();
private:
	CreateText* m_pText;
};

