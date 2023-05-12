#include "EnemyBase.h"

void EnemyBase::SetDamge(int damage)
{
	m_saveDamage = m_hp;// 体力を保存
	m_hp -= damage;// ダメージ計算
}