#include "GraphAnimation.h"

GraphAnimation::GraphAnimation()
{
}

GraphAnimation::~GraphAnimation()
{
}

void GraphAnimation::Animation(int& imgX, int imgSizeX, int imgNumMax)
{
	// ���݂̉摜���摜�̉E�[��菬����������摜�\���ʒu���E�ɂ��炷
	// �E�[�܂œ��B������摜�`������Ȃ�
	if (imgX < imgSizeX * imgNumMax)
	{
		imgX += imgSizeX;
	}
}
