#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>
#include <DxLib.h>

class Player;
class Field;
class Map;
class UI;
class ItemManegaer;

class FieldBase;

class SceneMain : public SceneBase
{
public:
	SceneMain(std::shared_ptr<FieldBase>field);
	virtual ~SceneMain();

	virtual void Init() override;
	virtual void End() override;

	virtual SceneBase* Update() override;
	virtual void Draw() override;

	void FieldCheckHit();
private:
	void Door();
private:
	
	int m_slowCount;

	int m_enemyCount;

	int m_tempRand;

	bool m_isInvincible;

	// プレイヤーのポインタ
	Player* m_pPlayer;
	// アイテムのポインタ
	std::shared_ptr<ItemManegaer>m_pItem;
	// マップのポインタ
	Field* m_pField;
	Map* m_pMap;
	UI* m_pUi;
	std::shared_ptr<FieldBase> m_pFieldOne;
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

	int m_hDoor;
};