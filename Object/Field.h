#pragma once
#include <vector>
#include <array>
#include <memory>

namespace 
{
	// 地面に敷き詰めるブロックの数
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

	// モデルの数
	int GetModelNumX();
	int GetModelNumY();
	// 指定した番号のモデルのハンドルを取得する
	int GetModelHandle(int y, int x);
	// モデルの位置を返す
	float SetPosY(int y, int x);
	// モデルのフレームインデックスを返す
	int GetColFrameIndex(int y, int x)const;

private:
	std::shared_ptr<Model> m_pModel[kBlockNumY][kBlockNumX];
};

