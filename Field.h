#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>

class Animation;
class Field
{
public:
	Field();
	virtual ~Field();

	void Init();
	void End();
	void Update();
	void Draw();
private:
	int m_hBox;

	int count;

	VECTOR m_boxPos;

	std::vector<std::shared_ptr<Animation>> m_pAnimation;// アニメーション再生用
};

