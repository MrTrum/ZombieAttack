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
private:
	cocos2d::Sprite* _Coin;
};


#endif // !_COIN_H
