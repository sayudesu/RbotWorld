#pragma once

/// <summary>
/// ������`�悳����N���X
/// </summary>
class CreateText
{
public:
	CreateText();
	virtual ~CreateText();

	// �V���v���ȃe�L�X�g�\��
	// ���W�A�����A�T�C�Y�A�F(�����F���w�肵�Ȃ��Ɣ�)
	virtual void DrawDef(int x, int y,const char* text,int size,int color = 0xffffff);//������\��

	// �h��Ȃ����ɕ������オ���čs�����X�ɏ�����
	// ���W�A�����A�T�C�Y�A�F(�����F���w�肵�Ȃ��Ɣ�)
	virtual void DrawUp(int x, int y, const char* text, int size, int color = 0xffffff);
private:
	// 
	int m_stringUpX;
	int m_stringUpY;
	//
	bool m_isTempPos;
};

