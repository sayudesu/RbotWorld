#include "Field.h"
#include "Animation.h"

namespace
{
	const char* const kModelName = "Data/Model/Stage/uploads_files_770164_Crate_simple.mv1";
}

Field::Field() :
	m_hBox(-1),
	m_boxPos(VGet(0.0f, 0.0f, 0.0f))
{
	// 3Dモデルの生成
	m_pAnimation.push_back(std::make_shared<Animation>(kModelName, m_boxPos));
	for (auto& num : m_pAnimation)
	{
		num = std::make_shared<Animation>(kModelName, m_boxPos);
	}
}

Field::~Field()
{
}

void Field::Init()
{
	for (auto& num : m_pAnimation)
	{
		num->Init();
	}
}

void Field::End()
{
	for (auto& num : m_pAnimation)
	{
		num->End();
	}
}

void Field::Update()
{

	count++;
	// 敵を複製
	if (count > 1)
	{
		count = 0;
		m_pAnimation.push_back(std::make_shared<Animation>(kModelName, m_boxPos));

	}

	for (auto& num : m_pAnimation)
	{
	//	m_boxPos.x += 1.0f;
	}
}

void Field::Draw()
{
	for (auto& num : m_pAnimation)
	{
		num->Draw();
	}

	//-500~500の範囲にグリッドの表示
	for (float x = -500.0f; x <= 500000.0f; x += 100.0f)
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
}
