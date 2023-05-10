#pragma once

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
	/// <returns>0(フェードしていない)〜255(真っ黒)</returns>
	int GetFadeBright() const { return m_fadeBright; }

private:
	// フェード関連処理
	int m_fadeColor;
	int m_fadeBright;
	int m_fadeSpeed;
};