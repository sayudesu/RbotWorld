#include "SceneDebug.h"
#include <DxLib.h>
#include "game.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/EnemyRush.h"
#include "Object/Field.h"
#include "SceneTitle.h"

#include "Util/Vec3.h"

#include "Sound.h"

namespace
{
	// �����ʒu
	Vec3 kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneDebug::SceneDebug():
	m_slowCount(0),
	m_enemyCount(0),
	m_isInvincible(false),
	m_pPlayer(nullptr),
	m_pField(nullptr)
{
	m_pEnemyRush.push_back(std::make_shared<EnemyRush>(kPos));
	m_pPlayer = new Player;
	m_pField = new Field;
}

SceneDebug::~SceneDebug()
{
	delete m_pPlayer;
	delete m_pField;

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

	Sound::startBgm(Sound::SoundId_Main, 50);
}

void SceneDebug::End()
{

	Sound::stopBgm(Sound::SoundId_Main);

	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->End();
	}

	m_pPlayer->End();

	m_pField->End();
}

// �X�V //
SceneBase* SceneDebug::Update()
{
	m_pField->Update();

	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Update();
	}

//	printfDx("%d\n", m_pPlayer->GetSlowWorld());
	// �X���[���[�V��������
	
	///////////////////////////////
	// �����̓v���C���[cpp�ɒu�� //
	//     �v���C���[�̑���      //
	///////////////////////////////
	m_pPlayer->UpdateControl();

	m_slowCount = (m_slowCount += 1) % m_pPlayer->GetSlowWorld();

	if (m_slowCount == 0)
	{
		// �v���C���[�̍X�V
		m_pPlayer->Update();
		for (auto& enemyRush : m_pEnemyRush)
		{
			enemyRush->Update();

			//// �G����ʍ��W����o����폜
			if (enemyRush->GetPos().x < 0)
			{
				enemyRush->End();
			}
		}

		// �G�𐶐�(�܂����S�ȃG�l�~�[�폜�����Ȃ�)
		m_enemyCount++;
		if (m_enemyCount > 60 * m_tempRand)
		{
			m_enemyCount = 0;
			Vec3 pos = { m_pPlayer->GetPos().x,0.0f,0.0f};
			pos.x += 3000;
			m_pEnemyRush.push_back(std::make_shared<EnemyRush>(pos));
		}

		// ���̃G�l�~�[�������_���b�ɏo��
		if (m_enemyCount == 0)
		{
			m_tempRand = GetRand(2);
		}
	}

	// �v���C���[�ƃG�l�~�[�̓����蔻��
	playerCheckHit();
	// �v���C���[�ƒn�ʂ̓����蔻��
	fieldCheckHit();
	// ���G���Ԃ̒���
	if (!m_pPlayer->GetInvincible()) m_isInvincible = false;


	
	// �t�F�C�h����
	UpdateFade();

	if (m_pPlayer->GetPos().x > 30000)
	{
		return(new SceneTitle);
	}
	if (m_pPlayer->GetPos().y < -1000.0f)
	{
		return(new SceneTitle);
	}
	return this;
}
// �`�� //
void SceneDebug::Draw()
{

	for (auto& enemyRush : m_pEnemyRush)
	{
		enemyRush->Draw();
	}

	m_pPlayer->Draw();

	m_pField->Draw();

	// �t�F�C�h����
	SceneBase::DrawFade();
}

void SceneDebug::playerCheckHit()
{
	// �����蔻��̏��
	if (!m_isInvincible)
	{
		// �G�Ƃ̔���
		for (auto& enemy : m_pEnemyRush)
		{
			// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
			MV1_COLL_RESULT_POLY_DIM result;		//������f�[�^

			result = MV1CollCheck_Capsule(
				enemy->GetModelHandle(),
				enemy->GetColFrameIndex(),
				m_pPlayer->GetPos(),
				m_pPlayer->GetSize(),
				m_pPlayer->GetRadius());
			if (result.HitNum > 0)	//1���ȏ�̃|���S���Ɠ������Ă����烂�f���ɂ����Ă���ݒ�
			{
				// �_���[�W�ʂ�n��
				m_pPlayer->OnDamage(30);
				// �U���J�n
				StartJoypadVibration(DX_INPUT_PAD1, 1000, 60, -1);
				// �_���[�W���������
				m_isInvincible = true;
			}

			// �����蔻����̌�n��
			MV1CollResultPolyDimTerminate(result);
		}
	}
}

void SceneDebug::fieldCheckHit()
{
	// �n�ʔ���̏���n��
	m_pPlayer->FieldCheckHit(false);
	// �n�ʂƂ̔���
	// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�

	for (int x = 0; x < m_pField->GetModelNumX(); x++)
	{
		MV1_COLL_RESULT_POLY_DIM result;		//������f�[�^
		result = MV1CollCheck_Capsule(
			m_pField->GetModelHandle(x),
			m_pField->GetColFrameIndex(),
			m_pPlayer->GetPos(),
			m_pPlayer->GetSize(),
			m_pPlayer->GetRadius());
		if (result.HitNum > 0)	//1���ȏ�̃|���S���Ɠ������Ă����烂�f���ɂ����Ă���ݒ�
		{
			// �n�ʔ���̏���n��
			m_pPlayer->FieldCheckHit(true);
		}
		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}
}
