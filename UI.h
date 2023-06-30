#pragma once
#include "ItemName.h"

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
	void Score();
private:
	// ���݂̃A�C�e���擾��
	int m_itemNum[static_cast<int>(Item::itemMaxNum)];
	// �ő�A�C�e����
	int m_itemMaxNum[static_cast<int>(Item::itemMaxNum)];
	// �X�R�A�p
	int m_score;
	// �`�揈���֌W
	int drawCount[3];
	bool m_isCharenge[3];
};

