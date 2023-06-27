#include "SceneDebug.h"
#include "SceneTitle.h"
#include "SceneGameOver.h"
#include "SceneGameClear.h"
#include <DxLib.h>
#include "game.h"
#include "Object/Player.h"
#include "Object/Enemy.h"
#include "Object/EnemyRush.h"
#include "Object/Field.h"
#include "Object/Map/Map.h"

#include "Coin.h"
#include "ItemManegaer.h"

#include "Sound.h"

#include <cassert>

namespace
{
	// �����ʒu
	Vec3 kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneDebug::SceneDebug():
	m_slowCount(0),
	m_enemyCount(0),
	m_tempRand(0),
	m_isInvincible(false),
	m_pPlayer(nullptr),
	m_pField(nullptr),
	m_pMap(nullptr)
{
	// �C���X�^���X�쐬
	m_pItem = std::make_shared<ItemManegaer>();

	m_pPlayer = new Player;
	m_pField = new Field;
	m_pMap = new Map;
}

SceneDebug::~SceneDebug()
{

	m_pItem.reset();

	delete m_pPlayer;
	delete m_pField;
	delete m_pMap;
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

	m_pMap->Load();

	// �R�C���̐�
	const int coinNum = static_cast<int>(m_pField->GetCoinNum());
	// �R�C���̐����̔z����
	int* posX = new int[coinNum];
	int* posY = new int[coinNum];

	// �R�C���̐�
	m_coinNum = coinNum;

	// �R�C���̐���
	// �R�C���̈ʒu����
	for (int i = 0; i < coinNum; i++)
	{
		m_CoinPosX.push_back(m_pField->GetCoinX()[i]);
		m_CoinPosY.push_back(m_pField->GetCoinY()[i]);
	}

	// �R�C�����쐬
	m_pItem->CreateCoin(m_CoinPosX, m_CoinPosY, coinNum);

	m_isInvincible = true;

	Sound::startBgm(Sound::SoundId_Main, 50);
}

void SceneDebug::End()
{
	m_pPlayer->End();

	m_pField->End();

	Sound::stopBgm(Sound::SoundId_Main);
}

// �X�V //
SceneBase* SceneDebug::Update()
{
	// �t�F�C�h����
	UpdateFade();

	m_pField->Update();

	// �v���C���[�̑���
	m_pPlayer->UpdateControl();

	m_pItem->Update();

	// �Q�[���X���[�Đ��p
	m_slowCount = (m_slowCount += 1) % m_pPlayer->GetSlowWorld();

	if (m_slowCount == 0)
	{
		// �v���C���[�̍X�V
		m_pPlayer->Update();
	}

	// �v���C���[�ƃG�l�~�[�̓����蔻��
	PlayerCheckHit();
	// �v���C���[�ƒn�ʂ̓����蔻��
	FieldCheckHit();

//	CoinCheckHit();

	// ���G���Ԃ̒���
	if (!m_pPlayer->GetInvincible()) m_isInvincible = false;

	// �S�[���ɓ��B����ƃQ�[���N���A��ʂɈړ�
	if (m_pPlayer->GetPos().x > 30000)
	{
		StartFadeOut();
		//SceneBase::UpdateFade();

		return(new SceneGameClear);	
	}

	// �������邩�v���C���[�����񂾏ꍇ�̓Q�[���I�[�o�[��ʂɈړ�
	if (m_pPlayer->GetPos().y < -1000.0f ||
		m_pPlayer->GetIsDead())
	{
		if (!IsFading())
		{
			return(new SceneGameOver);
		}
	}
	return this;
}
// �`�� //
void SceneDebug::Draw()
{
	m_pMap->Draw();
	m_pPlayer->Draw();
	m_pField->Draw();
	m_pItem->Draw();

	for (int i = 0; i < m_coinNum; i++)
	{
		DrawBox(m_CoinPosX[i], m_CoinPosY[i],
			m_CoinPosX[i] + 1000, m_CoinPosY[i] + 1000,
			0xffffff, true);
		VECTOR pos = VGet(m_CoinPosX[i], m_CoinPosY[i], -0.5f);
		DrawSphere3D(pos, 32, 32, 0xffffff, 0xffffff, true);
		printfDx("%f\n", pos.x);
	}
#if false
	for (int y = 0; y < m_pField->GetModelNumY(); y++)
	{
		for (int x = 0; x < m_pField->GetModelNumX(); x++)
		{
			if (m_pField->GetCoinPosX(y, x) != 0)
			{
				int posX = m_pField->GetCoinPosX(y, x);
				int posY = m_pField->GetCoinPosY(y, x);
				DrawSphere3D(VGet(posX, posY, 5.0f), 80.0f, 32.0f, 0xffffff, 0xffffff, true);
			}
		}
	}
#endif
	// �t�F�C�h����
	SceneBase::DrawFade();
}

void SceneDebug::PlayerCheckHit()
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
				m_pPlayer->OnDamage(enemy->GetAttackDamage());
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

void SceneDebug::FieldCheckHit()
{
	// �n�ʔ���̏���n��
	m_pPlayer->FieldCheckHit(false);
	// �n�ʂƂ̔���
	// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�

	for (int y = 0; y < m_pField->GetModelNumY(); y++)
	{
		for (int x = 0; x < m_pField->GetModelNumX(); x++)
		{
			MV1_COLL_RESULT_POLY_DIM result;		//������f�[�^
			result = MV1CollCheck_Capsule(
				m_pField->GetModelHandle(y,x),
				m_pField->GetColFrameIndex(y,x),
				m_pPlayer->GetPos(),
				m_pPlayer->GetSize(),
				m_pPlayer->GetRadius());
			if (result.HitNum > 0)	//1���ȏ�̃|���S���Ɠ������Ă����烂�f���ɂ����Ă���ݒ�
			{
				// �n�ʔ���̏���n��
				m_pPlayer->FieldCheckHit(true);
				m_pPlayer->FieldPosY(m_pField->SetPosY(y, x));
			}
			// �����蔻����̌�n��
			MV1CollResultPolyDimTerminate(result);
		}
	}

}

bool SceneDebug::CoinCheckHit(const VECTOR& capsulePos, float capsuleRadius, float capsuleHeight, const VECTOR& spherePos, float sphereRadius)
{

	// �J�v�Z���̏㉺�[��Y���W���v�Z
	float capsuleTopY = capsulePos.y - capsuleHeight / 2.0f;
	float capsuleBottomY = capsulePos.y + capsuleHeight / 2.0f;

	// �J�v�Z���̒��S���Ƌ��̂̒��S�Ƃ̋������v�Z
	float distance = VDist(capsulePos, spherePos);

	// �J�v�Z���Ƌ��̂̔��a�̘a���v�Z
	float sumRadius = capsuleRadius + sphereRadius;

	// �J�v�Z���Ƌ��̂��ڐG���Ă��邩����
	if (distance <= sumRadius)
	{
		// �J�v�Z���Ƌ��̂��ڐG���Ă���ꍇ�AY���W�͈͓̔��ɂ��邩����
		if (spherePos.y >= capsuleTopY && spherePos.y <= capsuleBottomY)
		{
			return true;  // �ڐG���Ă���
		}

		// �J�v�Z���̏㉺�̋��̂Ƃ̋������v�Z
		float topDistance = VDist(capsulePos, VGet(capsulePos.x, capsuleTopY, capsulePos.z));
		float bottomDistance = VDist(capsulePos, VGet(capsulePos.x, capsuleBottomY, capsulePos.z));

		// �J�v�Z���̏㉺�̋��̂Ƃ̋��������̂̔��a�ȉ��ł���ΐڐG���Ă���
		if (topDistance <= sphereRadius || bottomDistance <= sphereRadius)
		{
			return true;  // �ڐG���Ă���
		}
	}

	return false;  // �ڐG���Ă��Ȃ�
}

float SceneDebug::VDist(const VECTOR& v1, const VECTOR& v2)
{
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	float dz = v1.z - v2.z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}
