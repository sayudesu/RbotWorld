#include "DrawPoly.h"
#include <vector>

namespace
{
	// マップチップの分割数
	constexpr float kTextureDivNumX_F = 11.0f;
	constexpr float kTextureDivNumY_F = 8.0f;
	// 使用するチップの番号(横位置、縦位置を指定する)
	constexpr int kUseTextureX = 8;
	constexpr int kUseTextureY = 3;
	// 使用するチップのテクスチャ座標
	constexpr float kTexxtureMinU = 1.0f / kTextureDivNumX_F * kUseTextureX;
	constexpr float kTexxtureMaxU = kTexxtureMinU + 1.0f / kTextureDivNumX_F;
	constexpr float kTexxtureMinV = 1.0f / kTextureDivNumY_F * kUseTextureY;
	constexpr float kTexxtureMaxV = kTexxtureMinV + 1.0f / kTextureDivNumY_F;
}

void Poly::DrawCube(VECTOR pos, float size, int texture)
{
	constexpr int polyNum = 2;//正方形１面描画するのに必要なポリゴンの数
	constexpr int vtxNum = polyNum * 3;//ポリゴン１面分の描画に必要な頂点数
	constexpr int cuveVtxNum = vtxNum * 6;//立方体1つ描画するのに必要な超点数

	std::vector<VERTEX3D> drawVtx; //描画に使用する頂点データ

	VERTEX3D polyVtx[vtxNum];

	//左上
	polyVtx[0].pos = VGet(-size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[0].norm = VGet(0.0f, 0.0f, -1.0f);
	polyVtx[0].dif = GetColorU8(255, 255, 255, 255);
	polyVtx[0].spc = GetColorU8(255, 255, 255, 255);
	polyVtx[0].u = kTexxtureMinU;
	polyVtx[0].v = kTexxtureMinV;
	polyVtx[0].su = 0.0f;
	polyVtx[0].sv = 0.0f;

	//0番目の頂点の情報を以降の頂点にコピーする
	for (int i = 1; i < vtxNum; i++) {
		polyVtx[i] = polyVtx[0];
	}

	//右上
	polyVtx[1].pos = VGet(size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[1].u = kTexxtureMaxU;
	polyVtx[1].v = kTexxtureMinV;
	//左下
	polyVtx[2].pos = VGet(-size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[2].u = kTexxtureMinU;
	polyVtx[2].v = kTexxtureMaxV;
	//右下
	polyVtx[3].pos = VGet(size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[3].u = kTexxtureMaxU;
	polyVtx[3].v = kTexxtureMaxV;
	//左下
	polyVtx[4].pos = VGet(-size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[4].u = kTexxtureMinU;
	polyVtx[4].v = kTexxtureMaxV;
	//右上
	polyVtx[5].pos = VGet(size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[5].u = kTexxtureMaxU;
	polyVtx[5].v = kTexxtureMinV;

	//描画の頂点データに登録
	for (auto& vtx : polyVtx) {
		drawVtx.push_back(vtx);
	}

	//回転行列
	MATRIX mtx = MGetRotY(DX_PI_F / 2.0f);
	//側面の頂点データ生成、登録
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

	//最後に位置情報を足す
	for (auto& vtx : drawVtx) {
		vtx.pos = VAdd(vtx.pos, pos);
	}

	DrawPolygon3D(drawVtx.data(), static_cast<int>(drawVtx.size() / 3), texture, true);
}
