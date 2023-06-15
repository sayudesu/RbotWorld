#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

class ItemBase;
class ItemManegaer
{
public:
	ItemManegaer();
	virtual ~ItemManegaer();

	void Load();
	void Create();
	void Delete();
	void Update();
	void Draw();

	// �ʒu���󂯎��
	void SetPos(VECTOR pos) { m_pos = pos; }
	// �T�C�Y���󂯎��
	void SetSize(VECTOR size) { m_size = size; }
	// �p�x���󂯎��
	void SetRota(VECTOR rota) { m_rota = rota; }

private:
	// ���f���n���h��
	int m_hItem;
	// �ʒu
	VECTOR m_pos;
	// �T�C�Y
	VECTOR m_size;
	// �p�x
	VECTOR m_rota;

	// �R�C���N���X
	std::shared_ptr<ItemBase> m_pCoin;
};
