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

	// 位置を受け取る
	void SetPos(VECTOR pos) { m_pos = pos; }
	// サイズを受け取る
	void SetSize(VECTOR size) { m_size = size; }
	// 角度を受け取る
	void SetRota(VECTOR rota) { m_rota = rota; }

private:
	// モデルハンドル
	int m_hItem;
	// 位置
	VECTOR m_pos;
	// サイズ
	VECTOR m_size;
	// 角度
	VECTOR m_rota;

	// コインクラス
	std::shared_ptr<ItemBase> m_pCoin;
};
