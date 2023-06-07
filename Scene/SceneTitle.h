#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>
#include "Util/Vec3.h"

class CreateText;
class DrawTitleModel;

class Shadow;

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
	int m_size;
	int m_color;

	Vec3 m_pos;

	// 決まった数なのでvectorからarrayに変更します
	// テキスト描画用
	std::vector<std::shared_ptr<CreateText>>m_pText;
	DrawTitleModel* m_pDrawModel;

	Shadow* m_pShadow;
};

