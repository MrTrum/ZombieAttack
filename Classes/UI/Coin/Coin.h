#ifndef _COIN_H
#define _COIN_H
#include "cocos2d.h"
class Coin : public cocos2d::Node
{
public:
	Coin();
	~Coin();
	virtual bool init();
	CREATE_FUNC(Coin);
	void PlayAnimation();
	bool FlyAnimation(cocos2d::Vec2 iconPos);
	void update(float dt);
private:
	cocos2d::Sprite* _Coin;
	int _coinVal=1;
	int static _totalVal;
};


#endif // !_COIN_H
