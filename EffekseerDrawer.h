#pragma once
// �G�t�F�N�V�A�Ǘ�
#include <DxLib.h>
class EffekseerDrawer
{
public:
	EffekseerDrawer();
	virtual~EffekseerDrawer();

	int Init();
	void End();
	void Update();
	void Draw(VECTOR pos);
private:
	int m_hEff;
	int m_hPlayEff;
	int m_hBg;
	int m_time;
};

