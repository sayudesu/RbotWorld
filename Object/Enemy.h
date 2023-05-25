#pragma once
#include <DxLib.h>
#include <memory>
#include "EnemyBase.h"

class Animation;
class Enemy : public EnemyBase
{
public:
	Enemy();
	virtual ~Enemy();

	void Init();
	void End();
	void Update();
	void Draw();
private:

	std::shared_ptr<Animation> m_pAnimation;

	void(Enemy::* m_upddateFunc)();
};

