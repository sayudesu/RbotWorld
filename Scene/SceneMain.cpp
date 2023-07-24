#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameOver.h"
#include "SceneGameClear.h"
#include <DxLib.h>
#include "game.h"
#include "Object/Player.h"

#include "Object/Field.h"
#include "Object/Map/Map.h"
#include "UI.h"

#include "Object/Coin.h"
#include "Object/ItemManegaer.h"
#include "ItemName.h"

#include "PauseScreen.h"

#include "FieldBase.h"

#include "Sound.h"
#include "Util/Pad.h"

#include <cassert>

namespace
{
	// �����ʒu
	Vec3 kPos = { static_cast<float>(Game::kScreenWidth),0.0f ,0.0f };
}

SceneMain::SceneMain(std::shared_ptr<FieldBase>field):
	m_slowCount(0),
	m_pPlayer(nullptr),
	m_pField(nullptr),
	m_pMap(nullptr),
	m_pUi(nullptr),
	m_pFieldOne(field),
	m_updateFunc(&SceneMain::UpdateMain),
	m_isGameClear(false),
	m_isGameOver(false)
{
	// �C���X�^���X�쐬
	m_pItem = std::make_shared<ItemManegaer>();
	m_pPlayer = new Player;
	m_pField = new Field;
	m_pMap = new Map;
	m_pUi = new UI;
	m_pPause = new PauseScreen;

}

SceneMain::~SceneMain()
{

	m_pItem.reset();

	delete m_pPlayer;
	delete m_pField;
	delete m_pMap;
}

void SceneMain::Init()
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

	m_pPause->Init();

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

	// BGM�Đ�
	Sound::startBgm(Sound::SoundId_Main, 50);
}

void SceneMain::End()
{
	m_pPlayer->End();

	m_pField->End();

	Sound::stopBgm(Sound::SoundId_Main);
}

// �X�V //
SceneBase* SceneMain::Update()
{
	
	// �Q�[�����N���A������
	// �Q�[���I�[�o�[�ɂȂ�����
	if (m_isGameClear)
	{
		// �X�R�A��n��
		// �Q�[���N���A��ʂɈڍs
		return new SceneGameClear{ m_pUi->GetScore(),m_coinCount,m_diamondCount };
	}
	else if (m_isGameOver) 
	{
		// �Q�[���I�[�o�[��ʂɈڍs
		return new SceneGameOver;
	}

	if (m_pPause->isSetMainScene())
	{
		if (SceneBase::UpdateSliderClose())
		{
			std::shared_ptr<FieldBase>m_pField;
			m_pField = std::make_shared<FieldBase>();
			return new SceneMain(m_pField);
		}
	}

	if (m_pPause->isSetTitleScene())
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneTitle();
		}
	}


	// ���݂̎w��֐��Ɉړ�����
	(this->*m_updateFunc)();
	return this;
}
// �`�� //
void SceneMain::Draw()
{
	// �}�b�v�`�b�v�̕`��
	m_pMap->Draw();
	// �v���C���[�̕`��
	m_pPlayer->Draw();
	// �n�ʂ̕`��
	m_pFieldOne->Draw();
	m_pField->Draw();
	// �A�C�e���̕`��
	m_pItem->Draw();
	// UI�̕`��
	m_pUi->Draw();
	// �|�[�Y��ʂ̕`��
	m_pPause->Draw();
	// �X���C�h�̕`��
	SceneBase::DrawSliderDoor();
}

// �n�ʂƂ̔���
void SceneMain::FieldCheckHit()
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

// �A�C�e���̔���
void SceneMain::ItemCheckHit()
{
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
			if (!m_pItem->isErase(Item::coin, i))
			{
				m_pItem->SetEraseNo(Item::coin, i);
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
			if (!m_pItem->isErase(Item::diamond, i))
			{
				m_pItem->SetEraseNo(Item::diamond, i);
				m_diamondCount++;
			}
		}
	}
}
// �Q�\�����C����ʂ̏���
void SceneMain::UpdateMain()
{
	// �t�B�[���h�̔���(�n��)
	m_pFieldOne->Update();
	m_pField->Update();

	// �v���C���[�̑���
	m_pPlayer->UpdateControl();
	// �A�C�e���̍X�V����
	m_pItem->Update();

	// �Q�[���X���[�Đ��p
	m_slowCount = (m_slowCount += 1) % m_pPlayer->GetSlowWorld();
	if (m_slowCount == 0)
	{
		// �v���C���[�̍X�V
		m_pPlayer->Update();
	}

	// �v���C���[�ƒn�ʂ̓����蔻��
	FieldCheckHit();

	// �S�[���ɓ��B����ƃQ�[���N���A��ʂɈړ�
	if (m_pPlayer->GetPos().x > 30000)
	{
		m_pPlayer->SetMoveing(false);
		if (SceneBase::UpdateSliderClose())
		{
			m_isGameClear = true;
		}
	}
	//	return new SceneGameClear{ m_pUi->GetScore(),m_coinCount,m_diamondCount };
		// �������邩�v���C���[�����񂾏ꍇ�̓Q�[���I�[�o�[��ʂɈړ�
	if (m_pPlayer->GetPos().y < -1000.0f ||
		m_pPlayer->GetIsDead())
	{
		m_pPlayer->SetMoveing(false);
		if (SceneBase::UpdateSliderClose())
		{
			m_isGameOver = true;
		}
	}

	// �A�C�e���̓����蔻�菈��
	ItemCheckHit();
	// UI�X�V����
	m_pUi->Update();
	// �擾�����A�C�e���̐���n���B
	m_pUi->SetItemNum(Item::coin, m_coinCount);
	m_pUi->SetItemNum(Item::diamond, m_diamondCount);

	// �X���C�h���J����
	SceneBase::UpdateSlider(m_isSliderOpen);
	
	// ���j���[��ʂ�\��
	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_updateFunc = &SceneMain::UpdateMenu;
	}
}

// �|�[�Y��ʏ���
void SceneMain::UpdateMenu()
{
	// �|�[�Y��ʍX�V
	m_pPause->Update();

	// �|�[�Y��ʏI��
	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_pPause->GetPauseEnd(true);
	}
	// �Q�[���v���C�p�֐��Ɉڍs����
	if (m_pPause->isSetEnd())
	{
		m_updateFunc = &SceneMain::UpdateMain;
		// �f�t�H���g�̏�Ԃɖ߂�
		m_pPause->Reset();
	}
}
