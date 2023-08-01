#pragma once

class CreateText;
class ButtonDrawer;

class PauseScreen
{
public:
	PauseScreen();
	virtual~PauseScreen();
	// 初期化処理
	void Init();
	// ポーズ画面全体の処理
	void Update();
	// ポーズ画面最初の処理
	void UpdateStart();
	// ポーズメイン画面表示
	void UpdateMain();
	// ポーズ画面終了処理
	void UpdateEnd();
	// 描画
	void Draw();
public:
	// ポーズ画面を終了したいかどうか
	void GetPauseEnd(bool isEnd) { m_isPauseEnd = isEnd; }
	// ポーズ画面が終了しかたどうか
	bool isSetEnd() { return m_isEnd; }
	// シーン切り替え用
	bool isSetMainScene() { return m_isMainScene; }
	bool isSetTitleScene() { return m_isTitleScene; }
	// 変数を初期化
	void Reset();
private:
	// メンバ関数ポインタ
	void (PauseScreen::* m_updateFunc)();
	// 四角形の位置調整
	int m_boxPos;
	// ポーズ画面終了処理
	bool m_isPauseEnd;
	// ポーズ画面が終了したかどうか
	bool m_isEnd;
	// ボタン説明を出すがどうか
	bool m_isButtonSettingDraw;
	// シーン切り替え用
	bool m_isMainScene;
	bool m_isTitleScene;
	// 選択用テキストを描画します
	CreateText* m_pText;
	// 操作説明を表示
	ButtonDrawer* m_pButtonSetting;
};

