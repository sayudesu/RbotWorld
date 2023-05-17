#pragma once
#include <DxLib.h>

class Field
{
public:
	Field();
	virtual ~Field();

	void Init();
	void End();
	void Update();
	void Draw();

	// �}�b�v�̃T�C�Y���擾����
	float GetSizeX() const;
	float GetSizeY() const;
	float GetSizeZ() const;

	// �}�b�v�̒��S���W���擾����
	VECTOR GetCenter() const;

	// �}�b�v�`�b�v�����擾����
	int GetChipNumX() const;
	int GetChipNumZ() const;
	// �w�肵���ꏊ���u���b�N���ǂ������擾����
	bool IsBlock(int x, int z) const;

	// �w�肵���`�b�v��3D���W���擾����(���S�ʒu)
	VECTOR GetChipPos(int x, int z) const;
private:
	int m_texture;
};

