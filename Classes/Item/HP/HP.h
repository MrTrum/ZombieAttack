#ifndef _HP_H
#define _HP_H
#include "UI/GameStats/ItemStats.h"
#include "cocos2d.h"
class HP : public cocos2d::Node
{
public:
	HP();
	~HP();
	void setIcon();
	void setLabelStats();
	int Level;
	ItemStats itemStat;
	void hide();
	void show();
private:
	cocos2d::Sprite* _HP;
	cocos2d::Sprite* _iconHP;
	cocos2d::Sprite* _basicStat;
	cocos2d::Sprite* _itemNum;
	cocos2d::Label* _labelStat;
	cocos2d::Label* _labelNum;
};
#endif // !_HP_H

