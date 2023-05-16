#include "SceneDebug.h"
#include <DxLib.h>
#include "game.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/EnemyRush.h"
#include "Object/Field.h"

#include "Util/Vec3.h"

namespace
{
	// �����ʒu
	Vec3 kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneDebug::SceneDebug():
	m_slowCount(0),
	m_enemyCount(0),
	m_isInvincible(false),
	m_isEnemyDamageHit(false),
	m_pPlayer(nullptr),
	m_pField(nullptr)
{
	m_pEnemyRush.push_back(std::make_shared<EnemyRush>(kPos));

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

	m_pPlayer->Init();
	m_pField->Init(); 

	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Init();
	}

	m_isInvincible = true;
}

void SceneDebug::End()
{
	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->End();
	}
	m_pPlayer->End();
	m_pField->End();

	delete m_pPlayer;
	delete m_pField;
}

// �X�V //
SceneBase* SceneDebug::Update()
{
	m_pField->Update();

	// �X���[���[�V��������
	m_slowCount = (m_slowCount += 1) % m_pPlayer->GetSlowWorld();
	if (m_slowCount == 0)
	{
		// �v���C���[�̍X�V
		m_pPlayer->Update();
		for (auto& enemyRush : m_pEnemyRush)
		{
			enemyRush->Update();

			// �G����ʍ��W����o����폜
			if (enemyRush->GetPos().left < 0)
			{
				enemyRush->End();
			}
		}

		if (m_enemyCount == 0)
		{
			m_tempRand = GetRand(2);
		//	printfDx("aaaaaaaaaaaaa");
			switch (m_tempRand)
			{
			case 0:
				m_tempRand = 1;
			case 1:
				m_tempRand = 2;
			case 2:
				m_tempRand = 3;
			case 3:
				m_tempRand = 4;
			case 4:
				m_tempRand = 5;
			default:
				m_tempRand = 1;
				break;
			}
		}
		// �G�𐶐�(�܂����S�ȃG�l�~�[�폜�����Ȃ�)
		m_enemyCount++;
		if (m_enemyCount > 60 * m_tempRand)
		{
			m_enemyCount = 0;
			Vec3 pos = { m_pPlayer->GetPosWorld().x,0.0f,0.0f };
			pos.x += 3000;
			m_pEnemyRush.push_back(std::make_shared<EnemyRush>(pos));
		}
	}

	// �v���C���[�̑���
	m_pPlayer->UpdateControl();

	// ���G���ԊO�ɓG�ɓ������Ă��邩�̔���
	if (!m_isInvincible)
	{
		for (auto & enemyRush : m_pEnemyRush)
		{
			damege(
				m_pPlayer->GetPos().left,//�v���C���[�̍��W
				m_pPlayer->GetPos().top,
				m_pPlayer->GetPos().right,
				m_pPlayer->GetPos().bottom,
				enemyRush->GetPos().left,// �G�̍��W
				enemyRush->GetPos().top,
				enemyRush->GetPos().right,
				enemyRush->GetPos().bottom,
				true,// �_���[�W���󂯂鑤(�v���C���[ : true�G: false�j
				enemyRush->GetAttackDamage()
			);	

			//damege(
			//	m_pPlayer->GetPosAttack().left,//�v���C���[�̍��W
			//	m_pPlayer->GetPosAttack().top,
			//	m_pPlayer->GetPosAttack().right,
			//	m_pPlayer->GetPosAttack().bottom,
			//	enemyRush->GetPos().left,// �G�̍��W
			//	enemyRush->GetPos().top,
			//	enemyRush->GetPos().right,
			//	enemyRush->GetPos().bottom,
			//	false,// �_���[�W���󂯂鑤(�v���C���[ : true�G: false�j
			//	enemyRush->GetAttackDamage()
			//);

			//if (m_isEnemyDamageHit)
			//{
			//	enemyRush->SetDamage(m_pPlayer->GetAttackDamage());
			//	m_isEnemyDamageHit = false;
			//}
		}

	}
	// ���G���Ԃ̒���
	if (!m_pPlayer->GetInvincible()) m_isInvincible = false;

	// �t�F�C�h����
	UpdateFade();

	return this;
}
// �`�� //
void SceneDebug::Draw()
{
	// 3D��Ԃ�2D�摜�ǂݍ��܂���
#if false	

	// �摜�̓ǂݍ���
	int GrHandle = LoadGraph("Title.png");

	VECTOR pos = { m_pPlayer->GetPosWorld().x,m_pPlayer->GetPosWorld().y,m_pPlayer->GetPosWorld().z };
	pos.z += 200.0f;
	// �R�c��ԏ�ɉ摜��`��
	DrawBillboard3D(pos, 0.5f, 0.5f, 120.0f * 30, 0.0f, GrHandle, true);

//	pos = { 0.0f,0.0f,pos.z };
//	DrawExtendGraph3D(pos.x, pos.y, pos.z, Game::kScreenWidth, Game::kScreenHeight, GrHandle, true);

	//DrawGraph3D(pos.x, pos.y, pos.z, GrHandle,true);

	DeleteGraph(GrHandle);

#endif	
	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Draw();
	}

	m_pPlayer->Draw();
	m_pField->Draw();

	// �t�F�C�h����
	SceneBase::DrawFade();
}

// �G�Ƃ̏Փ˔��� //
bool SceneDebug::damege(
	int left, int top, int right, int bottom,
	int left1,int top1,int right1,int bottom1,
	bool playerOrEnemy ,int damage)
{

	// �v���C���[�ƃG�l�~�[�̏Փ�
	if (left > right1) return true;;
		
	if (right < left1) return true;;
		
	if (top > bottom1) return true;;
		
	if (bottom <top1) return true;;

	if (playerOrEnemy)
	{
		// �_���[�W�ʂ�n��
		m_pPlayer->SetDamge(damage);
		// �U���J�n
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 60, -1);
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 60, 1);
		// �_���[�W���������
		m_isInvincible = true;
	}
	else
	{
		m_isEnemyDamageHit = true;
	}

	return false;
}

