#pragma once
#include "Util/Vec2.h"
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
	virtual void DrawDef(Vec2 pos,const char* text,int size,int color = 0xffffff);//������\��

	// �h��Ȃ����ɕ������オ���čs�����X�ɏ�����
	// ���W�A�����A�T�C�Y�A�㏸���鑬���A�F(�����F���w�肵�Ȃ��Ɣ�)
	virtual void DrawUp(Vec2 pos, const char* text, int size,float speedUp, int color = 0xffffff);
private:
	// �����̈ʒu
	Vec2 m_posUp;

	int m_hDef;
	int m_hTextUp;

	// ��x�����̏���
	bool m_isTempDef;
	bool m_isTempUp;
};

