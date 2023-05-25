#pragma once
#include <vector>
#include <array>
#include <memory>

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
	int GetModelNumX();
	int GetModelNumY();
	// 指定した番号のモデルのハンドルを取得する
	int GetModelHandle(int y, int x);
	// モデルの位置を返す
	float SetPosY(int y, int x);
	// モデルのフレームインデックスを返す
	int GetColFrameIndex(int y, int x)const;

private:
	std::shared_ptr<Animation> m_pModel[5][350];
//	std::vector<std::shared_ptr<Animation>> m_pModel;
//	std::vector<std::vector<std::shared_ptr<Animation>>> m_pModel;
};

