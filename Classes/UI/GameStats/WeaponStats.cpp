#include "UI/GameStats/WeaponStats.h"
WeaponStats::WeaponStats()
{
	_Damage = 0;
	_BulletNumber = 0;
}

WeaponStats::~WeaponStats()
{
	_Damage = 0;
	_BulletNumber = 0;
}
void WeaponStats::setStats(int Damage, int BulletNumber)
{
	_Damage = Damage;
	_BulletNumber = BulletNumber;
}