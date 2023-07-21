#include "PauseScreen.h"
#include <DxLib.h>
#include "Util/game.h"

PauseScreen::PauseScreen() :
	m_updateFunc(&PauseScreen::UpdateStart),
	m_boxPos(-Game::kScreenHeight),
	m_isPauseEnd(false),
	m_isEnd(false)
{
}

PauseScreen::~PauseScreen()
{
}

// �S�Ă̍X�V����
void PauseScreen::Update()
{
	(this->*m_updateFunc)();
}

// �|�[�Y��ʏ��߂̏���
void PauseScreen::UpdateStart()
{
	// ��ʂ̏ォ�牺�Ɉړ�������
	if (m_boxPos < 0)
	{
		m_boxPos += 50;
	}
	else
	{
		// ���݃|�[�Y���
		m_isPauseEnd = false;
		// �֐���؂�ւ���
		m_updateFunc = &PauseScreen::UpdateMain;
	}
}

// �|�[�Y��ʒ�
void PauseScreen::UpdateMain()
{
	// �|�[�Y��ʂł͂Ȃ��Ȃ����ꍇ
	// �|�[�Y��ʏI���p�֐��ɐ؂�ւ���
	if (m_isPauseEnd)
	{
		m_updateFunc = &PauseScreen::UpdateEnd;
	}
}

// �|�[�Y��ʏI���p�֐�
void PauseScreen::UpdateEnd()
{
	// ��Ɉړ�������
	if (m_boxPos > -Game::kScreenHeight)
	{
		m_boxPos -= 50;
	}
	else
	{
		m_isPauseEnd = false;
		m_isEnd = true;
	}
}
// �`��
void PauseScreen::Draw()
{
	// �l�p�`��`��
	DrawBox(500, 300 + m_boxPos,
			Game::kScreenWidth -500,Game::kScreenHeight - 300 + m_boxPos,
			0xffffff, true);
}

// �S�Ă̕ϐ���������Ԃɖ߂��܂�
void PauseScreen::Reset()
{	
	m_updateFunc = &PauseScreen::UpdateStart;
	m_boxPos = -Game::kScreenHeight;
	m_isPauseEnd = false;
	m_isEnd = false;
}
