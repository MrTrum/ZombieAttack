#include "UI/StoreItem/StoreLayer.h"
#include "GamePlayLayer.h"
#include "Parameter.h"
#include "math.h"
#include "AudioEngine.h"


#define UPGRADE_INDEX 0
#define BUY_ITEM_INDEX 1
StoreLayer::StoreLayer()
{
	_chon = 0;
	_shopTotalMoney = 0;
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
	//Play music
	shopMusic = experimental::AudioEngine::play2d("audio/nhacVaoShop.mp3");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/coin.plist", "images/coin.png");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size winSize = Director::getInstance()->getWinSize();
	//shop 
	auto _shop = Sprite::create("images/shop.png");
	_shop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_shop->setPosition(Vec2(0.0f, 0.0f));
	_shop->setContentSize(Size(visibleSize.width, visibleSize.height));
	addChild(_shop);
	auto shopSize = _shop->getContentSize();
	//shop item
	for (int i = 0; i < 3; i++)
	{
		auto _ItemWeapon = Sprite::create("images/ItemWeapon.png");
		_ItemWeapon->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		_ItemWeapon->setScale(shopSize.width/ _ItemWeapon->getContentSize().width * (0.7f/3 ),
			shopSize.height / _ItemWeapon->getContentSize().height * 0.55f);
		_ItemWeapon->setPosition(Vec2(shopSize.width * 0.1f + i *( _ItemWeapon->getContentSize().width + shopSize.width * 0.15f)
			, shopSize.height * 0.2f ));
		_shop->addChild(_ItemWeapon);
		listSpriteItem.pushBack(_ItemWeapon);
		_upgradeBtn = cocos2d::ui::Button::create("images/UpgradeWeapon.png");
		_upgradeBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_upgradeBtn->setPosition(Vec2(_ItemWeapon->getContentSize().width *0.5f
			, _ItemWeapon->getContentSize().height * 0.1f));
		_upgradeBtn->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchUpgradeButton, this));
		_ItemWeapon->addChild(_upgradeBtn);
		listButtonItem.pushBack(_upgradeBtn);
	}

	//quit button
	_quitShop = cocos2d::ui::Button::create("images/quit_shop.png");
	_quitShop->setPosition(Vec2(visibleSize.width*0.95f, visibleSize.height*0.9f));
	_quitShop->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchQuitButton, this));
	_shop->addChild(_quitShop);
	//Upgrade Item button
	_upgradeItemBtn = cocos2d::ui::Button::create("images/ShopButton.png");
	_upgradeItemBtn->setPosition(Vec2(visibleSize.width*0.2f, visibleSize.height*0.12f));
	_upgradeItemBtn->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchUpgradeWeaponButton, this));
	_shop->addChild(_upgradeItemBtn);
	auto _labelUpgradeItem = Label::createWithTTF("Upgrade", "fonts/kenvector_future.ttf", 25);
	_labelUpgradeItem->setPosition(_upgradeItemBtn->getPosition());
	_labelUpgradeItem->setColor(cocos2d::Color3B(0, 0, 0));
	_shop->addChild(_labelUpgradeItem);
	//Item button
	_itemBtn = cocos2d::ui::Button::create("images/ShopButton.png");
	_itemBtn->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height*0.12f));
	_itemBtn->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchItemButton, this));
	_shop->addChild(_itemBtn);
	auto _labelItem = Label::createWithTTF("Item", "fonts/kenvector_future.ttf", 25);
	_labelItem->setPosition(_itemBtn->getPosition());
	_labelItem->setColor(cocos2d::Color3B(0, 0, 0));
	_shop->addChild(_labelItem);
	//Weapon button
	_weaponBtn = cocos2d::ui::Button::create("images/ShopButton.png");
	_weaponBtn->setPosition(Vec2(visibleSize.width*0.8f, visibleSize.height*0.12f));
	_weaponBtn->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchWeaponButton, this));
	_shop->addChild(_weaponBtn);
	_weaponBtn->setEnabled(false);
	auto _labelWeapon = Label::createWithTTF("Coming Soon", "fonts/kenvector_future.ttf", 25);
	_labelWeapon->setPosition(_weaponBtn->getPosition());
	_labelWeapon->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelWeapon);
	//money number
	_Money = Money::create();
	_Money->setShopMoneyPos();
	_shop->addChild(_Money);
	//Icon gun
	_iconGun = M4A1::create();
	def = UserDefault::getInstance();
	_iconGun->_Level = def->getIntegerForKey("LevelM4A1", 1);
	_iconGun->baseBullet = UserDefault::getInstance()->getIntegerForKey("CurrentTotalBullet");
	int tempLevel = (_iconGun->_Level);
	_iconGun->_Stats.setStats(DAMAGE_M4A1 + (10 * tempLevel), NUMBER_BULLET_SHOOT + (10* tempLevel), PRICE_M4A1*1.5*tempLevel);
	_iconGun->setIcon(shopSize);
	_shop->addChild(_iconGun, 4);
	//Icon HP
	_iconHP = new HP();
	_iconHP->itemStat.setStats(STAT_HP, NUMBER_HP, PRICE_HP);
	_iconHP->setIcon(shopSize);
	_iconHP->setLabelStats();
	_shop->addChild(_iconHP, 4);
	_bomb = Dynamite::create();
	_bomb->show(shopSize);
	_bomb->setVisible(false);
	_shop->addChild(_bomb, 4);
	return true;
}
void StoreLayer::TouchWeaponButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{

}
void StoreLayer::TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->removeAllChildren();
		_btnGamePlayLayer->resumeGame();
		experimental::AudioEngine::stop(shopMusic);
	}
}
void StoreLayer::setCallBackBomb(std::function<void(Dynamite* HP)> callbackBomb)
{
	_callbackBomb = callbackBomb;
}
void StoreLayer::TouchUpgradeButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		if (_chon == UPGRADE_INDEX)
		{
			if (_shopTotalMoney >= _iconGun->_Stats._Price && pSender == listButtonItem.at(0))
			{
				_shopTotalMoney = _shopTotalMoney - _iconGun->_Stats._Price;
				_btnGamePlayLayer->setTotalMoney(_shopTotalMoney);
				_Money->setMoney(_shopTotalMoney);
				_iconGun->_Level++;
				int bulletNum = NUMBER_BULLET_SHOOT + (10 * _iconGun->_Level);
				_iconGun->_Stats.setStats(DAMAGE_M4A1 + (10 * _iconGun->_Level), bulletNum, PRICE_M4A1*1.5*_iconGun->_Level);
			
				def->setIntegerForKey("LevelM4A1", _iconGun->_Level);
				
				_iconGun->setLabelStats(_iconGun->_Level);
				if (_callback)
				{
					_callback(_iconGun);
				}

			}
			else if (_shopTotalMoney >= _iconGun->_Stats._Price && pSender == listButtonItem.at(1))
			{

			}
			else if (_shopTotalMoney >= _iconGun->_Stats._Price && pSender == listButtonItem.at(2))
			{

			}
		}
		else if (_chon == BUY_ITEM_INDEX)
		{
			if (_shopTotalMoney >= (PRICE_BULLET_M4A1*_iconGun->_Stats._BulletNumber) && pSender == listButtonItem.at(0))
			{
				auto test = (PRICE_BULLET_M4A1*_iconGun->_Stats._BulletNumber);
				_shopTotalMoney = _shopTotalMoney - test;
				_btnGamePlayLayer->setTotalMoney(_shopTotalMoney);
				_Money->setMoney(_shopTotalMoney);
				auto currentBullet = UserDefault::getInstance()->getIntegerForKey("CurrentTotalBullet");
				_iconGun->baseBullet =currentBullet+ (_iconGun->_Stats._BulletNumber * 2);
				_iconGun->recharge = true;
				if (_callback)
				{
					_callback(_iconGun);
				}

			}
			else if (_shopTotalMoney >= (PRICE_NUMBER_HP*_iconHP->itemStat._NumberItem) && pSender == listButtonItem.at(1))
			{
				_shopTotalMoney = _shopTotalMoney - (PRICE_NUMBER_HP*_iconHP->itemStat._NumberItem);
				_btnGamePlayLayer->setTotalMoney(_shopTotalMoney);
				_Money->setMoney(_shopTotalMoney);
				_iconHP->recharge = true;
				if (_callbackHP)
				{
					_callbackHP(_iconHP);
				}
			}
			else if (_shopTotalMoney >= (PRICE_BOMB*BOMB_NUMBER) && pSender == listButtonItem.at(2))
			{
				_shopTotalMoney = _shopTotalMoney - (PRICE_BOMB*BOMB_NUMBER);
				_btnGamePlayLayer->setTotalMoney(_shopTotalMoney);
				_Money->setMoney(_shopTotalMoney);
				_bomb->recharge = true;
				if (_callbackBomb)
				{
					_callbackBomb(_bomb);
				}
			}
		}

	}
}
void StoreLayer::setCallBackHP(std::function<void(HP* HP)> callbackHP)
{
	_callbackHP = callbackHP;
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
void StoreLayer::TouchUpgradeWeaponButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		_chon = UPGRADE_INDEX;
		_iconGun->hide();
		_iconHP->iconItemHide();
		_bomb->setVisible(false);
	}

}
void StoreLayer::TouchItemButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		_iconGun->show();
		_iconHP->iconItemShow();
		_bomb->setVisible(true);
		_chon = BUY_ITEM_INDEX;
	}
}