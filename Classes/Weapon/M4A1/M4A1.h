#ifndef _M4A1_H
#define _M4A1_H
#include "UI/GameStats/WeaponStats.h"
#include "cocos2d.h"
class M4A1: public cocos2d::Node
{
public:
	M4A1();
	~M4A1();
	CREATE_FUNC(M4A1);
	virtual bool init();
	void setIcon();
	int _Level;
	WeaponStats _Stats; 
private:

	cocos2d::Sprite* _iconGun;
	
};

#endif // !_M4A1_H
