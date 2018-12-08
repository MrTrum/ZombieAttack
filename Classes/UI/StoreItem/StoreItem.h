#ifndef _STORE_ITEM_H
#define _STORE_ITEM_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
USING_NS_CC;
class StoreItem : public cocos2d::ui::Layout
{
public:
	StoreItem();
	~StoreItem();
	static StoreItem* create(cocos2d::Size size);
	virtual bool init(cocos2d::Size size);
	cocos2d::ui::Button* _upgradeBtn;
	cocos2d::Sprite* _ItemWeapon;
	void setCallBack(std::function<void(int idItem)> callback);
	void setData(int id, int money);
	
private:
	int _Id;
	int _money;
	std::function<void(int idItem)> _callback;
	cocos2d::Label*	_labelUpgrade;
};


#endif // !_STORE_ITEM_H

