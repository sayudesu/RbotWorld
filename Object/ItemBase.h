#pragma once
#include <DxLib.h>
class ItemBase
{
public:
	ItemBase(int handle);
	virtual ~ItemBase();

	virtual void Update();
	virtual void StartUpdate();
	virtual void Draw();

	virtual void Erase();
	virtual void ItemState();
	/// <summary>
	/// �I�u�W�F�N�g����]�����܂�
	/// </summary>
	virtual void UpdateRota();

	/// <summary>
	/// �ʒu���󂯎��
	/// </summary>
	/// <param name="pos">�ʒu</param>
	void SetPos(VECTOR pos) { m_pos = pos; }
	/// <summary>
	/// �T�C�Y���󂯎��
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	void SetSize(VECTOR size) { m_size = size; }
	/// <summary>
	/// �p�x���󂯎��
	/// </summary>
	/// <param name="rota">�p�x</param>
	void SetRota(VECTOR rota){ m_rota = rota; }
	
	/// <summary>
	/// �A�C�e���������邩�ǂ���
	/// </summary>
	/// <param name="isErase"></param>
	void SetEraseItem(bool isErase);

	// �A�C�e���������Ă��邩�ǂ���
	bool isGetItem() { return m_isErase; }

protected:
	// �A�C�e���̃n���h��
	int m_hItem;
	// �ʒu
	VECTOR m_pos;
	// �T�C�Y
	VECTOR m_size;
	// ��]
	VECTOR m_rota;
	// �A�C�e�����������߂̏���
	bool m_isErase;
	// �����o�֐��|�C���^
	void (ItemBase::*m_updateFunc)();
};

