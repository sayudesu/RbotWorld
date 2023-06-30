#pragma once
#include <vector>
#include <array>
#include <memory>

namespace 
{
	// 地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 151;
	constexpr int kBlockNumY = 7;
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

	// モデルの数
	int GetModelNumX();
	int GetModelNumY();

	// 指定した番号のモデルのハンドルを取得する
	int GetModelHandle(int y, int x);

	// モデルの位置を返す
	float SetPosY(int y, int x);

	// モデルの位置を返す
	float SetPosX(int y, int x);

	// モデルのフレームインデックスを返す
	int GetColFrameIndex(int y, int x)const;

	int GetCoinPosX(int y, int x) { return m_CoinPosX[y][x]; }
	int GetCoinPosY(int y, int x) { return m_CoinPosY[y][x]; }
	std::vector<int> GetCoinX() { return m_coinX; }
	std::vector<int> GetCoinY() { return m_coinY; }
	std::vector<int> GetDiamondX() { return m_diomondX; }
	std::vector<int> GetDiamondY() { return m_diomondY; }

	// コインの数
	int GetCoinNum()const { return coinNum; }
	int GetDiamondNum()const { return diomondNum; }

private:
	std::shared_ptr<Model> m_pModel[kBlockNumY][kBlockNumX];

	int m_CoinPosX[kBlockNumY][kBlockNumX];
	int m_CoinPosY[kBlockNumY][kBlockNumX];

	std::vector<int> m_coinX;
	std::vector<int> m_coinY;
	std::vector<int> m_diomondX;
	std::vector<int> m_diomondY;

	int coinNum = -1;
	int diomondNum = -1;
};

