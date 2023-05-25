#pragma once
#include <DxLib.h>
#include <memory>

#include "EnemyBase.h"

class Model;
class EnemyRush : public EnemyBase
{
public:
	EnemyRush(Vec3 pos);
	virtual ~EnemyRush();

	void Init();
	void End();
	void Update();
	void Draw();

	// 当たり判定のフレームインデックス取得
	int GetColFrameIndex()const;
	int GetModelHandle();
private:

	std::shared_ptr<Model> m_pAnimation;

	void(EnemyRush::* m_upddateFunc)();
};

