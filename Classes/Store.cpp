#include "Store.h"
#include "ui/CocosGUI.h"

#define ORIGIN_Z	1
#define OPEN_Z		3
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
	winSize = Director::getInstance()->getWinSize();
	auto _sprShop = Sprite::create("shopLayer.png");
	addChild(_sprShop);
	_sprShop->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprShop->setPosition(winSize * 0.5f);
	scale = winSize.width / _sprShop->getContentSize().width;
	_sprShop->setScale(scale);

	//House UpGrade
	_upgradeArmor = cocos2d::ui::Button::create("shopyellow.png", "shopyellow.png", "shopyellow.png");

	float anchorY = _upgradeArmor->getContentSize().height / 2;
	float anchorX = anchorY / (_upgradeArmor->getContentSize().width);

	_upgradeArmor->setAnchorPoint(Vec2(anchorX, 0.5f));
	_upgradeArmor->setPosition(Vec2(winSize.width * 0.18f, winSize.height * 0.4f));
	_upgradeArmor->addTouchEventListener(CC_CALLBACK_2(MyStore::onTouchUpArmorBtn, this));
	_upgradeArmor->setScale(0.6f);
	addChild(_upgradeArmor);

	auto _armorBtnTxt = Label::create("UPGRADE ARMOR", "fonts/kenvector_future.ttf", 40);
	_upgradeArmor->addChild(_armorBtnTxt);
	_armorBtnTxt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_armorBtnTxt->setPosition(Vec2(_upgradeArmor->getContentSize().width * 0.3f, _upgradeArmor->getContentSize().height * 0.5f));
	_armorBtnTxt->enableOutline(Color4B::BLACK, 2);

	_sprUpArmor = Sprite::create("armor.png");
	addChild(_sprUpArmor);
	_sprUpArmor->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprUpArmor->setPosition(Vec2(_upgradeArmor->getPosition()));
	_sprUpArmor->setScale(0.7f);

	//Health Upgrade
	_upgradeHealth = cocos2d::ui::Button::create("shopblue.png", "shopblue.png", "shopblue.png");
	_upgradeHealth->setAnchorPoint(Vec2(anchorX, 0.5f));
	_upgradeHealth->setPosition(Vec2(winSize.width * 0.18f, winSize.height * 0.6f));
	_upgradeHealth->addTouchEventListener(CC_CALLBACK_2(MyStore::onTouchUpHealthBtn, this));
	_upgradeHealth->setScale(0.6f);
	addChild(_upgradeHealth);

	auto _healthBtnTxt = Label::create("MORE HP!!!", "fonts/kenvector_future.ttf", 40);
	_upgradeHealth->addChild(_healthBtnTxt);
	_healthBtnTxt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_healthBtnTxt->setPosition(Vec2(_upgradeHealth->getContentSize().width * 0.3f, _upgradeHealth->getContentSize().height * 0.5f));
	_healthBtnTxt->enableOutline(Color4B::BLACK, 2);

	_sprUpHealth = Sprite::create("images/potion.png");
	addChild(_sprUpHealth);
	_sprUpHealth->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprUpHealth->setPosition(Vec2(_upgradeHealth->getPosition()));
	_sprUpHealth->setScale(0.3f);

	//Gun Upgrade
	_upgradeGun = cocos2d::ui::Button::create("shopred.png", "shopred.png", "shopred.png");
	_upgradeGun->setAnchorPoint(Vec2(anchorX, 0.5f));
	_upgradeGun->setPosition(Vec2(winSize.width * 0.18f, winSize.height * 0.8f));
	_upgradeGun->addTouchEventListener(CC_CALLBACK_2(MyStore::onTouchUpGunBtn, this));
	_upgradeGun->setScale(0.6f);
	addChild(_upgradeGun);

	auto _gunBtnTxt = Label::create("GUN POWER", "fonts/kenvector_future.ttf", 40);
	_upgradeGun->addChild(_gunBtnTxt);
	_gunBtnTxt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_gunBtnTxt->setPosition(Vec2(_upgradeGun->getContentSize().width * 0.3f, _upgradeGun->getContentSize().height * 0.5f));
	_gunBtnTxt->enableOutline(Color4B::BLACK, 2);

	_sprUpGun = Sprite::create("m16.png");
	addChild(_sprUpGun);
	_sprUpGun->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_sprUpGun->setPosition(Vec2(_upgradeGun->getPosition()));
	_sprUpGun->setScale(0.8f);

	_sprUpLayer = Sprite::create("uplayer.png");
	addChild(_sprUpLayer, 2);
	_sprUpLayer->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprUpLayer->setPosition(winSize.width * 0.11f, winSize.height * 0.3f);
	_sprUpLayer->setScaleX(0.0f);
	paperSize = _sprUpLayer->getContentSize();
	
	//closebtn
	_closeBtn = cocos2d::ui::Button::create("images/quit_shop.png");
	_closeBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_closeBtn->setPosition(Vec2(winSize.width * 0.79f, winSize.height * 0.91f));
	_closeBtn->addTouchEventListener(CC_CALLBACK_2(MyStore::onTouchCloseBtn, this));
	_closeBtn->setScale(0.6f);
	addChild(_closeBtn,2);

	scheduleUpdate();
	return true;
}

void MyStore::onTouchUpGunBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	rotate = RotateBy::create(0.4f, 90);

	if (!_isBtnOpen)
	{
		getEnum = GUN;
		_upgradeGun->setZOrder(OPEN_Z);
		_upgradeGun->runAction(rotate);
		_isBtnOpen = true;
		_upgradeGun->setEnabled(false);
		_sprUpLayer->runAction(ScaleTo::create(0.4f, scale));
		gunShop();
	}
}

void MyStore::onTouchUpHealthBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	rotate = RotateBy::create(0.4f, 90);
	if (!_isBtnOpen)
	{
		getEnum = HEALTH;
		_upgradeHealth->setZOrder(OPEN_Z);
		_upgradeHealth->runAction(MoveTo::create(0.2f, Vec2(winSize.width * 0.18f, winSize.height * 0.8f)));
		_upgradeHealth->runAction(rotate);
		_isBtnOpen = true;
		_upgradeHealth->setEnabled(false);
		_sprUpLayer->runAction(ScaleTo::create(0.4f, scale));
		healthShop();
	}

}

void MyStore::onTouchUpArmorBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	rotate = RotateBy::create(0.4f, 90);
	if (!_isBtnOpen)
	{
		getEnum = ARMOR;
		_upgradeArmor->setZOrder(OPEN_Z);
		_upgradeArmor->runAction(MoveTo::create(0.4f, Vec2(winSize.width * 0.18f, winSize.height * 0.8f)));
		_upgradeArmor->runAction(rotate);
		_isBtnOpen = true;
		_upgradeArmor->setEnabled(false);
		_sprUpLayer->runAction(ScaleTo::create(0.4f, scale));
	}
}

void MyStore::onTouchCloseBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	_sprUpLayer->runAction(ScaleTo::create(0.2f, 0.0f, scale));
	rotate = RotateBy::create(0.4f, -90);
	if (_isBtnOpen)
	{
		_isBtnOpen = false;
		if (getEnum == GUN)
		{
			_upgradeGun->setZOrder(ORIGIN_Z);
			_upgradeGun->setEnabled(true);
			_upgradeGun->runAction(rotate);
			getEnum = NULL;
		}
		if (getEnum == HEALTH)
		{
			_upgradeHealth->setZOrder(ORIGIN_Z);
			_upgradeHealth->setEnabled(true);
			_upgradeHealth->runAction(MoveTo::create(0.2f, Vec2(winSize.width * 0.18f, winSize.height * 0.6f)));
			_upgradeHealth->runAction(rotate);
			getEnum = NULL;
		}
		if (getEnum == ARMOR)
		{
			_upgradeArmor->setZOrder(ORIGIN_Z);
			_upgradeArmor->setEnabled(true);
			_upgradeArmor->runAction(MoveTo::create(0.4f, Vec2(winSize.width * 0.18f, winSize.height * 0.4f)));
			_upgradeArmor->runAction(rotate);
			getEnum = NULL;
		}
	}
}

void MyStore::update(float dt)
{
	_closeBtn->setVisible(false);
	_sprUpGun->setPosition(Vec2(_upgradeGun->getPosition()));
	_sprUpGun->setZOrder(_upgradeGun->getZOrder());
	_sprUpHealth->setPosition(Vec2(_upgradeHealth->getPosition()));
	_sprUpHealth->setZOrder(_upgradeHealth->getZOrder());
	_sprUpArmor->setPosition(Vec2(_upgradeArmor->getPosition()));
	_sprUpArmor->setZOrder(_upgradeArmor->getZOrder());
	if (_isBtnOpen)
	{
		_closeBtn->setVisible(true);
	}
}

void MyStore::gunShop()
{
	_sprUpLayer->removeAllChildren();
	auto _power = Label::create("GUN POWER", "fonts/kenvector_future.ttf", 20);
	_sprUpLayer->addChild(_power);
	_power->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_power->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.8f));
	_power->enableOutline(Color4B::BLACK, 2);

	auto levelPowerBG = Sprite::create("levelbarBG.png");
	_sprUpLayer->addChild(levelPowerBG);
	levelPowerBG->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelPowerBG->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.7f));

	auto levelPower = Sprite::create("greenbar.png");
	_sprUpLayer->addChild(levelPower);
	levelPower->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelPower->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.7f));
	levelPower->setScaleX(0.8f);

	auto levelPowerOutline = Sprite::create("levelbar.png");
	_sprUpLayer->addChild(levelPowerOutline);
	levelPowerOutline->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelPowerOutline->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.7f));
	
	auto _magSize = Label::create("Mag Capacity", "fonts/kenvector_future.ttf", 20);
	_sprUpLayer->addChild(_magSize);
	_magSize->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_magSize->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.6f));
	_magSize->enableOutline(Color4B::BLACK, 2);

	auto levelMagBG = Sprite::create("levelbarBG.png");
	_sprUpLayer->addChild(levelMagBG);
	levelMagBG->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelMagBG->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.5f));

	auto levelMag = Sprite::create("greenbar.png");
	_sprUpLayer->addChild(levelMag);
	levelMag->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelMag->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.5f));
	levelMag->setScaleX(0.5f);

	auto levelMagOutline = Sprite::create("levelbar.png");
	_sprUpLayer->addChild(levelMagOutline);
	levelMagOutline->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelMagOutline->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.5f));

	auto _reloadSpd = Label::create("Reload Speed", "fonts/kenvector_future.ttf", 20);
	_sprUpLayer->addChild(_reloadSpd);
	_reloadSpd->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_reloadSpd->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.4f));
	_reloadSpd->enableOutline(Color4B::BLACK, 2);

	auto levelReloadBG = Sprite::create("levelbarBG.png");
	_sprUpLayer->addChild(levelReloadBG);
	levelReloadBG->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelReloadBG->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.3f));

	auto levelReload = Sprite::create("greenbar.png");
	_sprUpLayer->addChild(levelReload);
	levelReload->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelReload->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.3f));
	levelReload->setScaleX(0.3f);

	auto levelReloadOutline = Sprite::create("levelbar.png");
	_sprUpLayer->addChild(levelReloadOutline);
	levelReloadOutline->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	levelReloadOutline->setPosition(Vec2(paperSize.width * 0.2f, paperSize.height * 0.3f));
}

void MyStore::healthShop()
{
	_sprUpLayer->removeAllChildren();
	auto _health = Label::create("Increase Health Point", "fonts/kenvector_future.ttf", 20);
	_sprUpLayer->addChild(_health);
	_health->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_health->setPosition(Vec2(paperSize.width * 0.4f, paperSize.height * 0.9f));
	_health->enableOutline(Color4B::BLACK, 2);
}