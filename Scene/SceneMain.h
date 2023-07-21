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
	// ������m�F
	void FieldCheckHit();
	void ItemCheckHit();
	// �Q�[���S�̂̍X�V����
	void UpdateMain();
	void UpdateMenu();
private:
	int m_slowCount;
	// �v���C���[�N���X�̃|�C���^
	Player* m_pPlayer;
	// �A�C�e���N���X�̃|�C���^
	std::shared_ptr<ItemManegaer>m_pItem;
	// �}�b�v�N���X�̃|�C���^
	Field* m_pField;
	// UI�N���X�̃|�C���^
	UI* m_pUi;
	// �}�b�v���N���X�̃|�C���^
	Map* m_pMap;
	std::shared_ptr<FieldBase> m_pFieldOne;
	
	// �A�C�e���̐����擾
	int m_coinNum;
	int m_diamondNum;
	// �R�C���̈ʒu���擾
	std::vector<int> m_CoinPosX;
	std::vector<int> m_CoinPosY;
	// �_�C�������h�̈ʒu���擾
	std::vector<int> m_diamondPosX;
	std::vector<int> m_diamondPosY;

	// ���肵�ăA�C�e�����e���ŃJ�E���g
	int m_coinCount = 0;
	int m_diamondCount = 0;

	// �����o�֐��|�C���^
	void (SceneMain::* m_updateFunc)();
	// �|�[�Y��ʗp�N���X
	PauseScreen* m_pPause;
	bool m_isGameClear;
	bool m_isGameOver;

};