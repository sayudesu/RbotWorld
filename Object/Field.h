#pragma once
#include <vector>
#include <array>
#include <memory>

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
	int GetModelNumX();
	int GetModelNumY();
	// �w�肵���ԍ��̃��f���̃n���h�����擾����
	int GetModelHandle(int y, int x);
	// ���f���̈ʒu��Ԃ�
	float SetPosY(int y, int x);
	// ���f���̃t���[���C���f�b�N�X��Ԃ�
	int GetColFrameIndex(int y, int x)const;

private:
	std::shared_ptr<Animation> m_pModel[5][350];
//	std::vector<std::shared_ptr<Animation>> m_pModel;
//	std::vector<std::vector<std::shared_ptr<Animation>>> m_pModel;
};

