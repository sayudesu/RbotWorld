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
	// �摜�n���h��
	int m_handle;
	// ���W
	int m_x;
	int m_y;
};

