#pragma once
#include <DxLib.h>
class ItemBase
{
public:
	ItemBase(int handle);
	virtual ~ItemBase();

	virtual void Update();
	virtual void StartUpdate();
	virtual void Draw();

	virtual void Erase();
	virtual void ItemState();
	/// <summary>
	/// オブジェクトを回転させます
	/// </summary>
	virtual void UpdateRota();

	/// <summary>
	/// 位置を受け取る
	/// </summary>
	/// <param name="pos">位置</param>
	void SetPos(VECTOR pos) { m_pos = pos; }
	/// <summary>
	/// サイズを受け取る
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(VECTOR size) { m_size = size; }
	/// <summary>
	/// 角度を受け取る
	/// </summary>
	/// <param name="rota">角度</param>
	void SetRota(VECTOR rota){ m_rota = rota; }
	
	/// <summary>
	/// アイテムが消えるかどうか
	/// </summary>
	/// <param name="isErase"></param>
	void SetEraseItem(bool isErase);

	// アイテムが消えているかどうか
	bool isGetItem() { return m_isErase; }

protected:
	// アイテムのハンドル
	int m_hItem;
	// 位置
	VECTOR m_pos;
	// サイズ
	VECTOR m_size;
	// 回転
	VECTOR m_rota;
	// アイテムを消すための処理
	bool m_isErase;
	// メンバ関数ポインタ
	void (ItemBase::*m_updateFunc)();
};

