#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>

class Player;
class Enemy;
class EnemyRush;
class Field;
class Map;

class ItemManegaer;


class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug();

	virtual void Init() override;
	virtual void End() override;

	virtual SceneBase* Update() override;
	virtual void Draw() override;

	void PlayerCheckHit();
	void FieldCheckHit();

private:
	
	int m_slowCount;

	int m_enemyCount;

	int m_tempRand;

	bool m_isInvincible;

	// プレイヤーのポインタ
	Player* m_pPlayer;
	// アイテムのポインタ
	std::shared_ptr<ItemManegaer>m_pItem;
	// エネミーのポインタの配列
	std::vector<std::shared_ptr<EnemyRush>>m_pEnemyRush;
	// マップのポインタ
	Field* m_pField;
	Map* m_pMap;


	// test //

	int handle = -1;

	std::vector<int> m_CoinPosX;
	std::vector<int> m_CoinPosY;

};