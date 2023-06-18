#include "SceneTitle.h"
#include "SceneDebug.h"
#include <DxLib.h>
#include "CreateText.h"
#include "DrawTitleModel.h"
#include "game.h"
#include "Pad.h"
#include "Sound.h"

#include "Shadow.h"

namespace
{
	// タイトル
	const char* kTextTitle = "[RobotWorld]";
	// ボタン誘導
	const char* const kTextStart = "Start";
	// テスト用
	const char* const kTextTest = "Credit";
	const char* const kTextTest2 = "Setting";

	const char* const kFileName = "Data/Img/org2.png";
	const char* const kFileName2= "Data/Img/org2Test2_n.png";
}

SceneTitle::SceneTitle()
{
	m_pDrawModel = new DrawTitleModel;
	m_pShadow = new Shadow(kFileName, kFileName2);
	m_pText = new CreateText;
}

SceneTitle::~SceneTitle()
{
	delete m_pDrawModel;
}

void SceneTitle::Init()
{
	// BGM 再生
	Sound::startBgm(Sound::SoundId_Title, 50);

	// テキスト追加 //
	// タイトル
	m_pText->Add(Game::kScreenWidth/2 - 400,250 ,kTextTitle,0xffff00,130,false);
	// スタート
	m_pText->Add(Game::kScreenWidth / 2 - 300,Game::kScreenHeight / 2 + 100, kTextStart,0x000000, 50, true);
	// クレジット
	m_pText->Add(Game::kScreenWidth / 2 - 300, Game::kScreenHeight / 2 + 100 + 50 + 2, kTextTest, 0x000000, 50, true);
	// 設定
	m_pText->Add(Game::kScreenWidth / 2 - 300, Game::kScreenHeight / 2 + 100 + 50 + 50 + 4, kTextTest2, 0x000000, 50, true);
}

void SceneTitle::End()
{
	// BGM 停止
	Sound::stopBgm(Sound::SoundId_Title);
}

SceneBase* SceneTitle::Update()
{

	m_pShadow->Update();

	m_pDrawModel->Update();

	m_pText->Update();

	if (m_pText->SelectNo() == 0)
	{
		return(new SceneDebug);
	}
	if (m_pText->SelectNo() == 1)
	{
		DrawString(1000, 100, "まだクレジット表記はできていません。", 0xffffff);
	}
	if (m_pText->SelectNo() == 2)
	{ 
		DrawString(1000, 100, "まだ設定画面はできていません。", 0xffffff);
	}

	return this;
}

void SceneTitle::Draw()
{
	// 3Dモデル描画
	m_pDrawModel->Draw();
	// 2Dシェーダー描画
	m_pShadow->Draw();
	// テキスト描画
	m_pText->Draw();
}
