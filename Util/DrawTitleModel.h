#pragma once
class Model;
class TitleDrawModeler
{
public:
	TitleDrawModeler();
	virtual ~TitleDrawModeler();

	void Update();
	void Draw();

	// �Q�[���X�^�[�g�Ɠ����ɉE�Ɉړ�������
	void SetStartPos(bool move) { m_isMoveSelect = move; }

	bool GetSceneChange() { return m_isSceneChange; }
private:
	// ���f���N���X
	Model* m_pModel;
	// ���f����Y���W����
	float m_posY;
	// �V�[�����؂�ւ�邩�ǂ���
	bool m_isMoveSelect;
	// ���f�����E�܂ňړ��������ǂ���
	bool m_isSceneChange;
};

