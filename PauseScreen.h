#pragma once
#include "Vec3.h"

class PauseScreen
{
public:
	PauseScreen();
	virtual~PauseScreen();
	// �|�[�Y��ʑS�̂̏���
	void Update();
	// �|�[�Y��ʍŏ��̏���
	void UpdateStart();
	// �|�[�Y���C����ʕ\��
	void UpdateMain();
	// �|�[�Y��ʏI������
	void UpdateEnd();
	// �`��
	void Draw();
public:
	// �|�[�Y��ʂ��I�����������ǂ���
	void GetPauseEnd(bool isEnd) { m_isPauseEnd = isEnd; }
	// �|�[�Y��ʂ��I���������ǂ���
	bool isSetEnd() { return m_isEnd; }
	// �ϐ���������
	void Reset();
private:
	// �����o�֐��|�C���^
	void (PauseScreen::* m_updateFunc)();
	// �l�p�`�̈ʒu����
	int m_boxPos;
	// �|�[�Y��ʏI������
	bool m_isPauseEnd;
	// �|�[�Y��ʂ��I���������ǂ���
	bool m_isEnd;
};

