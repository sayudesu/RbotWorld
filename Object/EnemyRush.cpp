#include "EnemyRush.h"
#include "Animation.h"


namespace
{
	const char* const kModelName = "Data/Model/Enemy/uploads_files_2381754_Striker.mv1";
	// 初期位置
	constexpr VECTOR kDefaultPos = { 1500.0f,0.0f,0.0f };

	// 動きの速さ
	constexpr float kSpeedIdle = 3.0f;

	constexpr float kRushSpeed = 15.0f;
	
	constexpr int kDamagePower = 30;

	// アニメーションナンバー
	constexpr int kAnimNoView = 0;	// 発見する
	constexpr int kAnimNoDead = 1;	// 死んだ
	constexpr int kAnimNoIdle = 2;	// 待機
	constexpr int kAnimNoRush = 3;	// 走る

}

EnemyRush::EnemyRush(Vec3 pos)
{
	// 3Dモデルの生成
	m_pAnimation = std::make_shared<Animation>(kModelName);// モデルのハンドルを渡す
	m_pAnimation->SetAnimation(kAnimNoRush,true,true);// モデルの動きをセット

	m_pos = pos;

	// モデルの向き
	m_angle.x = 90.0f;
	m_angle.y = 90.0f;

	m_hitDamage = kDamagePower;

	m_pAnimation->SetUseCollision(true, true);

}

EnemyRush::~EnemyRush()
{
	printfDx("きえました\n");
}

void EnemyRush::Init()
{
	m_pAnimation->Init();
}

void EnemyRush::End()
{
	m_pAnimation->End();
}

void EnemyRush::Update()
{
	m_pAnimation->SetPos(VGet(m_pos.x, m_pos.y, m_pos.z));
	m_pAnimation->Update();//m_angle,1.0f
	
	m_pos.x -= kRushSpeed;

	VECTOR size = { 0.2f,0.2f ,0.2f };
//	m_pAnimation->SetSize(size);

	m_pAnimation->SetSize(VGet(0.3f, 0.3f, 0.3f));
	m_pAnimation->SetRot(VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
}

void EnemyRush::Draw()
{
	m_pAnimation->Draw();
}

int EnemyRush::GetModelHandle()
{
	return m_pAnimation->GetModelHandle();
}

int EnemyRush::GetColFrameIndex() const
{
	return m_pAnimation->GetColFrameIndex();
}