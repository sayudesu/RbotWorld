#include "SceneDebug.h"
#include <DxLib.h>
#include "game.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyRush.h"
#include "Field.h"

namespace
{
	VECTOR kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneDebug::SceneDebug():
	m_enemyCount(0),
	m_isInvincible(false),
	m_pPlayer(nullptr),
	m_pField(nullptr)
{
	m_pEnemyRush.push_back(std::make_shared<EnemyRush>(kPos));
	m_pEnemy.push_back(std::make_shared<Enemy>());

	m_pPlayer = new Player;
	m_pField = new Field;
}

void SceneDebug::Init()
{
	// 3D�֘A�̐ݒ�
	// Z�o�b�t�@���g�p����
	SetUseZBuffer3D(true);
	// Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);
	// �|���S���̗��ʂ�`�悵�Ȃ�
	SetUseBackCulling(true);

	//�J�����̐ݒ�
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p��ݒ�i���W�A���j
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -800), VGet(0.0f, 0.0f, 0.0f));

	m_pPlayer->Init();
	m_pField->Init();
	for (auto& enemy : m_pEnemy)
	{
		enemy->Init();
	}
	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Init();
	}

	m_isInvincible = true;
}

void SceneDebug::End()
{
	for (auto& enemy : m_pEnemy)
	{
		enemy->End();
	}
	for (auto& enemy : m_pEnemyRush)
	{
		enemy->End();
	}
	m_pPlayer->End();
	m_pField->End();

	delete m_pPlayer;
	delete m_pField;
}

SceneBase* SceneDebug::Update()
{
	m_pPlayer->Update();
	m_pField->Update();

	// �G�𐶐�(�܂��G�l�~�[�폜�����Ȃ�)
	m_enemyCount++;
	if (m_enemyCount > 60 * 1)
	{
		m_enemyCount = 0;
		VECTOR pos = { 0.0f,0.0f,0.0f };
		pos.x = m_pPlayer->GetPosWorld().x + 3000;
		m_pEnemyRush.push_back(std::make_shared<EnemyRush>(pos));
	}


	for (auto& enemy : m_pEnemy) 
	{
		enemy->Update();
	}
	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Update();
	}
	for (auto& enemy : m_pEnemy)
	{
		enemy->SetPosPlayer(m_pPlayer->GetPos());
	}

	if (!m_isInvincible)
	{
		damege();
	}
	
	if (!m_pPlayer->GetInvincible()) m_isInvincible = false;
	
	UpdateFade();

	return this;
}

void SceneDebug::Draw()
{
	for (auto& enemy : m_pEnemy)
	{
		enemy->Draw();
	}
	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Draw();
	}

	m_pPlayer->Draw();
	m_pField->Draw();

	SceneBase::DrawFade();
}

bool SceneDebug::damege()
{
	for (auto& enemyRush : m_pEnemyRush)
	{
		// �v���C���[�ƃG�l�~�[�̏Փ�
		if (m_pPlayer->GetPos().left > enemyRush->GetPos().right) continue;
		
		if (m_pPlayer->GetPos().right < enemyRush->GetPos().left) continue;
		
		if (m_pPlayer->GetPos().top > enemyRush->GetPos().bottom) continue;
		
		if (m_pPlayer->GetPos().bottom < enemyRush->GetPos().top) continue;

		printfDx("�_���[�W���������\n");

		// �_���[�W�ʂ�n��
		m_pPlayer->SetDamge(enemyRush->GetAttackDamage());
		// �U���J�n
		StartJoypadVibration(DX_INPUT_PAD1, 100, 60, 0);
		// �_���[�W���������
		m_isInvincible = true;

		return true;
	}

	return false;
	
}

