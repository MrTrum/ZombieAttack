#ifndef _STORE_LAYER_H
#define _STORE_LAYER_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "UI/NumberMoney/Money.h"
class GamePlayLayer;
USING_NS_CC;
class StoreLayer : public cocos2d::Node
{
public:
	StoreLayer();
	~StoreLayer();
	CREATE_FUNC(StoreLayer);
	virtual bool init();
	void TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void setGamePlayLayerPtr(GamePlayLayer* ptr);
	void setTotalMoney(int _GameTotalMoney);
private:
	int _shopTotalMoney;
	cocos2d::ui::Button* _quitShop;
	GamePlayLayer* _btnGamePlayLayer;
	Money* _Money;
};


#endif