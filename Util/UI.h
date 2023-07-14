#pragma once
#include "ItemName.h"
#include "Vec3.h"

#define DEBUG_ false;

namespace
{
	// �`�������W�̐�
	constexpr int kCharengeNum = 2;
	// �A�C�e���̍ő�l
	constexpr int kItemNum = static_cast<int>(Item::itemMaxNum);
}

class Achievement;
class StringStatic;


class UI
{
public:
	UI();
	virtual ~UI();

	// �X�V����
	void Update();
	// �`��
	void Draw();
	/// <summary>
	/// �A�C�e�������擾���Ă��邩
	/// </summary>
	/// <param name="name">�A�C�e���̖��O</param>
	/// <param name="num">�A�C�e���̐�</param>
	void SetItemNum(Item  name, int num);
	/// <summary>
	/// �A�C�e���̍ő吔
	/// </summary>
	/// <param name="name">�A�C�e���̖��O</param>
	/// <param name="num">�A�C�e���ő�̐�</param>
	void SetItemMaxNum(Item  name, int num);

	// �X�R�A��Ԃ�
	int GetScore() { return m_score; }
private:
	// �`�������W-----------------------------------
	void ItemMaxCharenge();// �A�C�e���}�b�N�X�`�������W	

	// �X�R�A�p-------------------------------------
	void Score();// �X�R�A�̌v�Z
private:
	// �A�C�e���Ǘ�----------------------------------
	int m_itemNum[kItemNum];// ���݂̃A�C�e���擾��
	int m_itemMaxNum[kItemNum];// �ő�A�C�e����

	// �`�������W�p---------------------------------
	Vec3 m_charengePos[kCharengeNum];// �ʒu
	int m_drawCount[kCharengeNum];// �`�掞�ԃJ�E���g
	int m_charengeColor[kCharengeNum];// �F�w��
	bool m_isCharenge[kCharengeNum];// �����`�揈��
	bool m_isCharengeDraw[kCharengeNum];// ������`��
	const char* m_charengeString[kCharengeNum];// ����

	// �X�R�A�p-------------------------------------
	int m_score;

	// �����`��N���X-------------------------------
	Achievement* m_pString;
	StringStatic* m_pStringStatic;

	//----------------------------------------------

#if DEBUG_
	Vec3 m_scorePos[kItemNum];// �ʒu
	const char* m_scoreString[kItemNum];// ����
#endif
};

