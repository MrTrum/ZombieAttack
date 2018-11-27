#include "UI/StoreItem/StoreLayer.h"
#include "GamePlayLayer.h"
#include "Parameter.h"
#include "math.h"

#define ITEM_WIDTH_POSITION 0.05f
#define ITEM_HEIGHT_POSITION 0.25f
#define ITEM_DISTANCT_POSITION 0.32f
#define UPGRADEBTN_WIDTH_POSITION 0.185f
#define UPGRADEBTN_HEIGHT_POSITION 0.25f
#define UPGRADEBTN_DISTANCT_POSITION 0.32f
#define PRICE_WIDTH_POSITION 0.11f
#define PRICE_HEIGHT_POSITION 0.25f
#define PRICE_LABEL_WIDTH_POSITION 0.18f
#define PRICE_LABEL_HEIGHT_POSITION 0.25f
#define PRICE_DISTANCT_POSITION 0.32f

StoreLayer::StoreLayer()
{
}

StoreLayer::~StoreLayer()
{
}
bool StoreLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/coin.plist", "images/coin.png");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size winSize = Director::getInstance()->getWinSize();
	//shop 
	auto _shop = Sprite::create("images/shop.png");
	_shop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_shop->setPosition(Vec2(0.0f, 0.0f));
	_shop->setContentSize(Size(visibleSize.width, visibleSize.height));
	this->addChild(_shop);
	//shop item
	for (int i = 0; i < 3; i++)
	{
		auto _ItemWeapon = Sprite::create("images/ItemWeapon.png");
		_ItemWeapon->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		_ItemWeapon->setScale(1.0f, 1.5f);
		_ItemWeapon->setPosition(Vec2(winSize.width*(ITEM_WIDTH_POSITION + (ITEM_DISTANCT_POSITION*i)), winSize.height*ITEM_HEIGHT_POSITION));
		this->addChild(_ItemWeapon);	

	}
	//Upgrade button
	_upgradeBtn = cocos2d::ui::Button::create("images/UpgradeWeapon.png");
	_upgradeBtn->setPosition(Vec2(winSize.width*(UPGRADEBTN_WIDTH_POSITION), winSize.height*UPGRADEBTN_HEIGHT_POSITION));
	_upgradeBtn->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchUpgradeButton, this));
	this->addChild(_upgradeBtn);
	//quit button
	_quitShop = cocos2d::ui::Button::create("images/quit_shop.png");
	_quitShop->setPosition(Vec2(visibleSize.width*0.95f, visibleSize.height*0.9f));
	_quitShop->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchQuitButton, this));
	this->addChild(_quitShop);
	//weapon button
	_weaponBtn = cocos2d::ui::Button::create("images/ShopButton.png");
	_weaponBtn->setPosition(Vec2(visibleSize.width*0.3f, visibleSize.height*0.12f));
	_weaponBtn->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchWeaponButton, this));
	this->addChild(_weaponBtn);
	auto _labelWeapon = Label::createWithTTF("Weapon", "fonts/kenvector_future.ttf", 25);
	_labelWeapon->setPosition(_weaponBtn->getPosition());
	_labelWeapon->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelWeapon);
	//Item button
	_itemBtn = cocos2d::ui::Button::create("images/ShopButton.png");
	_itemBtn->setPosition(Vec2(visibleSize.width*0.7f, visibleSize.height*0.12f));
	_itemBtn->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchItemButton, this));
	this->addChild(_itemBtn);
	auto _labelItem = Label::createWithTTF("Item", "fonts/kenvector_future.ttf", 25);
	_labelItem->setPosition(_itemBtn->getPosition());
	_labelItem->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelItem);
	//money number
	_Money = Money::create();
	_Money->setShopMoneyPos();
	this->addChild(_Money);
	//Icon gun
	_iconGun = M4A1::create();
	def = UserDefault::getInstance();
	_iconGun->_Level = def->getIntegerForKey("LevelM4A1",1);
	_iconGun->_Stats.setStats(DAMAGE_M4A1*0.15*_iconGun->_Level, NUMBER_BULLET_M4A1+(0.5*_iconGun->_Level), PRICE_M4A1*1.5*_iconGun->_Level);
	_iconGun->setIcon();
	this->addChild(_iconGun, 4);
	//Icon HP
	_iconHP = new HP();
	_iconHP->itemStat.setStats(STAT_HP, NUMBER_HP, PRICE_HP);
	_iconHP->setIcon();
	_iconHP->setLabelStats();
	_iconHP->hide();
	this->addChild(_iconHP, 4);
	//Price
	_Price = Sprite::createWithSpriteFrameName("coin1.png");
	_Price->setPosition(Vec2(winSize.width*(PRICE_WIDTH_POSITION), winSize.height*PRICE_HEIGHT_POSITION));
	_Price->setScale(0.15f);
	this->addChild(_Price);
	std::string _priceStr = StringUtils::format("  %i", _iconGun->_Stats._Price);
	_labelUpgrade = Label::createWithTTF(_priceStr, "fonts/kenvector_future.ttf", 25);
	_labelUpgrade->setPosition(Vec2(winSize.width*(PRICE_LABEL_WIDTH_POSITION), winSize.height*PRICE_LABEL_HEIGHT_POSITION));
	_labelUpgrade->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelUpgrade);
	return true;
}
void StoreLayer::TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->removeAllChildren();
		_btnGamePlayLayer->resumeGame();
	}
}
void StoreLayer::TouchUpgradeButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{ 
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		if (_shopTotalMoney >= _iconGun->_Stats._Price)
		{
			_shopTotalMoney = _shopTotalMoney - _iconGun->_Stats._Price;
			_btnGamePlayLayer->setTotalMoney(_shopTotalMoney);
			_Money->setMoney(_shopTotalMoney);
			_iconGun->_Level++;
			def->setIntegerForKey("LevelM4A1", _iconGun->_Level);
			int bulletNum = NUMBER_BULLET_M4A1 + (NUMBER_BULLET_M4A1*0.25*_iconGun->_Level);
			_iconGun->_Stats.setStats(DAMAGE_M4A1 + (pow(10, 1 / _iconGun->_Level)*_iconGun->_Level), bulletNum, PRICE_M4A1*1.5*_iconGun->_Level);
			_iconGun->setLabelStats();
			std::string _priceStr = StringUtils::format("  %i", _iconGun->_Stats._Price);
			_labelUpgrade->setString(_priceStr);
			if (_callback)
			{
				_callback(_iconGun);
			}

		}
	}
}
void StoreLayer::setCallBack(std::function<void(M4A1* Gun)> callback)
{
	_callback = callback;
	
}

void StoreLayer::setGamePlayLayerPtr(GamePlayLayer* ptr)
{
	_btnGamePlayLayer = ptr;
}
void StoreLayer::setTotalMoney(int _GameTotalMoney)
{
	_shopTotalMoney = _GameTotalMoney;
	_Money->setMoney(_shopTotalMoney);
	
}
void StoreLayer::TouchWeaponButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		_iconHP->hide();
		_iconGun->show();
		std::string _priceStr = StringUtils::format("  %i", _iconGun->_Stats._Price);
		_labelUpgrade->setString(_priceStr);
	}

}
void StoreLayer::TouchItemButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		_iconGun->hide();
		_iconHP->show();
		_iconHP->setLabelStats();
		std::string _priceStr = StringUtils::format("  %i", _iconHP->itemStat._Price);
		_labelUpgrade->setString(_priceStr);
	}
}