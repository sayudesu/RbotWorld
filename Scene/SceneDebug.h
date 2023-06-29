#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>
#include <DxLib.h>

class Player;
class Enemy;
class EnemyRush;
class Field;
class Map;
class UI;
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
	bool CoinCheckHit(const VECTOR& capsulePos, float capsuleRadius, float capsuleHeight, const VECTOR& spherePos, float sphereRadius);
	float VDist(const VECTOR& v1, const VECTOR& v2);
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
	UI* m_pUi;

	// test //

//	int handle = -1;
	int m_coinNum;
	int m_diamondNum;
	std::vector<int> m_CoinPosX;
	std::vector<int> m_CoinPosY;

	std::vector<int> m_diamondPosX;
	std::vector<int> m_diamondPosY;

	int m_coinCount = 0;
	int m_diamondCount = 0;
};