#ifndef _HP_H
#define _HP_H
#include "UI/GameStats/ItemStats.h"
#include "cocos2d.h"

USING_NS_CC;
class HP : public cocos2d::Node
{
public:
	HP();
	~HP();
	void setIcon(Size panel);
	void setLabelStats();
	void setItemIcon();
	void iconUpgradeHide(int number,int price);
	void iconUpgradeShow();
	void iconItemShow();
	void iconItemHide();
	void setLevel();
	void getLevel();
	int Level;
	ItemStats itemStat;
	void hide();
	void show();
	bool recharge = false;
private:
	Size	_panel;
	cocos2d::Sprite* _HP;
	cocos2d::Sprite* _iconHP;
	cocos2d::Sprite* _basicStat;
	cocos2d::Sprite* _itemNum;
	cocos2d::Label* _labelStat;
	cocos2d::Label* _labelNum;
	cocos2d::Sprite* _Price;
	cocos2d::Label* _labelUpgrade;
	cocos2d::Sprite* _iconBuyHP;
	cocos2d::Label* _labelBuyHP;
};
#endif // !_HP_H

