#include "FieldBase.h"
#include "Util/Model.h"
#include <assert.h>
#include <iostream>

namespace
{
	// ファイル名
	const char* const kFileStageName = "Data/Model/Stage/Field.mv1";

	constexpr float kBlockSideLength = 200.0f;
}

FieldBase::FieldBase():
    m_stageNum(0)
{
    m_data.blockNumX = 0;
    m_data.blockNumY = 0;
    m_data.fileName = " ";
	m_pModel.clear();
}

FieldBase::~FieldBase()
{
}

void FieldBase::Init(LoadData data)
{
	FirstModelLoad();
	LoadFile(data.fileName);
    int orgModel = m_pModel[0]->GetModelHandle();

    ModelLoad(orgModel);
}

void FieldBase::End()
{
}

void FieldBase::Update()
{
    for (auto& field : m_pModel)
    {
        field->Update();
    }
}

void FieldBase::Draw()
{
    for (auto& field : m_pModel)
    {
        field->Draw();
    }
}

void FieldBase::FirstModelLoad()
{
	float x = 200.0f * static_cast<float>(0 % m_data.blockNumX) - m_data.blockNumX / 2;
	float y = 200.0f * static_cast<float>(m_data.blockNumY - (0 / m_data.blockNumX)) - m_data.blockNumX / 2;

	m_pModel.push_back(std::make_shared<Model>(kFileStageName));
	m_pModel.back()->SetPos(VGet(x, -kBlockSideLength / 2, y));
	m_pModel.back()->SetUseCollision(true, true);
}

void FieldBase::LoadFile(const char* fileName)
{
    // csvファイルを読み込んで数字の配列にしたい
    FILE* fp;

    if (fopen_s(&fp, fileName, "rt") != 0)
    {
        std::cout << "ファイル読み込み失敗";
        return;    // 異常終了
    }

    int chr;
    int wNum = -1;    // 未確定
    // 横の要素数数える用
    int tempW = 0;



    int tempNum = 0;
    while (true)
    {
        chr = fgetc(fp);    // 1文字読み込み
        // 区切り文字が見つかった
        if (chr == ',' ||
            chr == '\n' ||
            chr == EOF)
        {
            // dataTblにデータを入れる
            m_blockNum.push_back(tempNum);
            tempNum = 0;

            // ファイルの終端に来たら終了
            if (chr == EOF)
            {
                break;
            }
            else if (chr == ',')
            {
                tempW++;    // 要素数数える
            }
            else   // chr == '\n'
            {
                tempW++;    // 要素数数える
                if (wNum < 0)
                {
                    wNum = tempW;    // 要素数確定
                }
                /*else
                {
                    assert(wNum == tempW);
                }*/
                tempW = 0;
            }
            // まだ終わってないので続けて読み込み
            continue;
        }

        // データは数字のみのはず
        assert(chr >= '0' && chr <= '9');

        // 数字なのは確定
        // 文字列を数値に変換したい
        // 268を読み込む
        // 1文字目は'2'    これを数値に変換していれる
        // 2文字目は'6'    tempNumは2 20 + 6  tempNum = 26
        // 3文字目は'8' tempNumは26 260+ 8 tempNum = 268
        tempNum = (tempNum * 10) + chr - '0';

        // データの区切りが見つかった時点でそこまでがデータのひとまとまり

    }
    // ファイルを閉じる
    fclose(fp);
}

void FieldBase::ModelLoad(int orgModel)
{
    for (int i = 0; i < m_blockNum.size(); i++)
    {
        float x = 200.0f * static_cast<float>(0 % m_data.blockNumX) - m_data.blockNumX / 2;
        float y = 200.0f * static_cast<float>(m_data.blockNumY - (0 / m_data.blockNumX)) - m_data.blockNumX / 2;

        if (m_blockNum[i] == 1)
        {
            m_pModel.push_back(std::make_shared<Model>(orgModel));
            m_pModel.back()->SetPos(VGet(x, -kBlockSideLength / 2, y));
            m_pModel.back()->SetUseCollision(true, true);
            continue;
        }

    }
}
