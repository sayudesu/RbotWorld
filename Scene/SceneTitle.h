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
	// テキスト用のクラス
	CreateText* m_pText;
	// 3Dモデル表示用クラス
	DrawTitleModel* m_pDrawModel;
	// 2Dシェーダー用クラス
	Shadow* m_pShadow;
};

