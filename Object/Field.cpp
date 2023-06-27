#include "Field.h"
#include "Model.h"
#include <DxLib.h>

namespace
{
	// �t�@�C����
	const char* const kFileStageName = "Data/Model/Stage/Field.mv1";

	// �u���b�N�̈�ӂ̒���
	constexpr float kBlockSideLength = 100.0f;

	// �񎟌��z��}�b�v�f�[�^
	constexpr int StageData[kBlockNumY][kBlockNumX] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
}

Field::Field()
{

	for (int y = 0; y < kBlockNumY; y++)
	{
		for (int x = 0; x < kBlockNumX; x++)
		{
			// ���f���N���X�̃C���X�^���X�쐬
			m_pModel[y][x] = std::make_shared<Model>(kFileStageName);
			// �����蔻��p����
			m_pModel[y][x]->SetUseCollision(true, true);

			m_CoinPosX[y][x] = 0;

		}
	}

	for (int y = 0; y < kBlockNumY; y++)
	{
		for (int x= 0; x < kBlockNumX; x++)
		{
			if (StageData[y][x] == 1)
			{
				// ���W�v�Z
				float posY = 200.0f * ((kBlockNumY - 1) - y) - 300;
				float posX = 200.0f * x ;

				// ���f���Ɉʒu��n��
				m_pModel[y][x]->SetPos(VGet(
					posX,
					posY,
					0.0f));
			}

			if (StageData[y][x] == 2)
			{
				coinNum++;
				int posX = 200.0f * x;
				int posY = 200.0f * ((kBlockNumY - 1) - y) - 300;
				//m_CoinPosX[y][x] = posX;
				//m_CoinPosY[y][x] = posY;

				m_coinX.push_back(posX);
				m_coinY.push_back(posY);


			}
		}
	}
	int a;
}

Field::~Field()
{

}

void Field::Init()
{
}

void Field::End()
{
}

void Field::Update()
{
	for (int y = 0; y < kBlockNumY; y++)
	{
		for (int x = 0; x < kBlockNumX; x++)
		{
			m_pModel[y][x]->Update();
		}
	}
}

void Field::Draw()
{
	for (int y = 0; y < kBlockNumY; y++)
	{
		for (int x = 0; x < kBlockNumX; x++)
		{
			m_pModel[y][x]->Draw();
		}
	}
#if false		
	// �E�Ɉړ��p���C��
	const float xMax = 30000.0f;
	const float yMax = 1200.0f;
	const float x = 300.0f;

	const float chipSize = 150.0f;

	// -500~500�͈̔͂ɃO���b�h�̕\��
	for (float x = -500.0f; x <= xMax; x += chipSize)
	{
		const VECTOR start = VGet(x, 0.0f, -500.0f);
		const VECTOR end = VGet(x, 0.0f, 500.0f);
		DrawLine3D(start, end, x * 300.0f);
	}
	for (float z = -500.0f; z <= 500.0f; z += chipSize)
	{
		const VECTOR start = VGet(-500.0f, 0.0f, z);
		const VECTOR end = VGet(500.0f, 0.0f, z);
		DrawLine3D(start, end, 0xffff00);
	}

	// Y���W��DrwaLine��`��
	for (float y = 0.0f; y <= yMax; y += chipSize)
	{
		const VECTOR start = VGet(-1050.0f, y, x);
		const VECTOR end = VGet(xMax, y, x);
		DrawLine3D(start, end, 0xffff00);
	}
	for (float tY = -1000.0f; tY <= xMax; tY += chipSize)
	{
		const VECTOR start = VGet(tY, 0.0f, x);
		const VECTOR end = VGet(tY, 1500.0f, x);
		DrawLine3D(start, end, 0xffff00);
	}
#endif
}

// ���f��X�̐�
int Field::GetModelNumX()
{
	return kBlockNumX;
}
// ���f��Y�̐�
int Field::GetModelNumY()
{
	return kBlockNumY;
}

// �w�肵���ԍ��̃��f���̃n���h�����擾����
int Field::GetModelHandle(int y ,int x)
{
	return m_pModel[y][x]->GetModelHandle();
}

// ���f����Y�ʒu��Ԃ�
float Field::SetPosY(int y, int x)
{
	return m_pModel[y][x]->GetModelPos().y;
}

// ���f����X�ʒu��Ԃ�
float Field::SetPosX(int y, int x)
{
	return m_pModel[y][x]->GetModelPos().x;
}

// ���f���̃t���[���C���f�b�N�X��Ԃ�
int Field::GetColFrameIndex(int y,int x)const
{
	return m_pModel[y][x]->GetColFrameIndex();
}

