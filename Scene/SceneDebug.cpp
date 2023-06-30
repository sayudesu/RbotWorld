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
#include "UI.h"

#include "Coin.h"
#include "ItemManegaer.h"
#include "ItemName.h"

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
	m_pMap(nullptr),
	m_pUi(nullptr)
{
	// �C���X�^���X�쐬
	m_pItem = std::make_shared<ItemManegaer>();

	m_pPlayer = new Player;
	m_pField = new Field;
	m_pMap = new Map;
	m_pUi = new UI;
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
	// �R�C���̐�
	m_coinNum = coinNum + 1;

	// �R�C���̐���
	// �R�C���̈ʒu����
	for (int i = 0; i < m_coinNum; i++)
	{
		m_CoinPosX.push_back(m_pField->GetCoinX()[i]);
		m_CoinPosY.push_back(m_pField->GetCoinY()[i]);
	}

	// �R�C�����쐬
	m_pItem->CreateCoin(m_CoinPosX, m_CoinPosY, m_coinNum);

	// �_�C���̐�
	const int diamondNum = static_cast<int>(m_pField->GetDiamondNum());
	// �_�C���̐�
	m_diamondNum = diamondNum + 1;

	// �_�C���̐���
	// �_�C���̈ʒu����
	for (int i = 0; i < m_diamondNum; i++)
	{
		m_diamondPosX.push_back(m_pField->GetDiamondX()[i]);
		m_diamondPosY.push_back(m_pField->GetDiamondY()[i]);
	}

	// �R�C�����쐬
	m_pItem->CreateDiamond(m_diamondPosX, m_diamondPosY, m_diamondNum);


	m_pUi->SetItemMaxNum(Item::coin, m_coinNum);
	m_pUi->SetItemMaxNum(Item::diamond, m_diamondNum);

	m_isInvincible = true;
	// BGM�Đ�
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

	// ���G���Ԃ̒���
	if (!m_pPlayer->GetInvincible()) m_isInvincible = false;

	// �S�[���ɓ��B����ƃQ�[���N���A��ʂɈړ�
	if (m_pPlayer->GetPos().x > 30000)
	{
		StartFadeOut();
		// �X�R�A��n��
		return new SceneGameClear{ m_pUi->GetScore() };
	}

	// �������邩�v���C���[�����񂾏ꍇ�̓Q�[���I�[�o�[��ʂɈړ�
	if (m_pPlayer->GetPos().y < -1000.0f ||
		m_pPlayer->GetIsDead())
	{
		if (!IsFading())
		{
			return new SceneGameOver;
		}
	}


	// �֐������܂� //

	// �v���C���[�̔���p���W
	// �R�C���̈ʒu
	// �v���C���[�̈ʒu����R�C���̈ʒu������
	// �G�ꂽ�R�C���̐����J�E���g����
	VECTOR pos = { m_pPlayer->GetPos().x,m_pPlayer->GetPos().y + 250.0f ,m_pPlayer->GetPos().z };
	// �R�C���ƃv���C���[�̓����蔻��
	for (int i = 0; i < m_coinNum; i++)
	{
		const VECTOR coinPos = VGet(m_CoinPosX[i], m_CoinPosY[i] + 150.0f, m_pPlayer->GetPos().z);

		const VECTOR vec = VSub(pos, coinPos);

		const float del = VSize(vec);

		// �x�N�g���̃T�C�Y���擾����
		// �R�C���ɓ������Ă���ꍇ�͔�����s��Ȃ�
		// �G�ꂽ�R�C���̔ԍ���n��
		if (del < 128 * 2 + 62)
		{
			if (!m_pItem->isErase(Item::coin,i))
			{
				m_pItem->SetEraseNo(Item::coin,i);
				m_coinCount++;
			}
		}
	}

	// �R�C���ƃv���C���[�̓����蔻��
	// �v���C���[�̈ʒu����R�C���̈ʒu������
	// �x�N�g���̃T�C�Y���擾����
	// �R�C���̈ʒu
	for (int i = 0; i < m_diamondNum; i++)
	{
		const VECTOR diamondPos = VGet(m_diamondPosX[i], m_diamondPosY[i] + 250.0f, m_pPlayer->GetPos().z);

		const VECTOR vec = VSub(pos, diamondPos);

		const float del = VSize(vec);

		// �R�C���ɓ������Ă���ꍇ�͔�����s��Ȃ�
		// �G�ꂽ�R�C���̔ԍ���n��
		// �G�ꂽ�R�C���̐����J�E���g����
		if (del < 128 * 2 + 62)
		{
			if (!m_pItem->isErase(Item::diamond,i))
			{
				m_pItem->SetEraseNo(Item::diamond,i);
				m_diamondCount++;
			}
		}
	}
	m_pUi->Update();
	// �擾�����A�C�e���̐���n���B
	m_pUi->SetItemNum(Item::coin, m_coinCount);
	m_pUi->SetItemNum(Item::diamond, m_diamondCount);

	return this;
}
// �`�� //
void SceneDebug::Draw()
{
	m_pMap->Draw();
	m_pPlayer->Draw();
	m_pField->Draw();
	m_pItem->Draw();
	m_pUi->Draw();
#if false			
	for (int i = 0; i < m_coinNum; i++)
	{
		DrawSphere3D(VGet(m_CoinPosX[i], m_CoinPosY[i] + 150.0f, -0.5f),
			62, 32, 0xffff00, 0xffff00, true);
	}
	for (int i = 0; i < m_diamondNum; i++)
	{
		DrawSphere3D(VGet(m_diamondPosX[i], m_diamondPosY[i] + 250.0f, -0.5f),
			62, 32, 0x0000ff, 0x0000ff, true);
	}

	DrawSphere3D(VGet(m_pPlayer->GetPos().x, m_pPlayer->GetPos().y + 250.0f, m_pPlayer->GetPos().z),
		128 * 2, 32, 0xffffff, 0xffffff, true);
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
