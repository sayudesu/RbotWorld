#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "ItemName.h"

class ItemBase;
class ItemManegaer
{
public:
	ItemManegaer();
	virtual ~ItemManegaer();

	void Load();

	/// <summary>
	/// �R�C���̍쐬
	/// </summary>
	/// <param name="coinPosX">�R�C����X�ʒu</param>
	/// <param name="coinPosY">�R�C����Y�ʒu</param>
	/// <param name="coinNum"> �R�C���̐�   </param>
	void CreateCoin(std::vector<int> coinPosX, std::vector<int>coinPosY, int coinNum);
	/// <summary>
	/// �_�C���̍쐬
	/// </summary>
	/// <param name="coinPosX">�_�C����X�ʒu</param>
	/// <param name="coinPosY">�_�C����Y�ʒu</param>
	/// <param name="coinNum"> �_�C���̐�   </param>
	void CreateDiamond(std::vector<int> diamondPosX, std::vector<int>diamondPosY, int diamondNum);

	void Delete();
	void Update();
	void Draw();

	// �A�C�e�������������ꍇ���̔ԍ���Ԃ�
	void SetEraseNo(Item name, int eraseNo);

	bool isErase(Item name,int eraseNo);

private:
	// ���f���n���h��
	int m_hItem[2];
	// �ʒu
	VECTOR m_pos;
	// �T�C�Y
	VECTOR m_size;
	// �p�x
	VECTOR m_rota;

	// �R�C���̈ʒu���ꎞ�I�Ɏ󂯎��
	std::vector<int>m_coinPosX;
	std::vector<int>m_coinPosY;

	// �_�C���̈ʒu���ꎞ�I�Ɏ󂯎��
	std::vector<int>m_diamondPosX;
	std::vector<int>m_diamondPosY;

	// �R�C���N���X
	std::vector<std::shared_ptr<ItemBase>> m_pCoin;
	std::vector<std::shared_ptr<ItemBase>> m_pDiamond;
	std::vector<bool>m_isErase;
};
