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
	void Update();
	/// <summary>
	/// �e�L�X�g��`�悷��
	/// </summary>
	void Draw();
private:
	std::vector<std::shared_ptr<Text>> m_pText;
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

	void Draw();
private:
	// �ʒu
	int m_x;
	int m_y;
	// ����
	const char* m_text;
	// �F
	int m_color;
	// �g��\�����邩�ǂ���
	bool m_isFrame;
	// �����f�[�^
	int m_fontHandle;
};

