#include "EnemyBase.h"

void EnemyBase::SetDamage(bool damage)
{
	//m_saveDamage = m_hp;// �̗͂�ۑ�
	//m_hp -= damage;// �_���[�W�v�Z
	if (damage)m_hp = 0;
}