#include "Enemy.h"
#include "Animation.h"
#include "Vec3.h"

namespace
{
	const char* const kModelName = "Data/Model/Enemy/uploads_files_63893_R12.mv1";
	// 初期位置
	constexpr VECTOR kDefaultPos = { 1500.0f,0.0f,0.0f };

	// 動きの速さ
	constexpr float kSpeedIdle = 3.0f;

	// 最大HP
	constexpr int kMaxHp = 100;

}

Enemy::Enemy() :
	m_upddateFunc(&Enemy::Update)
{
	// 3Dモデルの生成
	m_pAnimation = std::make_shared<Animation>(kModelName);// モデルのハンドルを渡す
	m_pAnimation->SetAnimation(0,true,true);// モデルの動きをセット
}

Enemy::~Enemy()
{
	
}

void Enemy::Init()
{
	m_pAnimation->Init();
}

void Enemy::End()
{
	m_pAnimation->End();
}

void Enemy::Update()
{
	m_pAnimation->SetPos(VGet(m_pos.x, m_pos.y, m_pos.z));
	m_pAnimation->Update();
}

void Enemy::Draw()
{
	m_pAnimation->Draw();
}
