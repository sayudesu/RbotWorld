#include "Field.h"
#include "Animation.h"
#include <DxLib.h>



Field::Field()
{
	// 3Dモデルをロード
	m_pModel.push_back(std::make_shared<Animation>(kFileStageName));
	
	// 最初にロードしたモデルと合わせてモデルを100個生成
	int orgModel = m_pModel[0]->GetModelHandle();
	for (int i = 0; i < kBlockNum - 1; i++)
	{
		m_pModel.push_back(std::make_shared<Animation>(orgModel));
		m_pModel[i]->SetUseCollision(true, true);
	}

	// 地面に並べる
	for (int i = 0; i < m_pModel.size(); i++)
	{
		float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
		float z = 200.0f * (i / kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
		m_pModel[i]->SetPos(VGet(x,
								 -kBlockSideLength / 2.0f - 50.0f,//上面がy=0.0fになるように配置
								 z + 2000.0f));
	}
}

Field::~Field()
{

}

void Field::Init()
{
}

void Field::End()
{
}

void Field::Update()
{
}

void Field::Draw()
{
	for (auto& model : m_pModel)
	{
		model->Draw();
	}
#if _DEBUG	
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
#endif
}

int Field::GetModelHandle() const
{
	return m_pModel.size();
}

int Field::GetColFrameIndex()const
{
	for (auto& model : m_pModel)
	{
		return model->GetColFrameIndex();
	}
}
