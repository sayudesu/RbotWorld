#include "CreateText.h"
#include <DxLib.h>
#include "Util/Pad.h"
#include <cassert>

namespace 
{
	// �t�H���g�֘A
	const char* kFont = "Data/Fonts/851letrogo_007.ttf";// �t�H���g�p�X
	const char* kFontName = "851���g���S";// �t�H���g�̖��O
}

//////////////////////
// CreateText�N���X //
//////////////////////
CreateText::CreateText():
	m_isSelect(false),
	selectNum(-1),
	selectNow(0),
	m_selectNo(-1),
	selectRad(0)
{

}

CreateText::~CreateText()
{
	for (auto& text : m_pText)
	{
		text.reset();
	}
}

void CreateText::Add(int x, int y, const char* text, int color, int size,bool frame)
{
	// �C���X�^���X���쐬
	m_pText.push_back(std::make_shared<Text>(x,y,text,color,size,frame));

	if (frame)selectNum++;
}

void CreateText::Update()
{
	if (!m_isSelect)
	{
		// �I��
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			if (selectNow > 0)
			{
				selectNow--;
			}
			else
			{
				selectNow = selectNum;
			}

			m_isSelect = false;
		}
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			if (selectNow < selectNum)
			{
				selectNow++;
			}
			else
			{
				selectNow = 0;
			}

			m_isSelect = false;
		}
	}
	
	// �I��������
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isSelect = true;
	}

	// �I��������100�t���[����ɂ��̉�ʂɐ؂�ւ��
	if (m_isSelect)
	{
		m_pText[selectNow + 1]->SetSelectRadius(selectRad += 6);

		for (int i = 0; i < m_pText.size(); i++)
		{
			m_pText[selectNow + 1]->BlendMode();
		}

		if (selectRad > 100)
		{
			m_selectNo = selectNow;
			m_isSelect = false;
		}
	}

	// �S�đI���t���[����\�������Ȃ�
	for (int i = 0; i < m_pText.size(); i++)
	{
		m_pText[i]->SetSelectFrame(false);
	}
	// �I�𒆂̕����͑I���t���[����\��������
	m_pText[selectNow + 1]->SetSelectFrame(true);

#if true
	// �f�o�b�O�p
	if (selectRad > 100)
	{
		m_isSelect = false;
		selectRad = 0;

		for (int i = 0; i < m_pText.size(); i++)
		{
			m_pText[i]->SetSelectRadius(0);
		}
	}

#endif
}

void CreateText::UpdatePos(int x, int y)
{
	for (auto& text : m_pText)
	{
		text->UpdatePos(x, y);
	}
}

void CreateText::Draw()
{
	for (auto& text : m_pText)
	{
		text->Draw();
	}
}

void CreateText::ResetSelectNo()
{
	m_selectNo = -1;
}

////////////////
// Text�N���X //
////////////////
Text::Text(int x, int y, const char* text, int color, int size, bool frame) :
	m_x(x),
	m_y(y),
	m_changePosX(0),
	m_changePosY(0),
	m_text(text),
	m_color(color),
	m_isFrame(frame),
	m_isSelect(false),
	m_rad(0),
	m_blend(255)
{
	// �t�H���g�f�[�^���쐬
	m_fontHandle = CreateFontToHandle(kFontName, size, 3);
	assert(m_fontHandle != -1);
}

Text::~Text()
{
	DeleteFontToHandle(m_fontHandle);
}

void Text::UpdatePos(int x,int y)
{
	m_changePosX = x;
	m_changePosY = y;
}

void Text::Draw()
{
	// �g�g��
	if (m_isFrame)
	{
		DrawBox(m_x + m_changePosX - 1, m_y + m_changePosY - 1,
			m_x + m_changePosX + 500 + 1, m_y + m_changePosY + 50 + 1, 0xff0000, true);
		DrawBox(m_x + m_changePosX, m_y + m_changePosY,
			m_x + m_changePosX + 500, m_y + m_changePosY + 50, 0xffffff, true);
	}
	// �I�����Ă��邩������
	if (m_isSelect)
	{
		DrawBox(m_x + m_changePosX, m_y + m_changePosY,
			m_x + m_changePosX + 500, m_y + m_changePosY + 50, 0x00ffff, true);
	}

	// �`��u�����h���[�h�����u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, m_blend);
	// �t�H���g�f�[�^���g��������`��
	DrawStringToHandle(m_x + m_changePosX, m_y + m_changePosY, m_text, m_color, m_fontHandle);
	// �`��u�����h���[�h���m�[�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if(m_rad != 0)DrawCircle(m_x + m_changePosX + 250, m_y + m_changePosY + 25, m_rad, 0xff0000,false);
}

// �I���t���[����\�����邩�ǂ���
void Text::SetSelectFrame(bool isSelect)
{
	m_isSelect = isSelect;
}

void Text::SetSelectRadius(int rad)
{
	m_rad = rad;
}

void Text::BlendMode()
{
	m_blend--;
}
