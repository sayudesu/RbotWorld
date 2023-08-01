#include "UI.h"
#include <DxLib.h>
#include "../Util/Achievement.h"
#include "../Util/game.h"

namespace
{
	// �`�������W
	constexpr int kCharengeItemMax = kCharengeNum;// �A�C�e���}�b�N�X���ǂ��������鐔

	// �A�C�e���̐�
	constexpr int kItemMax = kItemNum;// �A�C�e���̍ő吔

	// �t�H���g�֘A
	const char* kFont     = "Data/Fonts/851letrogo_007.ttf";// �t�H���g�p�X
	const char* kFontName = "851���g���S";// �t�H���g�̖��O

	// �`�������W�p����
	const char* kCharengeCoin    = "�R�C�������ׂĂ������イ�����I";
	constexpr int kCharengeCoinColor = 0xFFFFFF11;
	const char* kCharengeDaimond = "�_�C�������ׂĂ������イ�����I";
	constexpr int kCharengeDiamondColor = 0x1111FF;
	constexpr int kStringCount = 60 * 3;// �����̕`�掞��
}

UI::UI() :
	m_score(0)
{
	// �A�C�e�����̏�����
	for (int i = 0; i < kItemMax; i++)
	{
		m_itemNum[i] = 0;
		m_itemMaxNum[i] = 0;
	}

	// �`�������W�p�ϐ��̏�����
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

	// �����p�֐��̃C���X�^���X���쐬
	// �����̐ݒ�����ĕ������쐬
	m_pString = new Achievement;
	m_pString->InitFont(kFont, kFontName);
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		m_pString->Add(m_charengePos[i].x, m_charengePos[i].y, m_charengeString[i], m_charengeColor[i], 64);
	}

	m_pStringStatic = new StringStatic;
	m_pStringStatic->InitFont(kFont, kFontName);
	m_pStringStatic->AddStatic(Game::kScreenWidth/2 - 500, 100, "���_ = %d",0, 0xffffff, 100);
}

UI::~UI()
{
	delete m_pString;
	delete m_pStringStatic;
}

void UI::Update()
{
	// �`�������W�����̈ړ�-----------------------------------------------------------------------------
	// �����̐���
	ItemMaxCharenge();
	// �ړ�����
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		m_pString->Update(i,m_charengePos[i].x, m_charengePos[i].y);
	}
	// -------------------------------------------------------------------------------------------------

	// �X�R�A�̍X�V-------------------------------------------------------------------------------------
	Score();
	m_pStringStatic->UpdateStatic(0, Game::kScreenWidth / 2 - 500, 100, m_score);
	// -------------------------------------------------------------------------------------------------
	
}

void UI::Draw()
{	
	// �`�������W
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		if (m_isCharenge[i])
		{
			m_pString->Draw(i);
		}
	}

	// �X�R�A
	m_pStringStatic->DrawStatic(0);

#if DEBUG_		
	DrawFormatString(200, 500, 0xffffff, "diamond = %d", m_itemNum[static_cast<int>(Item::diamond)]);
	DrawFormatString(200, 530, 0xffffff, "MAXdiamond = %d", m_itemMaxNum[static_cast<int>(Item::diamond)]);

	DrawFormatString(200, 560, 0xffffff, "coin = %d", m_itemNum[static_cast<int>(Item::coin)]);
	DrawFormatString(200, 590, 0xffffff, "MAXcoin = %d", m_itemMaxNum[static_cast<int>(Item::coin)]);

	// �A�C�e���X�̎擾��
	DrawFormatString(200, 200, 0xffffff, "�R�C���擾�� = %d", m_itemNum[static_cast<int>(Item::coin)]);
	DrawFormatString(200, 230, 0xffffff, "�_�C���擾�� = %d", m_itemNum[static_cast<int>(Item::diamond)]);

	// �A�C�e���X�̓��_
	for (int i = 0; i < kItemMax; i++)
	{
		DrawFormatString(m_scorePos[i].x, m_scorePos[i].y, 0xffffff, m_scoreString[i], m_itemNum[i] * 5);
	}
#endif
}
// �A�C�e���̎擾��
void UI::SetItemNum(Item name, int num)
{
	if (name == Item::coin)   m_itemNum[static_cast<int>(Item::coin)]    = num;
	if (name == Item::diamond)m_itemNum[static_cast<int>(Item::diamond)] = num;
}

// �A�C�e���̍ő吔
void UI::SetItemMaxNum(Item name, int num)
{
	if (name == Item::coin)   m_itemMaxNum[static_cast<int>(Item::coin)]    = num;
	if (name == Item::diamond)m_itemMaxNum[static_cast<int>(Item::diamond)] = num;
}

// �`�������W�A�b�v�f�[�g
void UI::ItemMaxCharenge()
{
	// �`�������W
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		// �A�C�e�����}�b�N�X�ɂȂ�����
		if (m_itemNum[i] >= m_itemMaxNum[i] && !m_isCharenge[i])
		{
			m_isCharengeDraw[i] = true;
		}
		// �������ړ�
		// �ړI�̏ꏊ�ɕ����͓�������J�E���g�_�E���J�n
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
		// �J�E���g�_�E�����I�������
		// ��������ɍs��
		// ������
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

// �X�R�A�v�Z
void UI::Score()
{
	m_score = ((m_itemNum[static_cast<int>(Item::coin)] * 5 +
		m_itemNum[static_cast<int>(Item::diamond)] * 5)) * 15;
}
