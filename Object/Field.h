#pragma once
#include <vector>
#include <array>
#include <memory>

namespace 
{
	// �n�ʂɕ~���l�߂�u���b�N�̐�
	constexpr int kBlockNumX = 151;
	constexpr int kBlockNumY = 6;
}

class Model;
class Field
{
public:
	Field();
	virtual ~Field();

	void Init();
	void End();
	void Update();
	void Draw();

	// ���f���̐�
	int GetModelNumX();
	int GetModelNumY();
	// �w�肵���ԍ��̃��f���̃n���h�����擾����
	int GetModelHandle(int y, int x);
	// ���f���̈ʒu��Ԃ�
	float SetPosY(int y, int x);
	// ���f���̈ʒu��Ԃ�
	float SetPosX(int y, int x);
	// ���f���̃t���[���C���f�b�N�X��Ԃ�
	int GetColFrameIndex(int y, int x)const;

	int GetCoinPosX(int y, int x) { return m_CoinPosX[y][x]; }
	int GetCoinPosY(int y, int x) { return m_CoinPosY[y][x]; }
	int GetCoinNum() { return coinNum; }

private:
	std::shared_ptr<Model> m_pModel[kBlockNumY][kBlockNumX];

	int m_CoinPosX[kBlockNumY][kBlockNumX];
	int m_CoinPosY[kBlockNumY][kBlockNumX];

	int coinNum = 0;
};

