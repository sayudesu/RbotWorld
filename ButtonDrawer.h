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
	// �摜�n���h��
	int m_handle;
	// ���W
	int m_x;
	int m_y;
};

