#include "Field.h"
#include "Animation.h"

namespace
{
	const char* const kModelName = "Data/Model/Stage/uploads_files_770164_Crate_simple.mv1";
}

Field::Field() 
{
	//for (auto& num : m_pAnimation)
	//{
	//	num = std::make_shared<Animation>(kModelName, m_boxPos);
	//}
}

Field::~Field()
{
}

void Field::Init()
{
    // ２ポリゴン分の頂点のデータをセット
    m_vertex[0].pos = VGet(100.0f, 100.0f, 0.0f);
    m_vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
    m_vertex[0].dif = GetColorU8(255, 255, 255, 255);
    m_vertex[0].spc = GetColorU8(0, 0, 0, 0);
    m_vertex[0].u = 0.0f;
    m_vertex[0].v = 0.0f;
    m_vertex[0].su = 0.0f;
    m_vertex[0].sv = 0.0f;

    m_vertex[1].pos = VGet(250.0f, 100.0f, 0.0f);
    m_vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
    m_vertex[1].dif = GetColorU8(255, 0, 255, 255);
    m_vertex[1].spc = GetColorU8(0, 0, 0, 0);
    m_vertex[1].u = 0.0f;
    m_vertex[1].v = 0.0f;
    m_vertex[1].su = 0.0f;
    m_vertex[1].sv = 0.0f;

    m_vertex[2].pos = VGet(100.0f, 300.0f, 0.0f);
    m_vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
    m_vertex[2].dif = GetColorU8(0, 255, 255, 255);
    m_vertex[2].spc = GetColorU8(0, 0, 0, 0);
    m_vertex[2].u = 0.0f;
    m_vertex[2].v = 0.0f;
    m_vertex[2].su = 0.0f;
    m_vertex[2].sv = 0.0f;


    m_vertex[3].pos = VGet(400.0f, 200.0f, 0.0f);
    m_vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
    m_vertex[3].dif = GetColorU8(0, 255, 255, 255);
    m_vertex[3].spc = GetColorU8(0, 0, 0, 0);
    m_vertex[3].u = 0.0f;
    m_vertex[3].v = 0.0f;
    m_vertex[3].su = 0.0f;
    m_vertex[3].sv = 0.0f;

    m_vertex[4].pos = VGet(600.0f, 400.0f, 0.0f);
    m_vertex[4].norm = VGet(0.0f, 0.0f, -1.0f);
    m_vertex[4].dif = GetColorU8(0, 0, 255, 255);
    m_vertex[4].spc = GetColorU8(0, 0, 0, 0);
    m_vertex[4].u = 0.0f;
    m_vertex[4].v = 0.0f;
    m_vertex[4].su = 0.0f;
    m_vertex[4].sv = 0.0f;

    m_vertex[5].pos = VGet(500.0f, 50.0f, 0.0f);
    m_vertex[5].norm = VGet(0.0f, 0.0f, -1.0f);
    m_vertex[5].dif = GetColorU8(255, 0, 255, 255);
    m_vertex[5].spc = GetColorU8(0, 0, 0, 0);
    m_vertex[5].u = 0.0f;
    m_vertex[5].v = 0.0f;
    m_vertex[5].su = 0.0f;
    m_vertex[5].sv = 0.0f;
}

void Field::End()
{

}

void Field::Update()
{

}

void Field::Draw()
{
	// 3D空間の描画終了
	//// x座標を増加させる
	//for (int i = 0; i < 4; i++)
	//{
	//	m_vertex[i].x += 1.0f; // 1.0fを増やす値に変更することで増加幅を調整できます
	//}

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

    // ２ポリゴンの描画
 //   DrawPolygon3D(m_vertex, 2, DX_NONE_GRAPH, FALSE);
}
