#ifndef _STORE_H_
#define _SOTRE_H_

#include "cocos2d.h"
#include "ui/UIButton.h"

USING_NS_CC;

class MyStore : public cocos2d::Node
{
public:
	MyStore();
	~MyStore();
	bool init();
	CREATE_FUNC(MyStore);
	void onTouchUpGunBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void onTouchUpHealthBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void onTouchUpArmorBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void onTouchCloseBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void update(float dt);
	void gunShop();
	void healthShop();
	void armorShop();
private:
	Size		_sprShopSize;
	Size		shopSize;
	Size		paperSize;
	int			getEnum;
	float		scale;
	ui::Button	*_closeBtn;
	ui::Button	*_selectGun;
	ui::Button	*_selectHealth;
	ui::Button	*_selectArmor;
	ui::Button	*_upgradeGun;
	ui::Button	*_upgradeHealth;
	ui::Button	*_upgradeArmor;
	Sprite		*_sprShop;
	Sprite		*_sprUpLayer;
	bool		_isBtnOpen;
	RotateBy	*rotate;
};

#endif // !_STORE_H_

