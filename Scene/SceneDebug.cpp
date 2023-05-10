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
	m_isCheckHit(false),
	m_isCheckHitAttack(false),
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
	for (auto& enemy : m_pEnemyRush)
	{
		enemy->Init();
	}
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
	if (m_enemyCount > 60)
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
	for (auto& enemy : m_pEnemyRush)
	{
		enemy->Update();
	}
	for (auto& enemy : m_pEnemy)
	{
		enemy->SetPosPlayer(m_pPlayer->GetPos());
	}
	/*
	for (auto& enemy : m_pEnemy)
	{
		// �v���C���[�ƃG�l�~�[�̏Փ�
		if ((m_pPlayer->GetPos().right > enemy->GetPos().left) &&
			(m_pPlayer->GetPos().left < enemy->GetPos().right))
		{
			if ((m_pPlayer->GetPos().bottom > enemy->GetPos().top) &&
				(m_pPlayer->GetPos().top < enemy->GetPos().bottom))
			{
				// �_���[�W�ʂ�n��
				m_pPlayer->SetDamge(enemy->GetAttackDamage());
				// �U���J�n
				StartJoypadVibration(DX_INPUT_PAD1, 100, 60, 0);
			}
		}

		// �v���C���[�̍U��
		if ((m_pPlayer->GetPosAttack().right > enemy->GetPos().left) &&
			(m_pPlayer->GetPosAttack().left < enemy->GetPos().right))
		{
			if ((m_pPlayer->GetPosAttack().bottom > enemy->GetPos().top) &&
				(m_pPlayer->GetPosAttack().top < enemy->GetPos().bottom))
			{
				// �_���[�W�ʂ�n��
				enemy->SetDamge(m_pPlayer->GetAttackDamage());
			}
		}

	}
	*/
	for (auto& enemy : m_pEnemyRush)
	{
		// �v���C���[�ƃG�l�~�[�̏Փ�
		if ((m_pPlayer->GetPos().right > enemy->GetPos().left) &&
			(m_pPlayer->GetPos().left < enemy->GetPos().right))
		{
			if ((m_pPlayer->GetPos().bottom > enemy->GetPos().top) &&
				(m_pPlayer->GetPos().top < enemy->GetPos().bottom))
			{
				if (!m_isCheckHit)
				{
					// �_���[�W�ʂ�n��
					m_pPlayer->SetDamge(enemy->GetAttackDamage());
					// �U���J�n
					StartJoypadVibration(DX_INPUT_PAD1, 100, 60, 0);

					m_isCheckHit = true;
				}
			}
		}
		else
		{
			m_isCheckHit = false;
		}
		/*
		// �v���C���[�̍U��
		if ((m_pPlayer->GetPosAttack().right > enemy->GetPos().left) &&
			(m_pPlayer->GetPosAttack().left < enemy->GetPos().right))
		{
			if ((m_pPlayer->GetPosAttack().bottom > enemy->GetPos().top) &&
				(m_pPlayer->GetPosAttack().top < enemy->GetPos().bottom))
			{
				if (!m_isCheckHitAttack)
				{
					// �_���[�W�ʂ�n��
					enemy->SetDamge(m_pPlayer->GetAttackDamage());
				}
				m_isCheckHitAttack = true;
			}
		}
		else
		{
			m_isCheckHitAttack = false;
		}
		*/
	}

	
	
	UpdateFade();

	return this;
}

void SceneDebug::Draw()
{
	for (auto& enemy : m_pEnemy)
	{
		enemy->Draw();
	}
	for (auto& enemy : m_pEnemyRush)
	{
		enemy->Draw();
	}
	m_pPlayer->Draw();
	m_pField->Draw();
	SceneBase::DrawFade();
}

