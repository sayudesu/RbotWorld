#include "Shadow.h"
#include <DxLib.h>
#include <array>
#include "game.h"
#include <cassert>
using namespace std;

namespace
{
	const char* const kPixelShaderPass = "PixelShader.pso";
}

Shadow::Shadow(const char* fileName, const char* fileName_n)
{
	// 画像読み込み
	m_handle = LoadGraph(fileName);
	assert(m_handle != -1);
	m_handle2 = LoadGraph(fileName_n);
	assert(m_handle2 != -1);

	// シェーダーロード
	m_psH = LoadPixelShader(kPixelShaderPass);
	assert(m_psH != -1);

}

void Shadow::Update()
{
	float speed = 30.0f;
	if (DxLib::CheckHitKey(KEY_INPUT_LEFT))
	{
		m_x -= speed;
	}
	if (DxLib::CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_x += speed;
	}
	if (DxLib::CheckHitKey(KEY_INPUT_UP))
	{
		m_y -= speed;
	}
	if (DxLib::CheckHitKey(KEY_INPUT_DOWN))
	{
		m_y += speed;
	}
}

void Shadow::Draw()
{
	DrawGraphWithShader(m_x, m_y, m_handle, m_handle2, m_psH, true);
#if false
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawGraph(x, y, handle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#endif
}

/// <summary>
/// DxLib::DrawGraphの代わり
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="texH"></param>
/// <param name="normH"></param>
/// <param name="psH"></param>
/// <param name="transFlg"></param>
void Shadow::DrawGraphWithShader(int x, int y, int texH, int normH, int psH, int transFlg)
{
	int w = 0, h = 0;
	GetGraphSize(texH, &w, &h);
	array<VERTEX2DSHADER, 4> verts;
	// 頂点をZの字になるように
	// 左上
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	verts[0].u = 0.0f;
	verts[0].v = 0.0f;
	// 右上
	verts[1].pos.x = x + w;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	verts[1].v = 0.0f;
	// 左下
	verts[2].pos.x = x;
	verts[2].pos.y = y + h;
	verts[2].u = 0.0f;
	verts[2].v = 1.0f;
	// 左下
	verts[3].pos.x = x + w;
	verts[3].pos.y = y + h;
	verts[3].u = 1.0f;
	verts[3].v = 1.0f;

	for (auto& v : verts)
	{
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(255, 255, 255, 255);
		v.pos.z = 0.5f;
		v.rhw = 1.0f;
		v.su = 0.0f;
		v.sv = 0.0f;
	}
	// どのシェーダを使うのか？
	SetUsePixelShader(psH);
	// どのテクスチャを何番に割り当てるのか？
	SetUseTextureToShader(0, texH);
	SetUseTextureToShader(1, normH);

	if (transFlg)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	DrawPrimitive2DToShader(verts.data(), verts.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}
