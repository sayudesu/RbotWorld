#pragma once
#include <DxLib.h>
class ItemBase
{
public:
	ItemBase(int handle);
	virtual ~ItemBase();

	virtual void Update();
	virtual void Draw();

	// 位置を受け取る
	void SetPos(VECTOR pos) { m_pos = pos; }
	// サイズを受け取る
	void SetSize(VECTOR size) { m_size = size; }
	// 角度を受け取る
	void SetRota(VECTOR rota) { m_rota = rota; }

protected:
	int m_hItem;
	// 位置
	VECTOR m_pos;
	// サイズ
	VECTOR m_size;
	// 角度
	VECTOR m_rota;
};

