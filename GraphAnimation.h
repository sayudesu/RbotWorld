#pragma once

// �摜�A�j���[�V�����p�N���X
class GraphAnimation
{
public:
	GraphAnimation();
	virtual ~GraphAnimation();

	/// <summary>
	/// �摜���A�j���[�V����������
	/// </summary>
	/// <param name="imgX">      �摜����	        </param>
	/// <param name="imgSizeX">  �摜�P�����̑傫�� </param>
	/// <param name="imgNumMax"> �ǂݍ��܂���摜�� </param>
	void Animation(int& imgX, int imgSizeX, int imgNumMax);
};

