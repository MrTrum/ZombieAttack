#ifndef _MONEY_H
#define _MONEY_H
#include "cocos2d.h"
class Money : public cocos2d::Node
{
public:
	Money();
	~Money();
	CREATE_FUNC(Money);
	virtual bool init();
	static int _moneyGO;
	void setMoney(int);
	void resetMoney();
private:
	cocos2d::Sprite* _money1;
	cocos2d::Sprite* _money2;
	cocos2d::Sprite* _money3;
	cocos2d::Sprite* _money4;
	cocos2d::Sprite* _money5;
	cocos2d::Sprite* _money6;
	static bool _beginMoney;

};



#endif // !_SCORE_H
