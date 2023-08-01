#pragma once

class CreateText;
class ButtonDrawer;

class PauseScreen
{
public:
	PauseScreen();
	virtual~PauseScreen();
	// ����������
	void Init();
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
	// �V�[���؂�ւ��p
	bool isSetMainScene() { return m_isMainScene; }
	bool isSetTitleScene() { return m_isTitleScene; }
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
	// �{�^���������o�����ǂ���
	bool m_isButtonSettingDraw;
	// �V�[���؂�ւ��p
	bool m_isMainScene;
	bool m_isTitleScene;
	// �I��p�e�L�X�g��`�悵�܂�
	CreateText* m_pText;
	// ���������\��
	ButtonDrawer* m_pButtonSetting;
};

