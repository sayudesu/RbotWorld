#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

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
	void CreateCoin(int coinPosX[], int coinPosY[], int coinNum);

	void Delete();
	void Update();
	void Draw();

private:
	// ���f���n���h��
	int m_hItem;
	// �ʒu
	VECTOR m_pos;
	// �T�C�Y
	VECTOR m_size;
	// �p�x
	VECTOR m_rota;

	std::vector<int>m_coinPosX;
	std::vector<int>m_coinPosY;

	// �R�C���N���X
	std::vector<std::shared_ptr<ItemBase>> m_pCoin;
};
