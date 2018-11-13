#include "UI/GameStats/WeaponStats.h"
WeaponStats::WeaponStats()
{
	_Damage = 0;
	_BulletNumber = 0;
	_Price = 0;
}

WeaponStats::~WeaponStats()
{
	_Damage = 0;
	_BulletNumber = 0;
	_Price = 0;
}
void WeaponStats::setStats(int Damage, int BulletNumber,int Price)
{
	_Damage = Damage;
	_BulletNumber = BulletNumber;
	_Price = Price;
}