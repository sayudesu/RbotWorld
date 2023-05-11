#include "EnemyRush.h"
#include "Animation.h"
#include "Vec2.h"

namespace
{
	const char* const kModelName = "Data/Model/Enemy/uploads_files_2381754_Striker.mv1";
	// 初期位置
	constexpr VECTOR kDefaultPos = { 1500.0f,0.0f,0.0f };

	// 動きの速さ
	constexpr float kSpeedIdle = 3.0f;

	constexpr float kRushSpeed = 15.0f;

	// 最大HP
	constexpr int kMaxHp = 100;

	// アニメーションナンバー
	constexpr int kAnimNoView = 0;	// 発見する
	constexpr int kAnimNoDead = 1;	// 死んだ
	constexpr int kAnimNoIdle = 2;	// 待機
	constexpr int kAnimNoRush = 3;	// 走る

}

EnemyRush::EnemyRush(VECTOR pos)/*:
	m_upddateFunc(&EnemyRush::Update)*/
{
	// 3Dモデルの生成
	m_pAnimation = std::make_shared<Animation>(kModelName);// モデルのハンドルを渡す
	m_pAnimation->SetAnimation(kAnimNoRush);// モデルの動きをセット

	m_pos = pos;

	// モデルの向き
	m_angle.y = 90.0f;

	m_size = {};

	m_posPlayer = {};

	m_Hp = kMaxHp;

	m_isDead = false;

}

EnemyRush::~EnemyRush()
{
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
	m_pAnimation->SetPos(m_pos);
	m_pAnimation->Update(m_angle.x, m_angle.y, m_angle.z,1.0f);

	m_pos.x -= kRushSpeed;

	VECTOR size = { 0.2f,0.2f ,0.2f };
	m_pAnimation->SetSize(size);
}

void EnemyRush::Draw()
{
	m_pAnimation->Draw();
	DrawUI();
}

void EnemyRush::Dead()
{

}

void EnemyRush::DrawUI()
{
	if (!m_isDead)
	{
		const VECTOR pos = ConvWorldPosToScreenPos(m_pos);

		m_size.left   = pos.x- 50.0f;
		m_size.top    = pos.y - 130.0f;
		m_size.right  = m_size.left  + 110.0f;
		m_size.bottom = m_size.top   + 130.0f;

		DrawFormatString(m_size.left, m_size.top, 0xffffff, "EnemyRush");
		DrawBox(m_size.left, m_size.top, m_size.right, m_size.bottom, 0xff0000, false);

		//体力を描画
		DrawBox(m_size.left - 1, m_size.top - 1,
			m_size.left + 100 + 1, m_size.top + 1 + 20,
			0x0000ff, true);//外枠
		DrawBox(m_size.left, m_size.top,
			m_size.left + 100 * m_Hp / kMaxHp, m_size.top + 20,
			0x0ffff0, true);//メーター
		//長さ * HP / HPMAX
	}
	else
	{
		m_size.left   = NULL;
		m_size.top    = NULL;
		m_size.right  = NULL;
		m_size.bottom = NULL;
	}

}
