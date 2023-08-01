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
	// ‰æ‘œƒnƒ“ƒhƒ‹
	int m_handle;
	// À•W
	int m_x;
	int m_y;
};

