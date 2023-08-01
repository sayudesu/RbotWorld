#include "SceneTitle.h"
#include "SceneMain.h"
#include <DxLib.h>
#include "../Util/CreateText.h"
#include "../Util/DrawTitleModel.h"
#include "../Util/game.h"
#include "../Util/Pad.h"
#include "../Util/Sound.h"
#include "../ButtonDrawer.h"
#include "../CreditDrawer.h"
#include "../FieldOne.h"


#include "../Util/Shadow.h"

namespace
{
	// �^�C�g��
	const char* kTextTitle = "��ڂ��Ƃ�[���";
	// �{�^���U��
	const char* const kTextStart = "�����[��";
	// �e�X�g�p
	const char* const kTextTest = "���ꂶ����";
	const char* const kTextTest2 = "�ڂ��񂹂߂�";

	const char* const kFileName = "Data/Img/org2.png";
	const char* const kFileName2= "Data/Img/org2Test2_n.png";


	const char* const kTextQuit= "��߂�";
}

SceneTitle::SceneTitle()
{
	m_pDrawModeler = new TitleDrawModeler;
	m_pShadow = new Shadow(kFileName, kFileName2);
	m_pText = new CreateText;
	m_pButtonDrawer = new ButtonDrawer;
	m_pCreditDrawer = new CreditDrawer;
}

SceneTitle::~SceneTitle()
{
	delete m_pDrawModeler;
	delete m_pText;
	delete m_pButtonDrawer;
	delete m_pCreditDrawer;
}

void SceneTitle::Init()
{
	// BGM �Đ�
	Sound::startBgm(Sound::SoundId_Title, 50);
	m_pButtonDrawer->Init();
	m_pCreditDrawer->Init();
	// �e�L�X�g�ǉ� //
	// �^�C�g��
	m_pText->Add(Game::kScreenWidth/2 - 500,250 ,kTextTitle,0xffff00,130,false);
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
	if (m_pText->GetSelectNo() == -1)
	{
		m_pText->Update();
	}

	// �V�[����I��������ړ����f���̊J�n����
	if (m_pText->GetSelectNo() != -1)
	{
		m_pDrawModeler->SetStartPos(true);
	}
	// �Q�[���v���C��ʂɈړ�
	if (m_pText->GetSelectNo() == 0)
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
	if (m_pText->GetSelectNo() == 1)
	{
		if (m_pDrawModeler->GetSceneChange())
		{
			// �����X���C�h
			static int yS = -Game::kScreenHeight;
			static bool end = false;
			// �ォ�牺�ɃX���C�h
			if (yS < 0 && !end)
			{
				yS += 30;
			}

			// �{�^��������ʂ̍��W
			int x = Game::kScreenWidth / 2;
			int y = Game::kScreenHeight / 2 + yS;
			// �{�^��������ʂ̈ʒu
			m_pCreditDrawer->Update(x, y);

			// �߂�
			if (Pad::isTrigger(PAD_INPUT_1) && !end)
			{
				end = true;
			}
			// �������ɃX���C�h
			if (end)
			{
				if (yS > -Game::kScreenHeight)
				{
					yS -= 30;
				}
				else
				{
					end = false;
					yS = -Game::kScreenHeight;
					m_pText->ResetSelectNo();
				}
			}
		}
	}
	else
	{
		m_pCreditDrawer->Update(-Game::kScreenWidth / 2 + 100, 1000);
	}
	// �ݒ��ʂɈړ�
	if (m_pText->GetSelectNo() == 2)
	{ 
		if (m_pDrawModeler->GetSceneChange())
		{
			// �����X���C�h
			static int yS = -Game::kScreenHeight;
			static bool end = false;
			// �ォ�牺�ɃX���C�h
			if (yS < 0 && !end)
			{
				yS += 30;
			}

			// �{�^��������ʂ̍��W
			int x = Game::kScreenWidth / 2 + 100;
			int y = Game::kScreenHeight / 2 + yS;
			// �{�^��������ʂ̈ʒu
			m_pButtonDrawer->Update(x, y);

			// �߂�
			if (Pad::isTrigger(PAD_INPUT_1)&&!end)
			{
				end = true;
			}
			// �������ɃX���C�h
			if (end)
			{
				if (yS > -Game::kScreenHeight)
				{
					yS -= 30;
				}
				else
				{
					end = false;
					yS = -Game::kScreenHeight;
					m_pText->ResetSelectNo();
				}
			}
		}
	}
	else
	{
		m_pButtonDrawer->Update(-Game::kScreenWidth / 2 + 100, 1000);
	}
	// �Q�[���I��
	if (m_pText->GetSelectNo() == 3)
	{
		if (m_pDrawModeler->GetSceneChange())
		{
			DxLib::DxLib_End();
		}
	}

	// �X���C�h���J����
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
	m_pButtonDrawer->Draw();
	m_pCreditDrawer->Draw();
	// �X���C�h��`��
	SceneBase::DrawSliderDoor();
}
