#ifndef _M4A1_H
#define _M4A1_H
#include "UI/GameStats/WeaponStats.h"
#include "cocos2d.h"
class M4A1 : public cocos2d::Node
{
public:
	M4A1();
	~M4A1();
	CREATE_FUNC(M4A1);
	virtual bool init();
	void setIcon();
	void setLabelStats();
	int _Level;
	WeaponStats _Stats;
	enum gunType
	{
		M16 = 1,
		ShotGun = 2,
		FireGun = 3
	};
private:
	cocos2d::Sprite* _Gun;
	cocos2d::Sprite* _iconGun;
	cocos2d::Sprite* _Dmg;
	cocos2d::Sprite* _bulletNum;
	cocos2d::Label* _labelDmg;
	cocos2d::Label* _labelNum;
};

#endif // !_M4A1_H
