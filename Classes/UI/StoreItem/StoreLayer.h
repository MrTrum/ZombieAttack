#ifndef _STORE_LAYER_H
#define _STORE_LAYER_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "UI/NumberMoney/Money.h"
#include "Weapon/M4A1/M4A1.h"
USING_NS_CC;

class GamePlayLayer;

class StoreLayer : public cocos2d::Node
{
public:
	StoreLayer();
	~StoreLayer();
	CREATE_FUNC(StoreLayer);
	virtual bool init();
	void TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void TouchUpgradeButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void setGamePlayLayerPtr(GamePlayLayer* ptr);
	void setTotalMoney(int _GameTotalMoney);
	void setCallBack(std::function<void(M4A1* Gun)> callback);
private:
	int _shopTotalMoney;
	cocos2d::ui::Button* _quitShop;
	cocos2d::ui::Button* _upgradeBtn;
	cocos2d::ui::Button* _weaponBtn;
	cocos2d::ui::Button* _itemBtn;
	cocos2d::Label* _labelUpgrade;
	GamePlayLayer* _btnGamePlayLayer;
	M4A1* _iconGun;
	Money* _Money; 
	UserDefault* def;
	std::function<void(M4A1* Gun)> _callback;
};


#endif