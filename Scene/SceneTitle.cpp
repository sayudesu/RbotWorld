#include "SceneTitle.h"
#include "SceneMain.h"
#include <DxLib.h>
#include "CreateText.h"
#include "DrawTitleModel.h"
#include "game.h"
#include "Pad.h"
#include "Sound.h"
#include "ButtonDrawer.h"
#include "FieldOne.h"


#include "Shadow.h"

namespace
{
	// タイトル
	const char* kTextTitle = "ろぼっとわーるど";
	// ボタン誘導
	const char* const kTextStart = "すたーと";
	// テスト用
	const char* const kTextTest = "くれじっと";
	const char* const kTextTest2 = "ぼたんせつめい";

	const char* const kFileName = "Data/Img/org2.png";
	const char* const kFileName2= "Data/Img/org2Test2_n.png";


	const char* const kTextQuit= "やめる";
}

SceneTitle::SceneTitle()
{
	m_pDrawModeler = new TitleDrawModeler;
	m_pShadow = new Shadow(kFileName, kFileName2);
	m_pText = new CreateText;
	m_pButtonDrawer = new ButtonDrawer;
}

SceneTitle::~SceneTitle()
{
	delete m_pDrawModeler;
	delete m_pText;
	delete m_pButtonDrawer;
}

void SceneTitle::Init()
{
	// BGM 再生
	Sound::startBgm(Sound::SoundId_Title, 50);
	m_pButtonDrawer->Init();
	// テキスト追加 //
	// タイトル
	m_pText->Add(Game::kScreenWidth/2 - 500,250 ,kTextTitle,0xffff00,130,false);
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
	if (m_pText->GetSelectNo() == -1)
	{
		m_pText->Update();
	}

	// シーンを選択したら移動モデルの開始する
	if (m_pText->GetSelectNo() != -1)
	{
		m_pDrawModeler->SetStartPos(true);
	}
	// ゲームプレイ画面に移動
	if (m_pText->GetSelectNo() == 0)
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
	if (m_pText->GetSelectNo() == 1)
	{
		if (m_pDrawModeler->GetSceneChange())
		{
			m_pText->ResetSelectNo();
			DrawString(1000, 100, "まだクレジット表記はできていません。", 0xffffff);
		}
	}
	// 設定画面に移動
	if (m_pText->GetSelectNo() == 2)
	{ 
		if (m_pDrawModeler->GetSceneChange())
		{
			// 説明スライド
			static int yS = -Game::kScreenHeight;
			static bool end = false;
			static bool change = false;
			// 上から下にスライド
			if (yS < 0 && !end)
			{
				yS += 30;
			}

			// ボタン説明画面の座標
			int x = Game::kScreenWidth / 2 + 100;
			int y = Game::kScreenHeight / 2 + yS;
			// ボタン説明画面の位置
			m_pButtonDrawer->Update(x, y);

			// 戻る
			if (Pad::isTrigger(PAD_INPUT_1))
			{
				end = true;
			}
			// 下から上にスライド
			if (end)
			{
				if(yS > Game::kScreenHeight)yS -= 30;
				if (yS < -Game::kScreenHeight)
				{
					end = false;
					change = true;
				}
			}

			if (end && !change)
			{
				change = false;
				m_pText->ResetSelectNo();
			}
		}
	}
	else
	{
		m_pButtonDrawer->Update(-Game::kScreenWidth / 2 + 100, 1000);
	}
	// ゲーム終了
	if (m_pText->GetSelectNo() == 3)
	{
		if (m_pDrawModeler->GetSceneChange())
		{
			DxLib::DxLib_End();
		}
	}

	// スライドを開ける
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
	m_pButtonDrawer->Draw();
	// スライドを描画
	SceneBase::DrawSliderDoor();
}
