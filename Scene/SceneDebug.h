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
	virtual ~SceneDebug();

	virtual void Init() override;
	virtual void End() override;

	virtual SceneBase* Update() override;
	virtual void Draw() override;

	void playerCheckHit();
	void fieldCheckHit();

private:

	int m_slowCount;

	int m_enemyCount;

	int m_tempRand;

	bool m_isInvincible;

	// �v���C���[�̃|�C���^
	Player* m_pPlayer;
	// �G�l�~�[�̃|�C���^�̔z��
	std::vector<std::shared_ptr<EnemyRush>>m_pEnemyRush;
	// �}�b�v�̃|�C���^
	Field* m_pField;

};