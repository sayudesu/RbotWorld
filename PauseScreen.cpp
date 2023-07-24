#include "PauseScreen.h"
#include <DxLib.h>
#include "Util/game.h"
#include "Util/CreateText.h"
#include "ButtonDrawer.h"

PauseScreen::PauseScreen() :
	m_updateFunc(&PauseScreen::UpdateStart),
	m_boxPos(-Game::kScreenHeight),
	m_isPauseEnd(false),
	m_isEnd(false),
	m_isButtonSettingDraw(false),
	m_isMainScene(false),
	m_isTitleScene(false),
	m_pText(nullptr),
	m_pButtonSetting(nullptr)
{
	m_pText = new CreateText;
	m_pButtonSetting = new ButtonDrawer;
}

PauseScreen::~PauseScreen()
{
	delete m_pText;
	m_pText = nullptr;
	delete m_pButtonSetting;
	m_pButtonSetting = nullptr;
}

void PauseScreen::Init()
{
	m_pText->Add(Game::kScreenWidth / 2 - 500, 250, "メニューがめんひょうじちゅう！", 0xffff00, 80, false);
	// スタート
	int x = Game::kScreenWidth / 2 - 250;
	int y = Game::kScreenHeight / 2 + 100 - 100;
	int addFrame = 50 + 2;
	int color = 0x000000;
	int size = 50;
	m_pText->Add(x, y, "げーむにもどる", color, size, true);
	// クレジット
	y += addFrame;
	m_pText->Add(x, y, "そうさせつめい", color, size, true);
	y += addFrame;
	// 設定
	m_pText->Add(x, y, "いちからはじめる", color, size, true);
	// QUIT
	y += addFrame;
	m_pText->Add(x, y, "たいとるにもどる", color, size, true);

	m_pText->UpdatePos(0, m_boxPos);

	m_pButtonSetting->Init();
}

// 全ての更新処理
void PauseScreen::Update()
{
	// 0 ポーズ画面を終了する
	// 1 操作説明を描画する
	// 2 ゲームを一からやりなおす
	// 3 タイトルにもどる
	if (m_pText->GetSelectNo() == 0)
	{
		m_updateFunc = &PauseScreen::UpdateEnd;
		m_isButtonSettingDraw = false;
		m_pText->ResetSelectNo();
	}
	if (m_pText->GetSelectNo() == 1)
	{
		m_isButtonSettingDraw = true;
		m_pButtonSetting->Update(Game::kScreenWidth / 2, Game::kScreenHeight / 2);
		m_pText->ResetSelectNo();
	}
	if (m_pText->GetSelectNo() == 2)
	{
		m_isMainScene = true;
	}
	if (m_pText->GetSelectNo() == 3)
	{
		m_isTitleScene = true;
	}

	(this->*m_updateFunc)();
}

// ポーズ画面初めの処理
void PauseScreen::UpdateStart()
{
	// 画面の上から下に移動させる
	if (m_boxPos < 0)
	{
		m_boxPos += 50;
		m_pText->UpdatePos(0, m_boxPos);
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
	if (m_pText->GetSelectNo() == -1)
	{
		m_pText->Update();
	}
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
		m_pText->UpdatePos(0, m_boxPos);
	}
	else
	{
		m_isButtonSettingDraw = false;
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
			0xaaaaaa, true);
	// 選択画面表示
	m_pText->Draw();

	// ボタン説明表示
	if (m_isButtonSettingDraw)
	{
		m_pButtonSetting->Draw();
	}
}

// 全ての変数を初期状態に戻します
void PauseScreen::Reset()
{	
	m_updateFunc = &PauseScreen::UpdateStart;
	m_boxPos = -Game::kScreenHeight;
	m_isPauseEnd = false;
	m_isEnd = false;
}
