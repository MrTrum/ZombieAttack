#include "Store.h"
#include "ui/CocosGUI.h"

MyStore::MyStore()
{
	scale = 0;
	_isBtnOpen = false;
}

MyStore::~MyStore()
{
}

bool MyStore::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	_sprShop = Sprite::create("shop/ShopBackground.png");
	shopSize = _sprShop->getContentSize();
	addChild(_sprShop);
	_sprShop->setScale(winSize.height / _sprShop->getContentSize().height);
	_sprShop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprUpLayer = Sprite::create("shop/upLayer.png");
	_sprShop->addChild(_sprUpLayer);
	_sprUpLayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprUpLayer->setPosition(shopSize.width * 0.2f, 0.0f);

	_selectGun = ui::Button::create("shop/button.png");
	_sprShop->addChild(_selectGun,6);
	_selectGun->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_selectGun->setPosition(Vec2(shopSize.width * 0.2f, shopSize.height * 0.65f));
	_selectGun->addTouchEventListener(CC_CALLBACK_2(MyStore::onTouchUpGunBtn, this));
	auto _lbGun = Label::createWithTTF("GUN", "fonts/IBMPlexSans-BoldItalic.ttf", shopSize.height * 0.055f);
	_selectGun->addChild(_lbGun);
	_lbGun->enableOutline(cocos2d::Color4B::RED, 4);
	_lbGun->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_lbGun->setPosition(_selectGun->getContentSize() * 0.5f);

	_selectHealth = ui::Button::create("shop/button.png");
	_sprShop->addChild(_selectHealth, 6);
	_selectHealth->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_selectHealth->setPosition(Vec2(shopSize.width * 0.39f, shopSize.height * 0.65f));
	_selectHealth->addTouchEventListener(CC_CALLBACK_2(MyStore::onTouchUpHealthBtn, this));
	auto _lbHealth = Label::createWithTTF("HEALTH", "fonts/IBMPlexSans-BoldItalic.ttf", shopSize.height * 0.055f);
	_selectHealth->addChild(_lbHealth);
	_lbHealth->enableOutline(cocos2d::Color4B::RED, 4);
	_lbHealth->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_lbHealth->setPosition(_selectGun->getContentSize() * 0.5f);

	_selectArmor = ui::Button::create("shop/button.png");
	_sprShop->addChild(_selectArmor, 6);
	_selectArmor->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_selectArmor->setPosition(Vec2(shopSize.width * 0.58f, shopSize.height * 0.65f));
	_selectArmor->addTouchEventListener(CC_CALLBACK_2(MyStore::onTouchUpArmorBtn, this));
	auto _lbArmor = Label::createWithTTF("ARMOR", "fonts/IBMPlexSans-BoldItalic.ttf", shopSize.height * 0.055f);
	_selectArmor->addChild(_lbArmor);
	_lbArmor->enableOutline(cocos2d::Color4B::RED, 4);
	_lbArmor->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_lbArmor->setPosition(_selectArmor->getContentSize() * 0.5f);

	gunShop();
	scheduleUpdate();
	return true;
}

void MyStore::onTouchUpGunBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	gunShop();
}

void MyStore::onTouchUpHealthBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	healthShop();

}

void MyStore::onTouchUpArmorBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	armorShop();
}

void MyStore::onTouchCloseBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	
}

void MyStore::update(float dt)
{
	
}

void MyStore::gunShop()
{
	_sprUpLayer->removeAllChildren();
	auto sprGun = Sprite::create("shop/m16.png");
	_sprUpLayer->addChild(sprGun);
	sprGun->setPosition(Vec2(_sprUpLayer->getContentSize().width * 0.1f,
		_sprUpLayer->getContentSize().height * 0.65f));

	_upgradeGun = ui::Button::create("shop/upgradBtn.png");
	_sprUpLayer->addChild(_upgradeGun);
	_upgradeGun->setPosition(Vec2(_sprUpLayer->getContentSize().width * 0.7f,
		_sprUpLayer->getContentSize().height * 0.23f));
}

void MyStore::healthShop()
{
	_sprUpLayer->removeAllChildren();
	auto sprHealth = Sprite::create("shop/potion.png");
	_sprUpLayer->addChild(sprHealth);
	sprHealth->setPosition(Vec2(_sprUpLayer->getContentSize().width * 0.1f,
		_sprUpLayer->getContentSize().height * 0.65f));

	_upgradeHealth = ui::Button::create("shop/upgradBtn.png");
	_sprUpLayer->addChild(_upgradeHealth);
	_upgradeHealth->setPosition(Vec2(_sprUpLayer->getContentSize().width * 0.7f,
		_sprUpLayer->getContentSize().height * 0.23f));
}
void MyStore::armorShop()
{
	_sprUpLayer->removeAllChildren();
	auto sprArmor = Sprite::create("shop/armor.png");
	_sprUpLayer->addChild(sprArmor);
	sprArmor->setPosition(Vec2(_sprUpLayer->getContentSize().width * 0.1f,
		_sprUpLayer->getContentSize().height * 0.65f));

	_upgradeArmor = ui::Button::create("shop/upgradBtn.png");
	_sprUpLayer->addChild(_upgradeArmor);
	_upgradeArmor->setPosition(Vec2(_sprUpLayer->getContentSize().width * 0.7f,
		_sprUpLayer->getContentSize().height * 0.23f));
}