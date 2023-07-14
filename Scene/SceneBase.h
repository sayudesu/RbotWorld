#pragma once
#include "Vec3.h"
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


	// フェード関連
	void UpdateFade();
	void DrawFade() const;

	bool IsFadingIn() const;	// フェードイン中
	bool IsFadingOut() const;	// フェードアウト中
	bool IsFading() const { return IsFadingIn() || IsFadingOut(); }	// フェードインorアウト中

	void StartFadeOut();	// フェードアウト開始


	/// <summary>
	/// フェードの明るさを取得
	/// </summary>
	/// <returns>0(フェードしていない)～255(真っ黒)</returns>
	int GetFadeBright() const { return m_fadeBright; }

	// スライダー関連
	void UpdateSlider(bool &open);
	bool UpdateSliderOpen();
	bool UpdateSliderClose();

	void DrawSliderDoor();

protected:
	bool m_isSliderOpen;

private:
	// フェード関連処理
	int m_fadeColor;
	int m_fadeBright;
	int m_fadeSpeed;

	// 画面切り替わる際のスライド用変数
	int m_hDoor;
	int m_sliderPos;
	Vec3 m_pos;
};