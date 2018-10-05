#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"

class Hero : public cocos2d::Node
{
public:
	Hero();
	~Hero();
	CREATE_FUNC(Hero);
	virtual bool init();
	void shootAnimation();

private:
	cocos2d::Sprite	 *_sprhero;
};

#endif // !_HERO_H_

