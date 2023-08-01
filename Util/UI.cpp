#include "UI.h"
#include <DxLib.h>
#include "../Util/Achievement.h"
#include "../Util/game.h"

namespace
{
	// チャレンジ
	constexpr int kCharengeItemMax = kCharengeNum;// アイテムマックスかどうかを見る数

	// アイテムの数
	constexpr int kItemMax = kItemNum;// アイテムの最大数

	// フォント関連
	const char* kFont     = "Data/Fonts/851letrogo_007.ttf";// フォントパス
	const char* kFontName = "851レトロゴ";// フォントの名前

	// チャレンジ用文字
	const char* kCharengeCoin    = "コインをすべてかいしゅうした！";
	constexpr int kCharengeCoinColor = 0xFFFFFF11;
	const char* kCharengeDaimond = "ダイヤをすべてかいしゅうした！";
	constexpr int kCharengeDiamondColor = 0x1111FF;
	constexpr int kStringCount = 60 * 3;// 文字の描画時間
}

UI::UI() :
	m_score(0)
{
	// アイテム数の初期化
	for (int i = 0; i < kItemMax; i++)
	{
		m_itemNum[i] = 0;
		m_itemMaxNum[i] = 0;
	}

	// チャレンジ用変数の初期化
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		m_charengePos[i] = {0.0f,0.0f ,0.0f};
		m_drawCount[i] = kStringCount;
		m_isCharenge[i] = false;
		m_isCharengeDraw[i] = false;
	}
	m_charengeColor[0] = kCharengeCoinColor;
	m_charengeColor[1] = kCharengeDiamondColor;
	m_charengeString[0] = kCharengeCoin;
	m_charengeString[1] = kCharengeDaimond;

	// 文字用関数のインスタンスを作成
	// 文字の設定をして文字を作成
	m_pString = new Achievement;
	m_pString->InitFont(kFont, kFontName);
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		m_pString->Add(m_charengePos[i].x, m_charengePos[i].y, m_charengeString[i], m_charengeColor[i], 64);
	}

	m_pStringStatic = new StringStatic;
	m_pStringStatic->InitFont(kFont, kFontName);
	m_pStringStatic->AddStatic(Game::kScreenWidth/2 - 500, 100, "得点 = %d",0, 0xffffff, 100);
}

UI::~UI()
{
	delete m_pString;
	delete m_pStringStatic;
}

void UI::Update()
{
	// チャレンジ文字の移動-----------------------------------------------------------------------------
	// 文字の制御
	ItemMaxCharenge();
	// 移動処理
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		m_pString->Update(i,m_charengePos[i].x, m_charengePos[i].y);
	}
	// -------------------------------------------------------------------------------------------------

	// スコアの更新-------------------------------------------------------------------------------------
	Score();
	m_pStringStatic->UpdateStatic(0, Game::kScreenWidth / 2 - 500, 100, m_score);
	// -------------------------------------------------------------------------------------------------
	
}

void UI::Draw()
{	
	// チャレンジ
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		if (m_isCharenge[i])
		{
			m_pString->Draw(i);
		}
	}

	// スコア
	m_pStringStatic->DrawStatic(0);

#if DEBUG_		
	DrawFormatString(200, 500, 0xffffff, "diamond = %d", m_itemNum[static_cast<int>(Item::diamond)]);
	DrawFormatString(200, 530, 0xffffff, "MAXdiamond = %d", m_itemMaxNum[static_cast<int>(Item::diamond)]);

	DrawFormatString(200, 560, 0xffffff, "coin = %d", m_itemNum[static_cast<int>(Item::coin)]);
	DrawFormatString(200, 590, 0xffffff, "MAXcoin = %d", m_itemMaxNum[static_cast<int>(Item::coin)]);

	// アイテム個々の取得数
	DrawFormatString(200, 200, 0xffffff, "コイン取得数 = %d", m_itemNum[static_cast<int>(Item::coin)]);
	DrawFormatString(200, 230, 0xffffff, "ダイヤ取得数 = %d", m_itemNum[static_cast<int>(Item::diamond)]);

	// アイテム個々の得点
	for (int i = 0; i < kItemMax; i++)
	{
		DrawFormatString(m_scorePos[i].x, m_scorePos[i].y, 0xffffff, m_scoreString[i], m_itemNum[i] * 5);
	}
#endif
}
// アイテムの取得数
void UI::SetItemNum(Item name, int num)
{
	if (name == Item::coin)   m_itemNum[static_cast<int>(Item::coin)]    = num;
	if (name == Item::diamond)m_itemNum[static_cast<int>(Item::diamond)] = num;
}

// アイテムの最大数
void UI::SetItemMaxNum(Item name, int num)
{
	if (name == Item::coin)   m_itemMaxNum[static_cast<int>(Item::coin)]    = num;
	if (name == Item::diamond)m_itemMaxNum[static_cast<int>(Item::diamond)] = num;
}

// チャレンジアップデート
void UI::ItemMaxCharenge()
{
	// チャレンジ
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		// アイテムがマックスになったら
		if (m_itemNum[i] >= m_itemMaxNum[i] && !m_isCharenge[i])
		{
			m_isCharengeDraw[i] = true;
		}
		// 文字が移動
		// 目的の場所に文字は動いたらカウントダウン開始
		if (m_isCharengeDraw[i])
		{
			m_isCharenge[i] = true;

			if (m_charengePos[i].x < 450.0f)m_charengePos[i].x += 20.0f;
			if (m_charengePos[i].y < 300.0f)m_charengePos[i].y += 20.0f;

			if (m_charengePos[i].x >= 450.0f && m_charengePos[i].y >= 300.0f)
			{
				m_drawCount[i]--;
			}
		}
		// カウントダウンが終わったら
		// 文字が上に行き
		// 消える
		if (m_drawCount[i] < 0)
		{
			m_isCharengeDraw[i] = false;

			if (m_charengePos[i].y > 0.0f)m_charengePos[i].y -= 20.0f;

			if (m_charengePos[i].y <= 0.0f)
			{
				m_isCharenge[i] = false;
				m_charengePos[i] = { 0.0f,0.0f ,0.0f };
			}
		}
	}
}

// スコア計算
void UI::Score()
{
	m_score = ((m_itemNum[static_cast<int>(Item::coin)] * 5 +
		m_itemNum[static_cast<int>(Item::diamond)] * 5)) * 15;
}
