#pragma once
class Shadow
{
public:
	Shadow(const char* fileName, const char* fileName_n);
	void Update();
	void Draw();
	void DrawGraphWithShader(int x,int y, int texH,int normH,int psH,int transFlg);
private:
	int m_handle = -1;
	int m_handle2 = -1;
	int m_psH = -1;
	int m_x = 0, m_y = 0;
};


