#include "FieldOne.h"
namespace
{
	// �t�@�C���l�[��
	const char* kFileName = "Data/MapChip.csv";

	// �u���b�N�̕�����
	constexpr int kFieldBlockNumX = 151;
	constexpr int kFieldBlockNumY = 7;
	// �u���b�N�̐�
	constexpr int kFieldBlockNum = kFieldBlockNumX * kFieldBlockNumY;

}
FieldOne::FieldOne()
{
	m_stageNum = 1;
	m_data.fileName = kFileName;
	m_data.blockNumX = kFieldBlockNumX;
	m_data.blockNumY = kFieldBlockNumY;

	FieldBase::Init(m_data);
}

FieldOne::~FieldOne()
{
}
