#include "Field.h"
#include "Animation.h"
#include <DxLib.h>

namespace
{

	const bool debug = true;

	// ファイル名
	const char* const kFileStageName = "Data/Model/Stage/Field.mv1";


	// 地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 350;
	constexpr int kBlockNumY = 5;

	constexpr int kBlockNum = kBlockNumX * kBlockNumY;

	// ブロックの一辺の長さ
	constexpr float kBlockSideLength = 100.0f;

	// 地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthY = kBlockSideLength * kBlockNumY;

	// 二次元配列マップデータ
//	constexpr int StageData[kBlockNumY][kBlockNumX] =
//	{
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//	};

	// 一次元配列マップデータ
//	constexpr int StageData1[30] ={ 0,1,0,1,0,1,0,1,0,1 ,1,1,1,1,1,1,1,1,1,1 ,0,1,0,1,0,1,0,1,0,1 };

	// 一次元配列マップデータvector
	std::vector<int> VcStageData = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	// 二次元配列マップデータvecotr
	std::vector<std::vector<int>> mapData =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1},//,, 1, 0, 1,1, 0, 1, 1, 0, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 1},//,, 1, 0, 1,1, 0, 1, 1, 0, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1},//, 1, 0, 1,1, 0, 1, 1, 0, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},//, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1 },
	};
	
}

Field::Field()
{
	//// 新しい行を作成して追加する
	//std::vector<std::shared_ptr<Animation>> row1;
	//row1.push_back(std::make_shared<Animation>(kFileStageName));
	//m_pModel.push_back(row1);

	//// 別の行を作成して追加する
	//std::vector<std::shared_ptr<Animation>> row2;
	//row2.push_back(std::make_shared<Animation>(kFileStageName));
	//m_pModel.push_back(row2);

	//int orgModel = m_pModel[0][0]->GetModelHandle();
	//for (int y = 0; y < mapData.size() - 1; y++)
	//{
	//	for (int x = 0; x < mapData.at(y).size() - 1; x++)
	//	{
	//		m_pModel[y][x] = std::make_shared<Animation>(orgModel);  // 要素にAnimationオブジェクトを設定
	//		m_pModel[y][x]->SetUseCollision(true, true);
	//	}
	//}
	
	// 3Dモデルをロード
	m_pModel.push_back(std::make_shared<Animation>(kFileStageName));
	int orgModel = m_pModel[0]->GetModelHandle();
	// 最初にロードしたモデルと合わせてモデルを必要分生成
	for (int i = 0; i < kBlockNum - 1; i++)
	{
		m_pModel.push_back(std::make_shared<Animation>(orgModel));
		m_pModel[i]->SetUseCollision(true, true);
	}

	// 地面に並べる
	for (int i = 0; i < m_pModel.size(); i++)
	{
		//float x = 200.0f * (i % kBlockNumX) - kFieldSideLengthX / 2 + kBlockSideLength / 2;
	
		//m_pModel[i]->SetPos(VGet(
		//	x,
		//	-kBlockSideLength,//上面がy=0.0fになるように配置
		//	0.0f));
	}

	//printfDx("Y = %d\n", mapData.size());
	//printfDx("X = %d\n", mapData.at(0).size());


#if debug
			// vectorの二次元配列をfor文で回す
	for (int y = 0; y < mapData.size(); y++)
	{
		for (int x = 0; x < mapData.at(y).size(); x++)
		{
			// データの中に1があったら
			if (mapData[y][x] == 1)
			{
				float sizeX = 200.0f * x;
				float sizeY = 200.0f * y;

				// モデルクラスの中にxyzの座標を返す
				m_pModel[y][x]->SetPos(VGet(
					sizeX,
					-kBlockSideLength + sizeY,
					0.0f));
			}
		}
#else
	for (int i = 0; i < VcStageData.size(); i++)
	{
		if (VcStageData[i] == 1)
		{
			float x = 200.0f * i;

			m_pModel[i]->SetPos(VGet(
				x,
				-kBlockSideLength,
				0.0f));
		}
	}

	//  700
	//  500
	//  300
	//  100
	// -100
#endif
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
#if debug	
	for (const auto& row : m_pModel)
	{
		for (const auto& element : row) 
		{
			element->Update();
		}
	}
#else
	for (auto& model : m_pModel)
	{
		model->Update();
	}
#endif
}

void Field::Draw()
{
#if debug	
	for (const auto& row : m_pModel)
	{
		for (const auto& element : row)
		{
			element->Draw();
		}
	}
#else
	for (auto& model : m_pModel)
	{
		model->Draw();
	}
#endif
#if _DEBUG	
	// 右に移動用ライン
	const float xMax = 30000.0f;
	const float yMax = 1200.0f;
	const float x = 300.0f;

	const float chipSize = 150.0f;

	// -500~500の範囲にグリッドの表示
	for (float x = -500.0f; x <= xMax; x += chipSize)
	{
		const VECTOR start = VGet(x, 0.0f, -500.0f);
		const VECTOR end = VGet(x, 0.0f, 500.0f);
		DrawLine3D(start, end, x * 300.0f);
	}
	for (float z = -500.0f; z <= 500.0f; z += chipSize)
	{
		const VECTOR start = VGet(-500.0f, 0.0f, z);
		const VECTOR end = VGet(500.0f, 0.0f, z);
		DrawLine3D(start, end, 0xffff00);
	}

	// Y座標にDrwaLineを描画
	for (float y = 0.0f; y <= yMax; y += chipSize)
	{
		const VECTOR start = VGet(-1050.0f, y, x);
		const VECTOR end = VGet(xMax, y, x);
		DrawLine3D(start, end, 0xffff00);
	}
	for (float tY = -1000.0f; tY <= xMax; tY += chipSize)
	{
		const VECTOR start = VGet(tY, 0.0f, x);
		const VECTOR end = VGet(tY, 1500.0f, x);
		DrawLine3D(start, end, 0xffff00);
	}
#endif
}

// モデルの数
int Field::GetModelNumX()
{
#if debug
	return mapData.at(0).size();
#else
	return kBlockNum;
#endif
}

int Field::GetModelNumY()
{
#if debug	
	return mapData.size();
#else
	return 0;
#endif
}
#if debug
// 指定した番号のモデルのハンドルを取得する
int Field::GetModelHandle(int handlNum,int handlNumX)
{
	return m_pModel[handlNum][handlNumX]->GetModelHandle();
}
#else
// 指定した番号のモデルのハンドルを取得する
int Field::GetModelHandle(int handlNum)
{
	return m_pModel[handlNum]->GetModelHandle();
}
#endif
int Field::GetColFrameIndex()const
{
#if debug
	for (const auto& row : m_pModel)
	{
		for (const auto& element : row)
		{
			return element->GetColFrameIndex();
}
	}

#else
	for (auto& model : m_pModel)
	{
		return model->GetColFrameIndex();
}
#endif
}
