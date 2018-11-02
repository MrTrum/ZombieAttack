#include "UI/StoreItem/StoreLayer.h"
#include "GamePlayLayer.h"


#define ITEM_WIDTH_POSITION 0.05f
#define ITEM_HEIGHT_POSITION 0.25f
#define ITEM_DISTANCT_POSITION 0.32f
#define UPGRADEBTN_WIDTH_POSITION 0.185f
#define UPGRADEBTN_HEIGHT_POSITION 0.25f
#define UPGRADEBTN_DISTANCT_POSITION 0.32f

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
		//Upgrade button
		_upgradeBtn = cocos2d::ui::Button::create("images/UpgradeWeapon.png");
		_upgradeBtn->setPosition(Vec2(winSize.width*(UPGRADEBTN_WIDTH_POSITION + (UPGRADEBTN_DISTANCT_POSITION*i)), winSize.height*UPGRADEBTN_HEIGHT_POSITION));
		this->addChild(_upgradeBtn);
		auto _labelUpgrade = Label::createWithTTF("Upgrade", "fonts/kenvector_future.ttf", 25);
		_labelUpgrade->setPosition(_upgradeBtn->getPosition());
		_labelUpgrade->setColor(cocos2d::Color3B(0, 0, 0));
		this->addChild(_labelUpgrade);
	}

	//quit button
	_quitShop = cocos2d::ui::Button::create("images/quit_shop.png");
	_quitShop->setPosition(Vec2(visibleSize.width*0.95f, visibleSize.height*0.9f));
	_quitShop->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchQuitButton, this));
	this->addChild(_quitShop);
	//weapon button
	_weaponBtn = cocos2d::ui::Button::create("images/ShopButton.png");
	_weaponBtn->setPosition(Vec2(visibleSize.width*0.3f, visibleSize.height*0.12f));
	this->addChild(_weaponBtn);
	auto _labelWeapon = Label::createWithTTF("Weapon", "fonts/kenvector_future.ttf", 25);
	_labelWeapon->setPosition(_weaponBtn->getPosition());
	_labelWeapon->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelWeapon);
	//Item button
	_itemBtn = cocos2d::ui::Button::create("images/ShopButton.png");
	_itemBtn->setPosition(Vec2(visibleSize.width*0.7f, visibleSize.height*0.12f));
	this->addChild(_itemBtn);
	auto _labelItem = Label::createWithTTF("Item", "fonts/kenvector_future.ttf", 25);
	_labelItem->setPosition(_itemBtn->getPosition());
	_labelItem->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelItem);
	//money number
	_Money = Money::create();
	_Money->setShopMoneyPos();
	this->addChild(_Money);

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

void StoreLayer::setGamePlayLayerPtr(GamePlayLayer* ptr)
{
	_btnGamePlayLayer = ptr;
}
void StoreLayer::setTotalMoney(int _GameTotalMoney)
{
	_shopTotalMoney = _GameTotalMoney;
	_Money->setMoney(_shopTotalMoney);
}