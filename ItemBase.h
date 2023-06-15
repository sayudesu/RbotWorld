#pragma once
#include <DxLib.h>
class ItemBase
{
public:
	ItemBase(int handle);
	virtual ~ItemBase();

	virtual void Update();
	virtual void Draw();

	// �ʒu���󂯎��
	void SetPos(VECTOR pos) { m_pos = pos; }
	// �T�C�Y���󂯎��
	void SetSize(VECTOR size) { m_size = size; }
	// �p�x���󂯎��
	void SetRota(VECTOR rota) { m_rota = rota; }

protected:
	int m_hItem;
	// �ʒu
	VECTOR m_pos;
	// �T�C�Y
	VECTOR m_size;
	// �p�x
	VECTOR m_rota;
};

