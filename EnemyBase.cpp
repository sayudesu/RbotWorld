#include "EnemyBase.h"

void EnemyBase::SetDamge(int damage)
{
	m_saveDamage = m_Hp;// 体力を保存
	m_Hp -= damage;// ダメージ計算
}