#include "UI.h"
#include <DxLib.h>
#include "Util/StringFunction.h"

namespace
{
	// �`�������W
	constexpr int kCharengeItemMax = kCharengeNum;// �A�C�e���}�b�N�X���ǂ��������鐔
	// �A�C�e���̐�
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
	m_charengeString[0] = "�R�C����S�ĉ�������I";
//	m_charengeString[0] = "777";
	m_charengeString[1] = "�_�C����S�ĉ�������I";
//	m_charengeString[1] = "777";

	
	// �c�w�t�H���g�f�[�^�t�@�C����ǂݍ��݁A�t�H���g�n���h����ϐ� FontHandle �ɕۑ�����
	// �����p�֐��̃C���X�^���X���쐬
	// �����̐ݒ�����ĕ������쐬
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
	m_scoreString[0] = "�R�C�����_ = %d";
	m_scoreString[1] = "�_�C�����_ = %d";
#endif
}

UI::~UI()
{

}

void UI::Update()
{
	// �`�������W
	ItemMaxCharenge();
	m_pString->Update(static_cast<int>(Item::coin),m_charengePos[0].x, m_charengePos[0].y);
	m_pString->Update(static_cast<int>(Item::diamond),m_charengePos[1].x, m_charengePos[1].y);
	// �X�R�A�̌v�Z
	Score();
}

void UI::Draw()
{	
	// �`�������W
	for (int i = 0; i < kCharengeItemMax; i++)
	{
		if (m_isCharenge[i])
		{
			DrawFormatString(m_charengePos[i].x, m_charengePos[i].y, 0xffffff, m_charengeString[i]);
			m_pString->Draw(i);
		}
	}

	// �X�R�A
	DrawFormatString(200, 320, 0xffffff, "���_ = %d", m_score);


#if DEBUG_		
	DrawFormatString(500, 500, 0xffffff, "diamond = %d", m_itemNum[static_cast<int>(Item::diamond)]);
	DrawFormatString(500, 530, 0xffffff, "MAXdiamond = %d", m_itemMaxNum[static_cast<int>(Item::diamond)]);

	DrawFormatString(500, 560, 0xffffff, "coin = %d", m_itemNum[static_cast<int>(Item::coin)]);
	DrawFormatString(500, 590, 0xffffff, "MAXcoin = %d", m_itemMaxNum[static_cast<int>(Item::coin)]);

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
			if (m_charengePos[i].x < 500.0f)m_charengePos[i].x += 20.0f;
			if (m_charengePos[i].y < 300.0f)m_charengePos[i].y += 20.0f;
			if (m_charengePos[i].x == 500.0f && m_charengePos[i].y == 300.0f)
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

void UI::Score()
{
	// �X�R�A�v�Z
	m_score = ((m_itemNum[static_cast<int>(Item::coin)] * 5 +
		m_itemNum[static_cast<int>(Item::diamond)] * 5)) * 15;
}
