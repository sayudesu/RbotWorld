#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "../Util/game.h"
#include "../Util/Pad.h"
#include "../Util/Achievement.h"
#include "../Util/Sound.h"

namespace
{
	// �t�H���g�֘A
	const char* kFont = "Data/Fonts/851letrogo_007.ttf";// �t�H���g�p�X
	const char* kFontName = "851���g���S";// �t�H���g�̖��O
	const char* kGameOverText = "���[�ނ��[�΁[�I";
	const char* kGameOverNextText = "�������傩�炾�I";

}

SceneGameOver::SceneGameOver():
	m_isChangeScene(false),
	m_buckLineCount(0),
	m_buckLine(0),
	m_sliderPos(-Game::kScreenHeight),
	m_sliderEndPos(0)
{
	m_pStringScore = new StringStatic();

	m_isStringSlider = true;
}

SceneGameOver::~SceneGameOver()
{
	delete m_pStringScore;
}

void SceneGameOver::Init()
{
	m_pStringScore->InitFont(kFont, kFontName);

	m_pStringScore->AddStatic(Game::kScreenWidth / 2 - 500.0f, Game::kScreenHeight / 2 - 350.0f,
		kGameOverText, 0, 0xffff00, 96 + 32 + 16);

	m_pStringScore->AddStatic(Game::kScreenWidth / 2 - 450.0f, Game::kScreenHeight / 2 - 50.0f,
		kGameOverNextText, 0, 0xffffff, 64 + 32 + 16);

	// BGM�Đ�
	Sound::startBgm(Sound::SoundId_Main, 50);
}

void SceneGameOver::End()
{
}

SceneBase* SceneGameOver::Update()
{
	// �X���C�h�����̍s��܂œ�����
	if (m_isStringSlider && m_sliderPos < m_sliderEndPos)
	{
		m_sliderPos += 15;
		m_pStringScore->UpdateStatic(0, Game::kScreenWidth / 2 - 500.0f, Game::kScreenHeight / 2 - 350.0f + m_sliderPos, 0);
		m_pStringScore->UpdateStatic(1, Game::kScreenWidth / 2 - 450.0f, Game::kScreenHeight / 2 - 50.0f + m_sliderPos, 0);
	}

	// ���̃V�[���Ɉڍs���邩�ǂ���
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// �X���C�h���ĊJ������
		m_isStringSlider = true;
		// �X���C�h�̐������w��
		m_sliderEndPos = Game::kScreenHeight;

		m_isChangeScene = true;
		m_isSliderOpen = true;
	}

	// �X���C�h����ăV�[����؂�ւ���
	if (m_isChangeScene)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneTitle;	
		}
	}

	m_buckLineCount++;
	if (m_buckLineCount > 5)
	{
		m_buckLineCount = 0;
		if (m_buckLine < 450)m_buckLine += 50;
	}

	// �X���C�h���J����
	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneGameOver::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);

	for (int i = 100; i < m_buckLine; i += 10)
	{
		DrawBox(i, i,
			Game::kScreenWidth - i, Game::kScreenHeight - i,
			0xff0000, false);

	}
	for (int i = 0; i < 2; i++)
	{
		m_pStringScore->DrawStatic(i);
	}

	// �X���C�h��`��
	SceneBase::DrawSliderDoor();
}
