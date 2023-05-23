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
	int GetModelNum();
	// �w�肵���ԍ��̃��f���̃n���h�����擾����
	int GetModelHandle(int handlNum);

	int GetColFrameIndex()const;

private:
	std::vector<std::shared_ptr<Animation>> m_pModel;
//	std::vector<std::shared_ptr<Animation>, std::vector<int>> m_pModel;
};

