#pragma once
#include "Util/Vec3.h"
#include <vector>
#include <memory>
class Text;
/// <summary>
/// ������`�悳����N���X
/// </summary>
class CreateText
{
public:
	CreateText();
	virtual ~CreateText();

	/// <summary>
	/// �e�L�X�g�̐�����Text�N���X���C���X�^���X���쐬����
	/// </summary>
	/// <param name="x">    �ʒu  </param>
	/// <param name="y">    �ʒu  </param>
	/// <param name="text"> ����  </param>
	/// <param name="color">�F	  </param>
	/// <param name="size"> �T�C�Y</param>
	/// <param name="frame">�g�@�@</param>
	void Add(int x,int y,const char* text,int color,int size, bool frame);

	/// <summary>
	/// �p�b�h���͂̍X�V����
	/// </summary>
	void Update();

	// ���W��ύX���܂�
	void UpdatePos(int x, int y);

	/// <summary>
	/// �e�L�X�g��`�悷��
	/// </summary>
	void Draw();

	// �Z���N�g�i���o�[�����Z�b�g����
	void ResetSelectNo();

	/// <summary>
	/// �I�������ԍ�
	/// </summary>
	/// <returns>���Ԗڂ�I����������Ԃ�</returns>
	int GetSelectNo() { return m_selectNo; }
private:
	std::vector<std::shared_ptr<Text>> m_pText;
	// �I���������ǂ���
	bool m_isSelect;
	// �I�����̐�
	int selectNum;
	int selectNow;
	int m_selectNo;
	// �~�̔��a
	int selectRad;
};

class Text
{
public:
	/// <summary>
	/// �e�L�X�g�쐬
	/// </summary>
	/// <param name="x">    �ʒu  </param>
	/// <param name="y">    �ʒu  </param>
	/// <param name="text"> ����  </param>
	/// <param name="color">�F    </param>
	/// <param name="size"> �T�C�Y</param>
	/// <param name="frame">�g�@�@</param>
	Text(int x, int y, const char* text, int color, int size,bool frame);
	virtual ~Text();
	void UpdatePos(int x, int y);
	void Draw();

	void SetSelectFrame(bool isSelect);
	void SetSelectRadius(int rad);
	void BlendMode();
private:
	// �ʒu
	int m_x;
	int m_y;
	// ���̈ʒu���炸�炷�p
	int m_changePosX;
	int m_changePosY;
	// ����
	const char* m_text;
	// �F
	int m_color;
	// �g��\�����邩�ǂ���
	bool m_isFrame;
	// �����f�[�^
	int m_fontHandle;
	// �I�����Ă邩�ǂ���
	bool m_isSelect;
	// �I����̃G�t�F�N�g�~�̑傫��
	int m_rad;
	// �u�����h��
	int m_blend;
};

