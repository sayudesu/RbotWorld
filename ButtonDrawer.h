#pragma once
class ButtonDrawer
{
public:
	ButtonDrawer();
	virtual ~ButtonDrawer();

	void Init();
	void Update(int x,int y);
	void Draw();
private:
	// ‰æ‘œƒnƒ“ƒhƒ‹
	int m_handle;
	// À•W
	int m_x;
	int m_y;
};

