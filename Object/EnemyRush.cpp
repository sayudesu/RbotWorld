#include "EnemyRush.h"
#include "Model.h"


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
	m_pModel = std::make_shared<Model>(kModelName);// モデルのハンドルを渡す
	m_pModel->SetAnimation(kAnimNoRush,true,true);// モデルの動きをセット

	m_pos = pos;

	// モデルの向き
	m_angle.x = 90.0f;
	m_angle.y = 90.0f;

	m_hitDamage = kDamagePower;

	m_pModel->SetUseCollision(true, true);

}

EnemyRush::~EnemyRush()
{
	printfDx("きえました\n");
}

void EnemyRush::Init()
{
	m_pModel->Init();
}

void EnemyRush::End()
{
	m_pModel->End();
}

void EnemyRush::Update()
{
	m_pModel->SetPos(VGet(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Update();//m_angle,1.0f
	
	m_pos.x -= kRushSpeed;

	VECTOR size = { 0.2f,0.2f ,0.2f };
//	m_pAnimation->SetSize(size);

	m_pModel->SetSize(VGet(0.3f, 0.3f, 0.3f));
	m_pModel->SetRot(VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
}

void EnemyRush::Draw()
{
	m_pModel->Draw();
}

int EnemyRush::GetModelHandle()
{
	return m_pModel->GetModelHandle();
}

int EnemyRush::GetColFrameIndex() const
{
	return m_pModel->GetColFrameIndex();
}