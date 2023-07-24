#include "PauseScreen.h"
#include <DxLib.h>
#include "Util/game.h"
#include "Util/CreateText.h"
#include "ButtonDrawer.h"

PauseScreen::PauseScreen() :
	m_updateFunc(&PauseScreen::UpdateStart),
	m_boxPos(-Game::kScreenHeight),
	m_isPauseEnd(false),
	m_isEnd(false),
	m_isButtonSettingDraw(false),
	m_isMainScene(false),
	m_isTitleScene(false),
	m_pText(nullptr),
	m_pButtonSetting(nullptr)
{
	m_pText = new CreateText;
	m_pButtonSetting = new ButtonDrawer;
}

PauseScreen::~PauseScreen()
{
	delete m_pText;
	m_pText = nullptr;
	delete m_pButtonSetting;
	m_pButtonSetting = nullptr;
}

void PauseScreen::Init()
{
	m_pText->Add(Game::kScreenWidth / 2 - 500, 250, "���j���[���߂�Ђ傤�����イ�I", 0xffff00, 80, false);
	// �X�^�[�g
	int x = Game::kScreenWidth / 2 - 250;
	int y = Game::kScreenHeight / 2 + 100 - 100;
	int addFrame = 50 + 2;
	int color = 0x000000;
	int size = 50;
	m_pText->Add(x, y, "���[�ނɂ��ǂ�", color, size, true);
	// �N���W�b�g
	y += addFrame;
	m_pText->Add(x, y, "���������߂�", color, size, true);
	y += addFrame;
	// �ݒ�
	m_pText->Add(x, y, "��������͂��߂�", color, size, true);
	// QUIT
	y += addFrame;
	m_pText->Add(x, y, "�����Ƃ�ɂ��ǂ�", color, size, true);

	m_pText->UpdatePos(0, m_boxPos);

	m_pButtonSetting->Init();
}

// �S�Ă̍X�V����
void PauseScreen::Update()
{
	// 0 �|�[�Y��ʂ��I������
	// 1 ���������`�悷��
	// 2 �Q�[�����ꂩ����Ȃ���
	// 3 �^�C�g���ɂ��ǂ�
	if (m_pText->GetSelectNo() == 0)
	{
		m_updateFunc = &PauseScreen::UpdateEnd;
		m_isButtonSettingDraw = false;
		m_pText->ResetSelectNo();
	}
	if (m_pText->GetSelectNo() == 1)
	{
		m_isButtonSettingDraw = true;
		m_pButtonSetting->Update(Game::kScreenWidth / 2, Game::kScreenHeight / 2);
		m_pText->ResetSelectNo();
	}
	if (m_pText->GetSelectNo() == 2)
	{
		m_isMainScene = true;
	}
	if (m_pText->GetSelectNo() == 3)
	{
		m_isTitleScene = true;
	}

	(this->*m_updateFunc)();
}

// �|�[�Y��ʏ��߂̏���
void PauseScreen::UpdateStart()
{
	// ��ʂ̏ォ�牺�Ɉړ�������
	if (m_boxPos < 0)
	{
		m_boxPos += 50;
		m_pText->UpdatePos(0, m_boxPos);
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
	if (m_pText->GetSelectNo() == -1)
	{
		m_pText->Update();
	}
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
		m_pText->UpdatePos(0, m_boxPos);
	}
	else
	{
		m_isButtonSettingDraw = false;
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
			0xaaaaaa, true);
	// �I����ʕ\��
	m_pText->Draw();

	// �{�^�������\��
	if (m_isButtonSettingDraw)
	{
		m_pButtonSetting->Draw();
	}
}

// �S�Ă̕ϐ���������Ԃɖ߂��܂�
void PauseScreen::Reset()
{	
	m_updateFunc = &PauseScreen::UpdateStart;
	m_boxPos = -Game::kScreenHeight;
	m_isPauseEnd = false;
	m_isEnd = false;
}
