#pragma once
#include "SceneBase.h"

class StringStatic;
class SceneGameOver : public SceneBase
{
public:
	SceneGameOver();
	virtual ~SceneGameOver();

	void Init();
	void End();
	virtual SceneBase* Update() override;
	void Draw();
private:
	bool m_isChangeScene;
	int m_buckLineCount;
	int m_buckLine;
	bool m_isStringSlider;
	int m_sliderPos;
	int m_sliderEndPos;
	StringStatic* m_pStringScore;
};

