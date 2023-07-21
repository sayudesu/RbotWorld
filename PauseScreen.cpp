#include "PauseScreen.h"
#include <DxLib.h>
#include "Util/game.h"

PauseScreen::PauseScreen() :
	m_updateFunc(&PauseScreen::UpdateStart),
	m_boxPos(-Game::kScreenHeight),
	m_isPauseEnd(false),
	m_isEnd(false)
{
}

PauseScreen::~PauseScreen()
{
}

// 全ての更新処理
void PauseScreen::Update()
{
	(this->*m_updateFunc)();
}

// ポーズ画面初めの処理
void PauseScreen::UpdateStart()
{
	// 画面の上から下に移動させる
	if (m_boxPos < 0)
	{
		m_boxPos += 50;
	}
	else
	{
		// 現在ポーズ画面
		m_isPauseEnd = false;
		// 関数を切り替える
		m_updateFunc = &PauseScreen::UpdateMain;
	}
}

// ポーズ画面中
void PauseScreen::UpdateMain()
{
	// ポーズ画面ではなくなった場合
	// ポーズ画面終了用関数に切り替える
	if (m_isPauseEnd)
	{
		m_updateFunc = &PauseScreen::UpdateEnd;
	}
}

// ポーズ画面終了用関数
void PauseScreen::UpdateEnd()
{
	// 上に移動させる
	if (m_boxPos > -Game::kScreenHeight)
	{
		m_boxPos -= 50;
	}
	else
	{
		m_isPauseEnd = false;
		m_isEnd = true;
	}
}
// 描画
void PauseScreen::Draw()
{
	// 四角形を描画
	DrawBox(500, 300 + m_boxPos,
			Game::kScreenWidth -500,Game::kScreenHeight - 300 + m_boxPos,
			0xffffff, true);
}

// 全ての変数を初期状態に戻します
void PauseScreen::Reset()
{	
	m_updateFunc = &PauseScreen::UpdateStart;
	m_boxPos = -Game::kScreenHeight;
	m_isPauseEnd = false;
	m_isEnd = false;
}
