#include "Field.h"
#include "Animation.h"
#include "Field/DrawPoly.h"
namespace
{
	const char* const kModelName = "Data/Model/Stage/uploads_files_770164_Crate_simple.mv1";

	// テクスチャ情報
	const char* const kTextureFilename = "Data/Img/Texture00.png";

	// マップ情報
	constexpr int kMapSizeX = 15;
	constexpr int kMapSizeZ = 5;

	constexpr int kMapData[kMapSizeZ][kMapSizeX] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	// ブロック一つのサイズ
	constexpr float kCubeSize = 100.0f;
}

Field::Field() :
	m_texture(-1)
{
}

Field::~Field()
{
	DeleteGraph(m_texture);
}

void Field::Init()
{
	m_texture = LoadGraph(kTextureFilename);
}

void Field::End()
{

}

void Field::Update()
{
	for (int x = 0; x < kMapSizeX; x++)
	{
		for (int z = 0; z < kMapSizeZ; z++)
		{
			if (kMapData[z][x] == 0) continue;

			Poly::DrawCube(GetChipPos(x, z), kCubeSize, m_texture);
		}
	}
}

void Field::Draw()
{

    // 右に移動用ライン
    const float xMax = 30000.0f;
    const float x = 300.0f;

	// -500~500の範囲にグリッドの表示
	for (float x = -500.0f; x <= xMax; x += 100.0f)
	{
		const VECTOR start = VGet(x, 0.0f, -500.0f);
		const VECTOR end = VGet(x, 0.0f, 500.0f);
		DrawLine3D(start, end, x * 300.0f);
	}
	for (float z = -500.0f; z <= 500.0f; z += 100.0f)
	{
		const VECTOR start = VGet(-500.0f, 0.0f, z);
		const VECTOR end = VGet(500.0f, 0.0f, z);
		DrawLine3D(start, end, 0xffff00);
	}

    // Y座標にDrwaLineを描画
    for (float y = 0.0f; y <= 1000.0f; y += 100.0f)
    {
        const VECTOR start = VGet(-1050.0f, y, x);
        const VECTOR end = VGet(xMax, y, x);
        DrawLine3D(start, end, 0xffff00);
    }
    for (float tY = -950.0f; tY <= xMax; tY += 100.0f)
    {
        const VECTOR start = VGet(tY, 0.0f, x);
        const VECTOR end = VGet(tY, 1500.0f, x);
        DrawLine3D(start, end, 0xffff00);
    }
}

float Field::GetSizeX() const
{
	return kCubeSize * kMapSizeX;
}

float Field::GetSizeY() const
{
	return kCubeSize;
}

float Field::GetSizeZ() const
{
	return kCubeSize * kMapSizeZ;
}

VECTOR Field::GetCenter() const
{
	VECTOR result;
	result.x = GetSizeX() / 2.0f - kCubeSize / 2.0f;
	result.y = 0.0f;
	result.z = GetSizeZ() / 2.0f - kCubeSize / 2.0f;
	
	return result;
}

int Field::GetChipNumX() const
{
	return kMapSizeX;
}

int Field::GetChipNumZ() const
{
	return kMapSizeZ;
}

bool Field::IsBlock(int x, int z) const
{
	if (kMapData[z][x] == 0) return false;
	return true;
}

VECTOR Field::GetChipPos(int x, int z) const
{
	float posX = 100.0f * x;
	float posZ = 100.0f * z;

	//float posX = kCubeSize * x;
	//float posZ = kCubeSize * z;

	VECTOR result = VGet(posX, 0.0f, posZ);
	return result;
}
