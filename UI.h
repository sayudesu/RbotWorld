#pragma once
#include "ItemName.h"
class UI
{
public:
	UI();
	virtual ~UI();

	void Update();
	void Draw();

	void SetItemNum(Item  name, int num);
	void SetItemMaxNum(Item  name, int num);

private:
	int m_coinNum;
	int m_diamondNum;

	int m_coinMaxNum;
	int m_diamondMaxNum;

	int drawCount[3];
	bool m_isCoinCharenge[3];
};

