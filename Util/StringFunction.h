#pragma once
#include <vector>
#include <memory>

class AddString;

//////////////////
// �e�L�X�g�ݒ� //
//////////////////
class StringFunction
{
public:
	StringFunction();
	virtual ~StringFunction();
	virtual void InitFont(const char* fontPath, const char* fontName);
	/// <summary>
	/// ������ǉ�����
	/// </summary>
	/// <param name="x">���W</param>
	/// <param name="y">���W</param>
	/// <param name="text">����</param>
	/// <param name="color">�F</param>
	/// <param name="size">�傫��</param>
	/// <param name="font">�t�H���g�p�X</param>
	virtual void Add(int x, int y, const char* text, int color, int size);

	virtual void AddStatic(int x, int y, const char* text,int num, int color, int size);
	/// <summary>
	/// �����̈ʒu�ύX
	/// </summary>
	/// <param name="addNo">�ύX�����������ԍ�</param>
	/// <param name="x">���W</param>
	/// <param name="y">���W</param>
	virtual void Update(int addNo,int x, int y);
	/// <summary>
	/// �`�悳����
	/// </summary>
	/// <param name="addNo">�`�悵�Ă������ԍ�</param>
	virtual void Draw(int addNo);
	virtual void DrawStatic(int addNo);

private:
	const char* m_fontName;
	const char* m_fontPathName;
	std::vector<std::shared_ptr<AddString>>m_pAddString;
};

//////////////////
// �e�L�X�g�쐬 //
//////////////////
class AddString
{
public:
	/// <summary>
	/// ������ǉ�����
	/// </summary>
	/// <param name="x">���W</param>
	/// <param name="y">���W</param>
	/// <param name="text">����</param>
	/// <param name="color">�F</param>
	/// <param name="size">�傫��</param>
	/// <param name="font">�t�H���g�p�X</param>//
	AddString(int x, int y, const char* text, int color, int size, const char* fontPath, const char* font);
	AddString(int x, int y, const char* text, int num, int color, int size, const char* fontPath, const char* font);
	virtual ~AddString();
	/// <summary>
	/// �����̈ʒu
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	virtual void UpdateCharenge(int x, int y);
	virtual void UpdateStatic(int x, int y);
	virtual void Draw();
	virtual void DrawStatic();
private:
	int m_x;
	int m_y;
	const char* m_text;
	int m_color;
	int m_size;
	const char* m_font;
	int m_fontHandle;

	int m_xStatic;
	int m_yStatic;
	int m_num;
};

