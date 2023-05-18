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

	// �l�p���m�̓����蔻��
	// int left�Aint top�Aint right�Aint bottom�A
	// int left1�Aint top1�Aint right1�Aint bottom1�A
	// bool �_���[�W���󂯂鑤(�v���C���[ : true�G: false�j�Aint �^����_���[�W
	bool damege(int left, int top, int right, int bottom,
		int left1, int top1, int right1, int bottom1,
		bool playerOrEnemy = true,int damage = 0);
private:

	int m_slowCount;

	int m_enemyCount;

	int m_tempRand;

	bool m_isInvincible;

	bool m_isEnemyDamageHit;

	Player* m_pPlayer;
//	std::vector<std::shared_ptr<Enemy>>m_pEnemy;
	std::vector<std::shared_ptr<EnemyRush>>m_pEnemyRush;
	Field* m_pField;
};