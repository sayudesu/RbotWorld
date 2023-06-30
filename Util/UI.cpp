#include "UI.h"
#include <DxLib.h>

UI::UI() :
	m_score(0)
{
	for (int i = 0; i < static_cast<int>(Item::itemMaxNum); i++)
	{
		drawCount[i] = 60 * 3;
		m_isCharenge[i] = false;
	}
}

UI::~UI()
{

}

void UI::Update()
{
	// �A�C�e���̐���
	// ���݂̃A�C�e���̐����ő吔�Ɠ����ɂȂ���
	// ������\��������
	// �J�E���g��i�߂�
	// ��莞�ԕ\��������Ə�����
	for (int i = 0; i < static_cast<int>(Item::itemMaxNum); i++)
	{
		if (m_itemNum[i] == m_itemMaxNum[i] && drawCount[i] < 60 * 5)
		{
			m_isCharenge[i] = true;
			drawCount[i]++;
		}
		else
		{
			m_isCharenge[i] = false;				
		}
	}

	// 
	if (m_itemNum[static_cast<int>(Item::coin)] > 100 && drawCount[0] < 60 * 5)
	{
		m_isCharenge[0] = true;
		drawCount[0]++;
	}
	else
	{
		m_isCharenge[0] = false;
		
	}

	Score();
}

void UI::Draw()
{
	// �A�C�e���X�̎擾��
	DrawFormatString(200, 200, 0xffffff, "�R�C���擾�� = %d", m_itemNum[static_cast<int>(Item::coin)]);
	DrawFormatString(200, 230, 0xffffff, "�_�C���擾�� = %d", m_itemNum[static_cast<int>(Item::diamond)]);
	// �A�C�e���X�̓��_
	DrawFormatString(200, 260, 0xffffff, "�R�C�����_ = %d", m_itemNum[static_cast<int>(Item::coin)] * 5);
	DrawFormatString(200, 290, 0xffffff, "�_�C�����_ = %d", m_itemNum[static_cast<int>(Item::diamond)] * 5);
	// �X�R�A
	DrawFormatString(200, 320, 0xffffff, "���_ = %d", m_score);
	// �`�������W
	if(m_isCharenge[0])DrawFormatString(500, 200, 0xffffff, "�R�C��100���B�������I");

	if(m_isCharenge[1])DrawFormatString(500, 230, 0xffffff, "�R�C����S�ĉ�������I");
	if(m_isCharenge[2])DrawFormatString(500, 300, 0xffffff, "�_�C����S�ĉ�������I");
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

void UI::Score()
{
	// �X�R�A�v�Z
	m_score = ((m_itemNum[static_cast<int>(Item::coin)] * 5 +
		m_itemNum[static_cast<int>(Item::diamond)] * 5)) * 15;
}
