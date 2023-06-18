#pragma once
#include <DxLib.h>
class ItemBase
{
public:
	ItemBase(int handle);
	virtual ~ItemBase();

	virtual void Update();
	virtual void Draw();

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

protected:
	// �A�C�e���̃n���h��
	int m_hItem;
	// �ʒu
	VECTOR m_pos;
	// �T�C�Y
	VECTOR m_size;
	// ��]
	VECTOR m_rota;
};

