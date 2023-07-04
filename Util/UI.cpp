#include "UI.h"
#include <DxLib.h>
#include "Util/StringFunction.h"

namespace
{
	// チャレンジ
	constexpr int kCharengeItemMax = kCharengeNum;// アイテムマックスかどうかを見る数
	// アイテムの数
	constexpr int kItemMax = kItemNum;

	const char* kFont = "Data/Fonts/Valentina-Regular.ttf";
}

UI::UI() :
	m_score(0)
{
	for (int i = 0; i < kItemMax; i++)
	{
		m_itemNum[i] = 0;
		m_itemMaxNum[i] = 0;
	}

	for (int i = 0; i < kCharengeItemMax; i++)
	{
		m_charengePos[i] = {0.0f,0.0f ,0.0f};
		m_drawCount[i] = 60 * 3;
		m_isCharenge[i] = false;
		m_isCharengeDraw[i] = false;
	}
	m_charengeColor[0] = 0xffff00;
	m_charengeColor[1] = 0x0000ff;
	m_charengeString[0] = "コインを全て回収した！";
//	m_charengeString[0] = "777";
	m_charengeString[1] = "ダイヤを全て回収した！";
//	m_charengeString[1] = "777";

	
	// ＤＸフォントデータファイルを読み込み、フォントハンドルを変数 FontHandle に保存する
	// 文字用関数のインスタンスを作成
	// 文字の設定をして文字を作成
	m_pString = new StringFunction;
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		m_pString->Add(m_charengePos[i].x, m_charengePos[i].y, m_charengeString[i], m_charengeColor[i], 64, "Valentina");
	}
	
#if DEBUG_
	for (int i = 0; i < 2; i++)
	{
		m_scorePos[i] = { 0.0f,0.0f ,0.0f };
	}
	m_scorePos[0] = { 200.0f,260.0f ,0.0f };
	m_scorePos[1] = { 200.0f,290.0f ,0.0f };
	m_scoreString[0] = "コイン得点 = %d";
	m_scoreString[1] = "ダイヤ得点 = %d";
#endif
}

UI::~UI()
{

}

void UI::Update()
{
	// チャレンジ
	ItemMaxCharenge();
	m_pString->Update(static_cast<int>(Item::coin),m_charengePos[0].x, m_charengePos[0].y);
	m_pString->Update(static_cast<int>(Item::diamond),m_charengePos[1].x, m_charengePos[1].y);
	// スコアの計算
	Score();
}

void UI::Draw()
{	
	// チャレンジ
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		if (m_isCharenge[i])
		{
			DrawFormatString(m_charengePos[i].x, m_charengePos[i].y, 0xffffff, m_charengeString[i]);
			m_pString->Draw(i);
		}
	}

	// スコア
	DrawFormatString(200, 320, 0xffffff, "得点 = %d", m_score);


#if DEBUG_		
	DrawFormatString(500, 500, 0xffffff, "diamond = %d", m_itemNum[static_cast<int>(Item::diamond)]);
	DrawFormatString(500, 530, 0xffffff, "MAXdiamond = %d", m_itemMaxNum[static_cast<int>(Item::diamond)]);

	DrawFormatString(500, 560, 0xffffff, "coin = %d", m_itemNum[static_cast<int>(Item::coin)]);
	DrawFormatString(500, 590, 0xffffff, "MAXcoin = %d", m_itemMaxNum[static_cast<int>(Item::coin)]);

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

void UI::SetItemNum(Item name, int num)
{
	if (name == Item::coin)   m_itemNum[static_cast<int>(Item::coin)]    = num;
	if (name == Item::diamond)m_itemNum[static_cast<int>(Item::diamond)] = num;
}

void UI::SetItemMaxNum(Item name, int num)
{
	if (name == Item::coin)   m_itemMaxNum[static_cast<int>(Item::coin)]    = num;
	if (name == Item::diamond)m_itemMaxNum[static_cast<int>(Item::diamond)] = num;
}

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
			if (m_charengePos[i].x < 500.0f)m_charengePos[i].x += 20.0f;
			if (m_charengePos[i].y < 300.0f)m_charengePos[i].y += 20.0f;
			if (m_charengePos[i].x == 500.0f && m_charengePos[i].y == 300.0f)
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

void UI::Score()
{
	// スコア計算
	m_score = ((m_itemNum[static_cast<int>(Item::coin)] * 5 +
		m_itemNum[static_cast<int>(Item::diamond)] * 5)) * 15;
}
