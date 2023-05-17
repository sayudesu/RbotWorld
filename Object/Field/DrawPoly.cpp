#include "DrawPoly.h"
#include <vector>

namespace
{
	// �}�b�v�`�b�v�̕�����
	constexpr float kTextureDivNumX_F = 11.0f;
	constexpr float kTextureDivNumY_F = 8.0f;
	// �g�p����`�b�v�̔ԍ�(���ʒu�A�c�ʒu���w�肷��)
	constexpr int kUseTextureX = 8;
	constexpr int kUseTextureY = 3;
	// �g�p����`�b�v�̃e�N�X�`�����W
	constexpr float kTexxtureMinU = 1.0f / kTextureDivNumX_F * kUseTextureX;
	constexpr float kTexxtureMaxU = kTexxtureMinU + 1.0f / kTextureDivNumX_F;
	constexpr float kTexxtureMinV = 1.0f / kTextureDivNumY_F * kUseTextureY;
	constexpr float kTexxtureMaxV = kTexxtureMinV + 1.0f / kTextureDivNumY_F;
}

void Poly::DrawCube(VECTOR pos, float size, int texture)
{
	constexpr int polyNum = 2;//�����`�P�ʕ`�悷��̂ɕK�v�ȃ|���S���̐�
	constexpr int vtxNum = polyNum * 3;//�|���S���P�ʕ��̕`��ɕK�v�Ȓ��_��
	constexpr int cuveVtxNum = vtxNum * 6;//������1�`�悷��̂ɕK�v�Ȓ��_��

	std::vector<VERTEX3D> drawVtx; //�`��Ɏg�p���钸�_�f�[�^

	VERTEX3D polyVtx[vtxNum];

	//����
	polyVtx[0].pos = VGet(-size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[0].norm = VGet(0.0f, 0.0f, -1.0f);
	polyVtx[0].dif = GetColorU8(255, 255, 255, 255);
	polyVtx[0].spc = GetColorU8(255, 255, 255, 255);
	polyVtx[0].u = kTexxtureMinU;
	polyVtx[0].v = kTexxtureMinV;
	polyVtx[0].su = 0.0f;
	polyVtx[0].sv = 0.0f;

	//0�Ԗڂ̒��_�̏����ȍ~�̒��_�ɃR�s�[����
	for (int i = 1; i < vtxNum; i++) {
		polyVtx[i] = polyVtx[0];
	}

	//�E��
	polyVtx[1].pos = VGet(size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[1].u = kTexxtureMaxU;
	polyVtx[1].v = kTexxtureMinV;
	//����
	polyVtx[2].pos = VGet(-size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[2].u = kTexxtureMinU;
	polyVtx[2].v = kTexxtureMaxV;
	//�E��
	polyVtx[3].pos = VGet(size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[3].u = kTexxtureMaxU;
	polyVtx[3].v = kTexxtureMaxV;
	//����
	polyVtx[4].pos = VGet(-size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[4].u = kTexxtureMinU;
	polyVtx[4].v = kTexxtureMaxV;
	//�E��
	polyVtx[5].pos = VGet(size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[5].u = kTexxtureMaxU;
	polyVtx[5].v = kTexxtureMinV;

	//�`��̒��_�f�[�^�ɓo�^
	for (auto& vtx : polyVtx) {
		drawVtx.push_back(vtx);
	}

	//��]�s��
	MATRIX mtx = MGetRotY(DX_PI_F / 2.0f);
	//���ʂ̒��_�f�[�^�����A�o�^
	for (int i = 0; i < 3; i++) {
		for (auto& vtx : polyVtx) {
			vtx.pos = VTransform(vtx.pos, mtx);
			vtx.norm = VTransform(vtx.norm, mtx);
			drawVtx.push_back(vtx);
		}
	}

	mtx = MGetRotZ(DX_PI_F / 2.0f);
	for (auto& vtx : polyVtx) {
		vtx.pos = VTransform(vtx.pos, mtx);
		vtx.norm = VTransform(vtx.norm, mtx);
		drawVtx.push_back(vtx);
	}

	mtx = MGetRotZ(DX_PI_F);
	for (auto& vtx : polyVtx) {
		vtx.pos = VTransform(vtx.pos, mtx);
		vtx.norm = VTransform(vtx.norm, mtx);
		drawVtx.push_back(vtx);
	}

	//�Ō�Ɉʒu���𑫂�
	for (auto& vtx : drawVtx) {
		vtx.pos = VAdd(vtx.pos, pos);
	}

	DrawPolygon3D(drawVtx.data(), static_cast<int>(drawVtx.size() / 3), texture, true);
}
