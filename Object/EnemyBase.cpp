#include "EnemyBase.h"

void EnemyBase::SetDamage(bool damage)
{
	//m_saveDamage = m_hp;// 体力を保存
	//m_hp -= damage;// ダメージ計算
	if (damage)m_hp = 0;
}