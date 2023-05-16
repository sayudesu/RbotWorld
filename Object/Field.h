#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include "Util/Vec3.h"

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

	VERTEX3D m_vertex[6];

//	int m_hBox;

//	int count;

//	Vec3 m_boxPos;

//	std::vector<std::shared_ptr<Animation>> m_pAnimation;// アニメーション再生用
};

