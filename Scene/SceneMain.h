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
class PauseScreen;

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

private:
	// 判定を確認
	void FieldCheckHit();
	void ItemCheckHit();
	// ゲーム全体の更新処理
	void UpdateMain();
	void UpdateMenu();
private:
	int m_slowCount;
	// プレイヤークラスのポインタ
	Player* m_pPlayer;
	// アイテムクラスのポインタ
	std::shared_ptr<ItemManegaer>m_pItem;
	// マップクラスのポインタ
	Field* m_pField;
	// UIクラスのポインタ
	UI* m_pUi;
	// マップ情報クラスのポインタ
	Map* m_pMap;
	std::shared_ptr<FieldBase> m_pFieldOne;
	
	// アイテムの数を取得
	int m_coinNum;
	int m_diamondNum;
	// コインの位置を取得
	std::vector<int> m_CoinPosX;
	std::vector<int> m_CoinPosY;
	// ダイヤモンドの位置を取得
	std::vector<int> m_diamondPosX;
	std::vector<int> m_diamondPosY;

	// 入手してアイテムを各自でカウント
	int m_coinCount = 0;
	int m_diamondCount = 0;

	// メンバ関数ポインタ
	void (SceneMain::* m_updateFunc)();
	// ポーズ画面用クラス
	PauseScreen* m_pPause;
	bool m_isGameClear;
	bool m_isGameOver;

};