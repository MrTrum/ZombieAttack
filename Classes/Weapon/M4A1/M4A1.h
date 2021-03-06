#ifndef _M4A1_H
#define _M4A1_H
#include "UI/GameStats/WeaponStats.h"
#include "cocos2d.h"

USING_NS_CC;
class M4A1 : public cocos2d::Node
{
public:
	M4A1();
	~M4A1();
	CREATE_FUNC(M4A1);
	virtual bool init();
	void setIcon(Size panel);
	void setLabelStats(int Level);
	void hide();
	void show();
	int _Level,baseBullet;
	WeaponStats _Stats;
	enum gunType
	{
		M16 = 1,
		ShotGun = 2,
		FireGun = 3
	};
	bool recharge = false;
private:
	Size _panel;
	cocos2d::Sprite* _Gun;
	cocos2d::Sprite* _iconGun;
	cocos2d::Sprite* _Dmg;
	cocos2d::Sprite* _bulletNum;
	cocos2d::Label* _labelDmg;
	cocos2d::Label* _labelNum;
	cocos2d::Sprite* _Price;
	cocos2d::Label* _labelUpgrade;
	cocos2d::Sprite* _buyBullet;
	cocos2d::Label* _labelBuyBullet;
};

#endif // !_M4A1_H
