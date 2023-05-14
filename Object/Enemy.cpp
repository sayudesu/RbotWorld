#include "Enemy.h"
#include "Animation.h"
#include "Vec2.h"

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
	m_pAnimation->SetAnimation(0);// モデルの動きをセット

	m_size = {};

	m_posPlayer = {};

	m_hp = kMaxHp;
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
	m_pAnimation->SetPos(m_pos);
	m_pAnimation->Update(m_angle.x, m_angle.y, m_angle.z,1.0f);

	//m_angle.y++;
//	m_angle.x = GetRand(1000.0f);
	if (m_hp < 0)// 死んだら
	{
		if (m_pos.y > 100.0f)// 地面に落ちる
		{
			m_pos.y -= kSpeedIdle * 0.02f;
		}
		if (m_angle.x < 90.0f * DX_PI_F / 180.0f)// 角度を変える
		{
			m_angle.x += 0.1f;
		}
		m_isDead = true;
	}
	else
	{
		m_angle.x = 0.0f;

		// 上下運動
		if (m_isStep)
		{
			if (m_pos.y > 150.0f) m_isStep = false;
			m_pos.y += kSpeedIdle;
		}
		else
		{
			if (m_pos.y < 50.0f)   m_isStep = true;
			m_pos.y -= kSpeedIdle * 0.5f;
		}
	}

	if (!m_isDead)
	{
		Vec2 toPlayer{ 0,0 };
		toPlayer.x = m_posPlayer.left - m_size.left;
		toPlayer.y = m_posPlayer.top  - m_size.top;

		int circle = 100;

		DrawCircle(m_size.left + 70.0f, m_size.top + 50.0f, circle, 0xffffff, false);

		if (toPlayer.length() < circle)
		{
			toPlayer = toPlayer.normalize();

			const float speed = 10.0f;

			if (m_size.left + 70.0f > m_posPlayer.left)
			{
				m_pos.x -= speed;
			//	m_angle.y = 0.0f;
			}
			else
			{
				m_pos.x += speed;
			//	m_angle.y = 180.0f;
			}
		}
	}
}

void Enemy::Draw()
{
	m_pAnimation->Draw();
	DrawUI();
}

void Enemy::Dead()
{
}

void Enemy::DrawUI()
{
	if (!m_isDead)
	{
		const VECTOR pos = ConvWorldPosToScreenPos(m_pos);

		m_size.left   = pos.x - 240.0f;
		m_size.top    = pos.y - 150.0f;
		m_size.right  = m_size.left  + 140.0f;
		m_size.bottom = m_size.top   + 130.0f;

		DrawFormatString(m_size.left, m_size.top, 0xffffff, "Enemy");
		DrawBox(m_size.left, m_size.top, m_size.right, m_size.bottom, 0xff0000, false);

		//体力を描画
		DrawBox(m_size.left - 1, m_size.top - 1,
			m_size.left + 100 + 1, m_size.top + 1 + 20,
			0x0000ff, true);//外枠
		DrawBox(m_size.left, m_size.top,
			m_size.left + 100 * m_hp / kMaxHp, m_size.top + 20,
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
