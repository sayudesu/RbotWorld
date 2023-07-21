#pragma once
#include "Vec3.h"

class PauseScreen
{
public:
	PauseScreen();
	virtual~PauseScreen();
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
};

