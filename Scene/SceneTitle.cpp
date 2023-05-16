#include "SceneTitle.h"
#include "SceneDebug.h"
#include <DxLib.h>
#include "CreateText.h"
#include "game.h"
#include "Pad.h"

namespace
{
	// タイトル
	const char* const kTextTitle = "[RobotWorld]";
	// ボタン誘導
	const char* const kTextStart = "「 A 」ボタンで開始！";
	// テスト用
	const char* const kTextTest = "揺れながら文字を上昇して消える～";
}

SceneTitle::SceneTitle():
	m_size(0),
	m_color(0),
	m_pos(0.0f, 0.0f, 0.0f)
{
	m_pText.push_back(std::make_shared<CreateText>());
	m_pText.push_back(std::make_shared<CreateText>());
}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return(new SceneDebug);
	}

	return this;
}

void SceneTitle::Draw()
{

	// ここを今後　for　で回します。
	m_pos.x = static_cast<float>(Game::kScreenWidth) / 2.0f - 250.0f;
	m_pos.y = static_cast<float>(Game::kScreenHeight) / 2.0f - 300.0f;
	m_size = 100;
	m_color = 0xffff00;

	//// タイトル表示
	m_pText[0]->DrawDef(m_pos,
		kTextTitle, m_size, m_color);

	m_pos.x = static_cast<float>(Game::kScreenWidth) / 2.0f - 200.0f;
	m_pos.y = static_cast<float>(Game::kScreenHeight) / 2.0f + 300.0f;
	m_size = 32;
	m_color = 0xff0000;

	//// スタートボタン表示
	m_pText[1]->DrawDef(m_pos,
		kTextStart, m_size, m_color);

	m_pos.x = static_cast<float>(Game::kScreenWidth) / 2.0f - 200.0f;
	m_pos.y = static_cast<float>(Game::kScreenHeight) / 2.0f + 300.0f;
	m_size = 32;
	m_color = 0xff0000;

	//// 文字テスト
	m_pText[0]->DrawUp(m_pos,
		kTextTest, m_size, 8.0f,m_color);
}
