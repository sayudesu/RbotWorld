#pragma once
#include <Dxlib.h>
#include <vector>
#include <memory>

namespace
{
	// �����蔻��Ƃ��ė��p����t���[�����O
	const char* const kCollsionFielfFrameName = "CollField";
	const char* const kCollsionEnemyFrameName = "Coll";
}

class Model
{
public:
	// �t�@�C�������w�肵�ă��[�h���s��
	Model(const char* fileName);
	// �w�肳�ꂽ�n���h���̃��f����DuplicateModel���Đ�������
	Model(int orgModel);
	virtual ~Model();

	// �����蔻��ݒ�
	void SetUseCollision(bool isUse, bool isNeedUpdate);
	
	void Init(){}
	void End(){}
	void Update();
	void Draw();

	//���f���n���h���擾
	int GetModelHandle() const { return m_modelHandle; }

	// �����蔻��Ɏg�p����t���[���C���f�b�N�X���擾����
	int GetColFrameIndex()const { return m_colFrameIndex; }

	VECTOR GetModelPos() { return m_pos; }

	//�\���ʒu�̐ݒ�
	void SetPos(VECTOR pos);

	// ��]��Ԃ̐ݒ�
	void SetRot(VECTOR rot);

	// �T�C�Y�̐ݒ�
	void SetSize(VECTOR size);


	// �A�j���[�V�����̐���

	/// <summary>
	/// �A�j���[�V������ݒ肷��(�ς��Ɛ؂�ւ���)
	/// </summary>
	/// <param name="animNo">�ύX��A�j���[�V�����ԍ�</param>
	/// <param name="isLoop">�A�j���[�V���������[�v�����邩</param>
	/// <param name="isForceChange">���łɎw�肳�ꂽ�A�j�����Đ�����Ă���ꍇ���ύX���邩</param>
	void SetAnimation(int animNo, bool isLoop, bool isForceChange);

	// �A�j���[�V������ω�������(changeFrame�t���[�������Đ؂�ւ���)
	void ChangeAnimation(int animNo, bool isLoop, bool isForceChange, int changeFrame);

	// ���݂̃A�j���[�V�������I�����Ă��邩�ǂ������擾����(Loop�A�j���̏ꍇ�͎擾�ł��Ȃ� = false��Ԃ�)
	bool IsAnimEnd();


private:
	//�A�j���[�V�������
	struct AnimData
	{
		int animNo;			// �A�j���[�V�����ԍ�

		int attachNo;		// �A�^�b�`�ԍ�
		float totalTime;	// �A�j���[�V�����̑��Đ�����
		bool isLoop;		// �A�j���[�V���������[�v���邩
	};
private:
	// �A�j���[�V�����f�[�^�̃N���A
	void clearAnimData(AnimData& anim);

	// �A�j���[�V�����̍X�V
	void updateAnim(AnimData anim, float dt = 1.0f);

	// ���݂̃A�j���[�V�����؂�ւ���񂩂�A�j���[�V�����̃u�����h����ݒ肷��
	void updateAnimBlendRate();

private:
	// ���f���̃n���h��
	int m_modelHandle;

	// ���f���̈ʒu
	VECTOR m_pos;

	// �����蔻������g�p����
	bool m_isUseCllision;
	// �����蔻����𖈃t���[���X�V����
	bool m_isUpdateCollision;
	// �����蔻��Ƃ��ė��p����t���[���̃C���f�b�N�X
	int m_colFrameIndex;

	// �A�j���[�V�����̃A�^�b�`�ԍ�
	AnimData m_animPrev;	// �ύX�O�A�j���[�V�������
	AnimData m_animNext;	// �ύX��A�j���[�V�����f�[�^

	//�A�j���[�V�����̐؂�ւ����
	int m_animChangeFrame;			// ���݂̐؂�ւ��t���[����
	int m_animChangeFrameTotal;		// �؂�ւ��ɂ����鑍�t���[����
};

