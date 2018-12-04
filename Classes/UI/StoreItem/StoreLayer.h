#ifndef _STORE_LAYER_H
#define _STORE_LAYER_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "UI/NumberMoney/Money.h"
#include "Weapon/M4A1/M4A1.h"
#include "Item/HP/HP.h"
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
	void TouchWeaponButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void TouchUpgradeWeaponButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void TouchItemButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void setGamePlayLayerPtr(GamePlayLayer* ptr);
	void setTotalMoney(int _GameTotalMoney);
	void setUpgradeItemIcon(Vector<Sprite>* listSprite);
	void setCallBack(std::function<void(M4A1* Gun)> callback);
	void setCallBackHP(std::function<void(HP* HP)> callbackHP);
	int _chon;
private:
	int _shopTotalMoney;
	cocos2d::ui::Button* _quitShop;
	cocos2d::ui::Button* _upgradeBtn;
	cocos2d::ui::Button* _weaponBtn;
	cocos2d::ui::Button*_upgradeItemBtn;
	cocos2d::ui::Button* _itemBtn;
	cocos2d::Sprite* _Price;
	cocos2d::Label* _labelUpgrade;
	cocos2d::Label* _labelUpgradeItem;
	Vector<cocos2d::Sprite*> listSpriteItem;
	Vector<cocos2d::ui::Button*>listButtonItem;
	GamePlayLayer* _btnGamePlayLayer;
	M4A1* _iconGun;
	HP* _iconHP;
	Money* _Money; 
	UserDefault* def;
	
	std::function<void(M4A1* Gun)> _callback;
	std::function<void(HP* HP)> _callbackHP;
};


#endif