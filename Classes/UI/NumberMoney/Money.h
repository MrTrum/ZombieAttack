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
	void setShopMoneyPos();
	void moneyChange(cocos2d::Vector<int> listMoney,int money);
private:
	cocos2d::Sprite* _money;
	static bool _beginMoney;
	cocos2d::Vector<cocos2d::Sprite*> _listSprite;

};



#endif // !_SCORE_H
