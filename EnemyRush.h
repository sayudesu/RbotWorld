#pragma once
#include <DxLib.h>
#include <memory>
#include "Vec2.h"
#include "EnemyBase.h"

class Animation;
class EnemyRush : public EnemyBase
{
public:
	EnemyRush(VECTOR pos);
	virtual ~EnemyRush();

	void Init();
	void End();
	void Update();
	void Draw();
private:
	void Dead();
	void DrawUI();
private:

	std::shared_ptr<Animation> m_pAnimation;

	void(EnemyRush::* m_upddateFunc)();
};

