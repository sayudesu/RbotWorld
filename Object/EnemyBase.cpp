#include "EnemyBase.h"

void EnemyBase::SetDamage(int damage)
{
	m_saveDamage = m_hp;// �̗͂�ۑ�
	m_hp -= damage;// �_���[�W�v�Z
}