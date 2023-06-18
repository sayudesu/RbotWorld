#include "SceneTitle.h"
#include "SceneDebug.h"
#include <DxLib.h>
#include "CreateText.h"
#include "DrawTitleModel.h"
#include "game.h"
#include "Pad.h"
#include "Sound.h"

#include "Shadow.h"

namespace
{
	// �^�C�g��
	const char* kTextTitle = "[RobotWorld]";
	// �{�^���U��
	const char* const kTextStart = "Start";
	// �e�X�g�p
	const char* const kTextTest = "Credit";
	const char* const kTextTest2 = "Setting";

	const char* const kFileName = "Data/Img/org2.png";
	const char* const kFileName2= "Data/Img/org2Test2_n.png";
}

SceneTitle::SceneTitle()
{
	m_pDrawModel = new DrawTitleModel;
	m_pShadow = new Shadow(kFileName, kFileName2);
	m_pText = new CreateText;
}

SceneTitle::~SceneTitle()
{
	delete m_pDrawModel;
}

void SceneTitle::Init()
{
	// BGM �Đ�
	Sound::startBgm(Sound::SoundId_Title, 50);

	// �e�L�X�g�ǉ� //
	// �^�C�g��
	m_pText->Add(Game::kScreenWidth/2 - 400,250 ,kTextTitle,0xffff00,130,false);
	// �X�^�[�g
	m_pText->Add(Game::kScreenWidth / 2 - 300,Game::kScreenHeight / 2 + 100, kTextStart,0x000000, 50, true);
	// �N���W�b�g
	m_pText->Add(Game::kScreenWidth / 2 - 300, Game::kScreenHeight / 2 + 100 + 50 + 2, kTextTest, 0x000000, 50, true);
	// �ݒ�
	m_pText->Add(Game::kScreenWidth / 2 - 300, Game::kScreenHeight / 2 + 100 + 50 + 50 + 4, kTextTest2, 0x000000, 50, true);
}

void SceneTitle::End()
{
	// BGM ��~
	Sound::stopBgm(Sound::SoundId_Title);
}

SceneBase* SceneTitle::Update()
{

	m_pShadow->Update();

	m_pDrawModel->Update();

	m_pText->Update();

	if (m_pText->SelectNo() == 0)
	{
		return(new SceneDebug);
	}
	if (m_pText->SelectNo() == 1)
	{
		DrawString(1000, 100, "�܂��N���W�b�g�\�L�͂ł��Ă��܂���B", 0xffffff);
	}
	if (m_pText->SelectNo() == 2)
	{ 
		DrawString(1000, 100, "�܂��ݒ��ʂ͂ł��Ă��܂���B", 0xffffff);
	}

	return this;
}

void SceneTitle::Draw()
{
	// 3D���f���`��
	m_pDrawModel->Draw();
	// 2D�V�F�[�_�[�`��
	m_pShadow->Draw();
	// �e�L�X�g�`��
	m_pText->Draw();
}
