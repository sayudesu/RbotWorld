#pragma once
#include <vector>
#include <memory>

namespace
{
	// ファイル名
	const char* const kFileStageName = "Data/Model/Stage/Field.mv1";

	// 地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 50;
	constexpr int kBlockNumZ = 5;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	// ブロックの一辺の長さ
	constexpr float kBlockSideLength = 100.0f;

	// 地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

class Animation;
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
	int GetModelNum() { return kBlockNum; }
	// 指定した番号のモデルのハンドルを取得する
	int GetModelHandle()const;

	int GetColFrameIndex()const;



private:
	std::vector<std::shared_ptr<Animation>> m_pModel;
};

