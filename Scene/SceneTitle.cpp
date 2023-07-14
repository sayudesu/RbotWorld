#include "SceneTitle.h"
#include "SceneMain.h"
#include <DxLib.h>
#include "CreateText.h"
#include "DrawTitleModel.h"
#include "game.h"
#include "Pad.h"
#include "Sound.h"

#include "FieldOne.h"


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


	const char* const kTextQuit= "QUIT";
}

SceneTitle::SceneTitle()
{
	m_pDrawModeler = new TitleDrawModeler;
	m_pShadow = new Shadow(kFileName, kFileName2);
	m_pText = new CreateText;
}

SceneTitle::~SceneTitle()
{
	delete m_pDrawModeler;
	delete m_pText;
}

void SceneTitle::Init()
{
	// BGM �Đ�
	Sound::startBgm(Sound::SoundId_Title, 50);

	// �e�L�X�g�ǉ� //
	// �^�C�g��
	m_pText->Add(Game::kScreenWidth/2 - 400,250 ,kTextTitle,0xffff00,130,false);
	// �X�^�[�g
	int x = Game::kScreenWidth / 2 - 250;
	int y = Game::kScreenHeight / 2 + 100;
	int addFrame = 50 + 2;
	int color = 0x000000;
	int size = 50;
	m_pText->Add(x,y, kTextStart, color, size, true);
	// �N���W�b�g
	y += addFrame;
	m_pText->Add(x, y, kTextTest, color, size, true);
	y += addFrame;
	// �ݒ�
	m_pText->Add(x, y, kTextTest2, color, size, true);
	// QUIT
	y += addFrame;
	m_pText->Add(x, y, kTextQuit, color, size, true);
}

void SceneTitle::End()
{
	// BGM ��~
	Sound::stopBgm(Sound::SoundId_Title);
}

SceneBase* SceneTitle::Update()
{
	// 2D�V�F�[�_�[�̍X�V
//	m_pShadow->Update();
	// ���f���̍X�V
	m_pDrawModeler->Update();

	m_pText->Update();
	// �V�[����I��������ړ����f���̊J�n����
	if (m_pText->SelectNo() != -1)
	{
		m_pDrawModeler->SetStartPos(true);
	}
	// �Q�[���v���C��ʂɈړ�
	if (m_pText->SelectNo() == 0)
	{
		m_isSliderOpen = true;
		if (m_pDrawModeler->GetSceneChange())
		{			
			m_pField = std::make_shared<FieldBase>();
			if (SceneBase::UpdateSliderClose())
			{
				return(new SceneMain(m_pField));
				
			}
		}
	}
	// �N���W�b�g��ʂɈړ�
	if (m_pText->SelectNo() == 1)
	{
		if (m_pDrawModeler->GetSceneChange())
		{
			DrawString(1000, 100, "�܂��N���W�b�g�\�L�͂ł��Ă��܂���B", 0xffffff);
		}
	}
	// �ݒ��ʂɈړ�
	if (m_pText->SelectNo() == 2)
	{ 
		if (m_pDrawModeler->GetSceneChange())
		{
			DrawString(1000, 100, "�܂��ݒ��ʂ͂ł��Ă��܂���B", 0xffffff);
		}
	}
	// �Q�[���I��
	if (m_pText->SelectNo() == 3)
	{
		if (m_pDrawModeler->GetSceneChange())
		{
			DxLib::DxLib_End();
		}
	}

	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);
	// 3D���f���`��
	m_pDrawModeler->Draw();
	// 2D�V�F�[�_�[�`��
//	m_pShadow->Draw();
	// �e�L�X�g�`��
	m_pText->Draw();

	DrawBox(Game::kScreenWidth / 2 - 30, Game::kScreenHeight / 2 - 30, Game::kScreenWidth / 2 + 30, Game::kScreenHeight / 2 + 30, 0xffffff, true);

	// �X���C�h��`��
	SceneBase::DrawSliderDoor();
}
