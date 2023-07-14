#include "SceneTitle.h"
#include "SceneMain.h"
#include <DxLib.h>
#include "CreateText.h"
#include "DrawTitleModel.h"
#include "game.h"
#include "Pad.h"
#include "Sound.h"

#include "FieldOne.h"


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


	const char* const kTextQuit= "QUIT";
}

SceneTitle::SceneTitle()
{
	m_pDrawModeler = new TitleDrawModeler;
	m_pShadow = new Shadow(kFileName, kFileName2);
	m_pText = new CreateText;
}

SceneTitle::~SceneTitle()
{
	delete m_pDrawModeler;
	delete m_pText;
}

void SceneTitle::Init()
{
	// BGM 再生
	Sound::startBgm(Sound::SoundId_Title, 50);

	// テキスト追加 //
	// タイトル
	m_pText->Add(Game::kScreenWidth/2 - 400,250 ,kTextTitle,0xffff00,130,false);
	// スタート
	int x = Game::kScreenWidth / 2 - 250;
	int y = Game::kScreenHeight / 2 + 100;
	int addFrame = 50 + 2;
	int color = 0x000000;
	int size = 50;
	m_pText->Add(x,y, kTextStart, color, size, true);
	// クレジット
	y += addFrame;
	m_pText->Add(x, y, kTextTest, color, size, true);
	y += addFrame;
	// 設定
	m_pText->Add(x, y, kTextTest2, color, size, true);
	// QUIT
	y += addFrame;
	m_pText->Add(x, y, kTextQuit, color, size, true);
}

void SceneTitle::End()
{
	// BGM 停止
	Sound::stopBgm(Sound::SoundId_Title);
}

SceneBase* SceneTitle::Update()
{
	// 2Dシェーダーの更新
//	m_pShadow->Update();
	// モデルの更新
	m_pDrawModeler->Update();

	m_pText->Update();
	// シーンを選択したら移動モデルの開始する
	if (m_pText->SelectNo() != -1)
	{
		m_pDrawModeler->SetStartPos(true);
	}
	// ゲームプレイ画面に移動
	if (m_pText->SelectNo() == 0)
	{
		m_isSliderOpen = true;
		if (m_pDrawModeler->GetSceneChange())
		{			
			m_pField = std::make_shared<FieldBase>();
			if (SceneBase::UpdateSliderClose())
			{
				return(new SceneMain(m_pField));
				
			}
		}
	}
	// クレジット画面に移動
	if (m_pText->SelectNo() == 1)
	{
		if (m_pDrawModeler->GetSceneChange())
		{
			DrawString(1000, 100, "まだクレジット表記はできていません。", 0xffffff);
		}
	}
	// 設定画面に移動
	if (m_pText->SelectNo() == 2)
	{ 
		if (m_pDrawModeler->GetSceneChange())
		{
			DrawString(1000, 100, "まだ設定画面はできていません。", 0xffffff);
		}
	}
	// ゲーム終了
	if (m_pText->SelectNo() == 3)
	{
		if (m_pDrawModeler->GetSceneChange())
		{
			DxLib::DxLib_End();
		}
	}

	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);
	// 3Dモデル描画
	m_pDrawModeler->Draw();
	// 2Dシェーダー描画
//	m_pShadow->Draw();
	// テキスト描画
	m_pText->Draw();

	DrawBox(Game::kScreenWidth / 2 - 30, Game::kScreenHeight / 2 - 30, Game::kScreenWidth / 2 + 30, Game::kScreenHeight / 2 + 30, 0xffffff, true);

	// スライドを描画
	SceneBase::DrawSliderDoor();
}
