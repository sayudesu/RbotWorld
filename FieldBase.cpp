#include "FieldBase.h"
#include "Util/Model.h"
#include <assert.h>
#include <iostream>

namespace
{
	// �t�@�C����
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
    // csv�t�@�C����ǂݍ���Ő����̔z��ɂ�����
    FILE* fp;

    if (fopen_s(&fp, fileName, "rt") != 0)
    {
        std::cout << "�t�@�C���ǂݍ��ݎ��s";
        return;    // �ُ�I��
    }

    int chr;
    int wNum = -1;    // ���m��
    // ���̗v�f��������p
    int tempW = 0;



    int tempNum = 0;
    while (true)
    {
        chr = fgetc(fp);    // 1�����ǂݍ���
        // ��؂蕶������������
        if (chr == ',' ||
            chr == '\n' ||
            chr == EOF)
        {
            // dataTbl�Ƀf�[�^������
            m_blockNum.push_back(tempNum);
            tempNum = 0;

            // �t�@�C���̏I�[�ɗ�����I��
            if (chr == EOF)
            {
                break;
            }
            else if (chr == ',')
            {
                tempW++;    // �v�f��������
            }
            else   // chr == '\n'
            {
                tempW++;    // �v�f��������
                if (wNum < 0)
                {
                    wNum = tempW;    // �v�f���m��
                }
                /*else
                {
                    assert(wNum == tempW);
                }*/
                tempW = 0;
            }
            // �܂��I����ĂȂ��̂ő����ēǂݍ���
            continue;
        }

        // �f�[�^�͐����݂̂̂͂�
        assert(chr >= '0' && chr <= '9');

        // �����Ȃ̂͊m��
        // ������𐔒l�ɕϊ�������
        // 268��ǂݍ���
        // 1�����ڂ�'2'    ����𐔒l�ɕϊ����Ă����
        // 2�����ڂ�'6'    tempNum��2 20 + 6  tempNum = 26
        // 3�����ڂ�'8' tempNum��26 260+ 8 tempNum = 268
        tempNum = (tempNum * 10) + chr - '0';

        // �f�[�^�̋�؂肪�����������_�ł����܂ł��f�[�^�̂ЂƂ܂Ƃ܂�

    }
    // �t�@�C�������
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
