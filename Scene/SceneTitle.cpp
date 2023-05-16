#include "SceneTitle.h"
#include "SceneDebug.h"
#include <DxLib.h>
#include "CreateText.h"
#include "game.h"
#include "Pad.h"

namespace
{
	// �^�C�g��
	const char* const kTextTitle = "[RobotWorld]";
	// �{�^���U��
	const char* const kTextStart = "�u A �v�{�^���ŊJ�n�I";
	// �e�X�g�p
	const char* const kTextTest = "�h��Ȃ��當�����㏸���ď�����`";
}

SceneTitle::SceneTitle():
	m_size(0),
	m_color(0),
	m_pos(0.0f, 0.0f, 0.0f)
{
	m_pText.push_back(std::make_shared<CreateText>());
	m_pText.push_back(std::make_shared<CreateText>());
}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return(new SceneDebug);
	}

	return this;
}

void SceneTitle::Draw()
{

	// ����������@for�@�ŉ񂵂܂��B
	m_pos.x = static_cast<float>(Game::kScreenWidth) / 2.0f - 250.0f;
	m_pos.y = static_cast<float>(Game::kScreenHeight) / 2.0f - 300.0f;
	m_size = 100;
	m_color = 0xffff00;

	//// �^�C�g���\��
	m_pText[0]->DrawDef(m_pos,
		kTextTitle, m_size, m_color);

	m_pos.x = static_cast<float>(Game::kScreenWidth) / 2.0f - 200.0f;
	m_pos.y = static_cast<float>(Game::kScreenHeight) / 2.0f + 300.0f;
	m_size = 32;
	m_color = 0xff0000;

	//// �X�^�[�g�{�^���\��
	m_pText[1]->DrawDef(m_pos,
		kTextStart, m_size, m_color);

	m_pos.x = static_cast<float>(Game::kScreenWidth) / 2.0f - 200.0f;
	m_pos.y = static_cast<float>(Game::kScreenHeight) / 2.0f + 300.0f;
	m_size = 32;
	m_color = 0xff0000;

	//// �����e�X�g
	m_pText[0]->DrawUp(m_pos,
		kTextTest, m_size, 8.0f,m_color);
}
