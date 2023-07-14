#pragma once
#include "SceneBase.h"

class StringStatic;
class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(int score, int coinNum, int diamondNum);
	virtual ~SceneGameClear();
	void Init();
	void End();
	virtual SceneBase* Update() override;
	void Draw();
private:
	int m_score;
	int m_coinNum;
	int m_diamondNum;
	int m_buckLine;
	int m_buckLineCount;
	// ���������Ɉړ�������
	int m_sliderPos;
	int m_sliderEndPos;
	bool m_isStringSlider;
	StringStatic* m_pStringScore;

	// ���̃V�[���Ɉړ�
	bool m_isChangeScene;
};

