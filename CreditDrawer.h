#pragma once
class CreditDrawer
{
public:
	CreditDrawer();
	virtual ~CreditDrawer();

	void Init();
	void Update(int x, int y);
	void Draw();
private:
	// 画像ハンドル
	int m_handle;
	// 座標
	int m_x;
	int m_y;
};

