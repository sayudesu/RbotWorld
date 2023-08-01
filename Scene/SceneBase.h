#pragma once
#include "../Util/Vec3.h"
// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}


	virtual void Init() {}
	virtual void End()	{}

	virtual SceneBase* Update() { return this; }
	virtual void Draw() {}

	// スライダー関連
	void UpdateSlider(bool &open);
	bool UpdateSliderOpen();
	bool UpdateSliderClose();

	void DrawSliderDoor();

protected:
	bool m_isSliderOpen;

private:
	// 画面切り替わる際のスライド用変数
	int m_hDoor;
	int m_sliderPos;
	Vec3 m_pos;
};