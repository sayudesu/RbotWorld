#pragma once
#include <DxLib.h>

class Field
{
public:
	Field();
	virtual ~Field();

	void Init();
	void End();
	void Update();
	void Draw();

	// マップのサイズを取得する
	float GetSizeX() const;
	float GetSizeY() const;
	float GetSizeZ() const;

	// マップの中心座標を取得する
	VECTOR GetCenter() const;

	// マップチップ情報を取得する
	int GetChipNumX() const;
	int GetChipNumZ() const;
	// 指定した場所がブロックかどうかを取得する
	bool IsBlock(int x, int z) const;

	// 指定したチップの3D座標を取得する(中心位置)
	VECTOR GetChipPos(int x, int z) const;
private:
	int m_texture;
};

