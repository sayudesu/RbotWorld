#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>

class Player;
class Enemy;
class EnemyRush;
class Field;
class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug() {}

	virtual void Init() override;
	virtual void End() override;

	virtual SceneBase* Update() override;
	virtual void Draw() override;
private:

	int m_enemyCount;

	bool m_isCheckHit;
	bool m_isCheckHitAttack;

	Player* m_pPlayer;
	std::vector<std::shared_ptr<Enemy>>m_pEnemy;
	std::vector<std::shared_ptr<EnemyRush>>m_pEnemyRush;
	Field* m_pField;
};