#pragma once
#include <vector>
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
	int GetModelNum();
	// 指定した番号のモデルのハンドルを取得する
	int GetModelHandle()const;

	int GetColFrameIndex()const;



private:
	std::vector<std::shared_ptr<Animation>> m_pModel;
};

