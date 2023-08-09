#include "SceneGameClear.h"
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
	const char* kGameCrearText = "���[�ނ��肠�I";
	const char* kScoreText     = "������   %d";
	const char* kCoinText      = "������̂���   %d";
	const char* kDiamondText   = "�_�C���̂���   %d";

	// BGM�̉���
	constexpr int kBgmVolume = 50;

}

SceneGameClear::SceneGameClear(int score,int coinNum,int diamondNum):
	m_score(score),
	m_coinNum(coinNum),
	m_diamondNum(diamondNum),
	m_buckLine(0),
	m_buckLineCount(0),
	m_sliderPos(-Game::kScreenHeight),
	m_sliderEndPos(0),
	m_pStringScore(nullptr),
	m_isChangeScene(false)
{
	m_pStringScore = new StringStatic();

	m_isStringSlider = true;
}

SceneGameClear::~SceneGameClear()
{
	// BGM ��~
	Sound::stopBgm(Sound::SoundId_Main);
}

void SceneGameClear::Init()
{
	m_pStringScore->InitFont(kFont, kFontName);

	m_pStringScore->AddStatic(Game::kScreenWidth / 2 - 500.0f, Game::kScreenHeight / 2 - 350.0f,
		kGameCrearText, m_score, 0xffff00, 96 + 32 + 16);

	m_pStringScore->AddStatic(Game::kScreenWidth / 2 - 350.0f, Game::kScreenHeight / 2 - 50.0f,
		kScoreText, m_score, 0xffffff, 64 + 32 + 16);

	m_pStringScore->AddStatic(Game::kScreenWidth / 2 - 300.0f, Game::kScreenHeight / 2 + 150.0f,
		kCoinText, m_coinNum, 0xffffaa, 64);

	m_pStringScore->AddStatic(Game::kScreenWidth / 2 - 300.0f, Game::kScreenHeight / 2 + 250.0f,
		kDiamondText, m_diamondNum, 0x0000aa, 64);

	// BGM�Đ�
	Sound::startBgm(Sound::SoundId_Main, kBgmVolume);
}

void SceneGameClear::End()
{
	delete m_pStringScore;
}

SceneBase* SceneGameClear::Update()
{
	// �X���C�h�����̍s��܂œ�����
	if (m_isStringSlider && m_sliderPos < m_sliderEndPos)
	{
		m_sliderPos += 15;
		m_pStringScore->UpdateStatic(0, Game::kScreenWidth / 2 - 500.0f, Game::kScreenHeight / 2 - 350.0f + m_sliderPos, 0);
		m_pStringScore->UpdateStatic(1, Game::kScreenWidth / 2 - 350.0f, Game::kScreenHeight / 2 - 50.0f + m_sliderPos, m_score);
		m_pStringScore->UpdateStatic(2, Game::kScreenWidth / 2 - 300.0f, Game::kScreenHeight / 2 + 150.0f + m_sliderPos, m_coinNum);
		m_pStringScore->UpdateStatic(3, Game::kScreenWidth / 2 - 300.0f, Game::kScreenHeight / 2 + 250.0f + m_sliderPos, m_diamondNum);
	}

	m_buckLineCount++;
	if (m_buckLineCount > 5)
	{
		m_buckLineCount = 0;
		if(m_buckLine < 450)m_buckLine += 50;
	}
	
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// �X���C�h���ĊJ������
		m_isStringSlider = true;
		// �X���C�h�̐������w��
		m_sliderEndPos = Game::kScreenHeight;
		// ���̃V�[���ڍs���邽��
		m_isChangeScene = true;

		m_isSliderOpen = true;
	}

	if (m_isChangeScene)
	{
		// �X���C�h���J���ƃV�[�����ڍs������
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneTitle;
		}
	}
	// �X���C�h���J����
	SceneBase::UpdateSlider(m_isSliderOpen);
	return this;
}

void SceneGameClear::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);

	DrawBox(100, 100, 
			Game::kScreenWidth - 100, Game::kScreenHeight - 100,
			0x999999, true);

	for (int i = 100; i < m_buckLine; i+= 10)
	{
		DrawBox(i, i,
			Game::kScreenWidth - i, Game::kScreenHeight - i,
			0xfaff00, false);

	}

	for (int i = 0; i < 4; i++)
	{
		m_pStringScore->DrawStatic(i);
	}

	SceneBase::DrawSliderDoor();
}
