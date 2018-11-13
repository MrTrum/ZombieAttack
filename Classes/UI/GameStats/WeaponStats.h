#ifndef _WEAPON_STATS_H
#define _WEAPON_STATS_H
class WeaponStats
{
public:
	WeaponStats();
	~WeaponStats();
	void setStats(int Damage,int BulletNumber,int Price);
	int _Damage;
	int _BulletNumber;
	int _Price;
};

#endif // !_WEAPON_STATS_H
