#include "EnemyBase.h"

void EnemyBase::SetDamge(int damage)
{
	m_saveDamage = m_Hp;// �̗͂�ۑ�
	m_Hp -= damage;// �_���[�W�v�Z
}