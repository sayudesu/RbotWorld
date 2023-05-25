// 2023 Takeru Yui All Rights Reserved.
#include<vector>
#include "Map.h"
#include "DxLib.h"
#include "WorldSprite.h"
#include <vector>


const float Map::ChipSize = 200.0f;
const int Map::ChipPixelSize = 32;

namespace
{
	//const int mapData[10][10] =
	//{
	//	{1,1,1,1,1,1,1,1,1,1},
	//	{1,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,1},
	//	{1,2,2,2,2,2,0,0,0,1},
	//	{1,0,0,0,0,2,0,0,0,1},
	//	{1,0,0,0,0,2,0,0,0,1},
	//	{1,0,0,0,0,2,0,0,0,1},
	//	{1,0,0,0,0,2,0,0,0,1},
	//	{1,1,1,1,1,1,1,1,1,1},
	//};



	const std::vector<std::vector<int>>kMapData =
	{
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
	};
}

/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
	: sprite(nullptr)
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	if (sprite != nullptr)
	{
		delete sprite;
	}
}

/// <summary>
/// ロード
/// </summary>
void Map::Load()
{
	// とりあえずマップロード
	handle = LoadGraph("Data/Img/map.png");
	printfDx("%d\n", handle);
	// WorldSprite実体設定と位置初期化
	sprite = new WorldSprite();

	// どこの画像を表示させるか
	sprite->Initialize(handle, ChipPixelSize, 65);
	VECTOR chipHalfOffset = VGet(-Map::ChipSize * 0.5f, -Map::ChipSize * 0.5f, 0);					// マップチップの半分サイズ左下にずらすオフセット
	VECTOR chipPos = VAdd(VGet(0, 0, 0), chipHalfOffset);	// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
	// 描画位置
	sprite->SetTransform(VGet(chipPos.x, chipPos.y, chipPos.z), Map::ChipSize);
}

/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
	// 処理なし
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	// ゆくゆくはカメラを持ってきて、カメラ範囲以外表示しないように
	for (int y = 0; y < kMapData.size(); y++)
	{
		for (int x = 0; x < kMapData.at(y).size(); x++)
		{
			if (kMapData[y][x] == 1)
			{
				sprite->Initialize(handle, ChipPixelSize, 65);

				// 画像位置を指定
				sprite->SetTransform(VGet(
					x *Map::ChipSize + Map::ChipSize / 2 ,
					y * (kMapData.size() - 1) - Map::ChipSize + Map::ChipSize / 2,
					100.0f)
					, Map::ChipSize
				);

				// 画像描画
				sprite->Draw();

				VECTOR ScreenPos = ConvWorldPosToScreenPos(VGet(x * Map::ChipSize + (Map::ChipSize / 2),
					y * Map::ChipSize + (Map::ChipSize / 2),
					100.0f));

					 DrawFormatString(ScreenPos.x,
									  ScreenPos.y,
									  0xffffff,
									  "%d", x);
					 DrawFormatString(ScreenPos.x,
									  ScreenPos.y,
									  0xffffff,
									  "%d", y);

					 DrawBox(ScreenPos.x, ScreenPos.y, ScreenPos.x, ScreenPos.y, 0xff0000, true);
			}
		}
	}
}

