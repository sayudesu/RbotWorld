#pragma once
#include <DxLib.h>
#include <memory>
#include "EnemyBase.h"

class Model;
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

	std::shared_ptr<Model> m_pAnimation;

	void(Enemy::* m_upddateFunc)();
};

