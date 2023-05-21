#pragma once
#include <vector>
#include <memory>

namespace
{
	// �t�@�C����
	const char* const kFileStageName = "Data/Model/Stage/Field.mv1";

	// �n�ʂɕ~���l�߂�u���b�N�̐�
	constexpr int kBlockNumX = 50;
	constexpr int kBlockNumZ = 5;

	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	// �u���b�N�̈�ӂ̒���
	constexpr float kBlockSideLength = 100.0f;

	// �n�ʂ̈�ӂ̒���
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;
}

class Animation;
class Field
{
public:
	Field();
	virtual ~Field();

	void Init();
	void End();
	void Update();
	void Draw();

	// ���f���̐�
	int GetModelNum() { return kBlockNum; }
	// �w�肵���ԍ��̃��f���̃n���h�����擾����
	int GetModelHandle()const;

	int GetColFrameIndex()const;



private:
	std::vector<std::shared_ptr<Animation>> m_pModel;
};

