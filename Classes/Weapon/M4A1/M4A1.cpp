﻿#include "Weapon/M4A1/M4A1.h"
#include "Parameter.h"
#define UPGRADEBTN_WIDTH_POSITION 0.185f
#define UPGRADEBTN_HEIGHT_POSITION 0.25f
#define UPGRADEBTN_DISTANCT_POSITION 0.32f
#define PRICE_WIDTH_POSITION 0.11f
#define PRICE_HEIGHT_POSITION 0.25f
#define PRICE_LABEL_WIDTH_POSITION 0.18f
#define PRICE_LABEL_HEIGHT_POSITION 0.25f
#define PRICE_DISTANCT_POSITION 0.32f
M4A1::M4A1()
{
	_Level = 0;
	baseBullet = 0;
}

M4A1::~M4A1()
{
}
bool M4A1::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	//Tạo súng
	this->_Level = UserDefault::getInstance()->getIntegerForKey("LevelM4A1",1);
	return true;
}
void M4A1::setIcon(Size panel)
{
	Size winSize = Director::getInstance()->getWinSize();
	_panel = panel;
	_iconGun = Sprite::create("m16.png");
	_iconGun->setPosition(panel.width * 0.23f, panel.height * 0.7f);
	_iconGun->setScale(2.5f,2.0f);
	this->addChild(_iconGun);
	_Dmg = Sprite::create("images/damage.png");
	_Dmg->setPosition(panel.width * 0.14f, panel.height * 0.55f);
	_Dmg->setScale(0.12f);
	this->addChild(_Dmg);
	std::string _dmgStr = StringUtils::format("  %i", _Stats._Damage);
	_labelDmg = Label::createWithTTF(_dmgStr, "fonts/kenvector_future.ttf", winSize.height * 0.06f);
	_labelDmg->setPosition(panel.width * 0.27f, panel.height * 0.55f);
	this->addChild(_labelDmg);
	_bulletNum = Sprite::create("images/bulletNum.png");
	_bulletNum->setPosition(panel.width * 0.14f, panel.height * 0.42f);
	_bulletNum->setScale(0.18f);
	this->addChild(_bulletNum);
	std::string _numStr = StringUtils::format("  %i", _Stats._BulletNumber);
	_labelNum = Label::createWithTTF(_numStr, "fonts/kenvector_future.ttf", winSize.height * 0.06f);
	_labelNum->setPosition(panel.width * 0.27f, panel.height * 0.42f);
	this->addChild(_labelNum);
	_Price = Sprite::createWithSpriteFrameName("coin1.png");
	_Price->setPosition(panel.width * 0.15f, panel.height * 0.3f);
	_Price->setScale(0.3f);
	this->addChild(_Price);
	std::string _priceStr = StringUtils::format("  %i", _Stats._Price);
	_labelUpgrade = Label::createWithTTF(_priceStr, "fonts/kenvector_future.ttf", winSize.height * 0.06f);
	_labelUpgrade->setPosition(panel.width * 0.24f, panel.height * 0.3f);
	_labelUpgrade->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelUpgrade);
	
	this->setLabelStats(_Level);
}
void M4A1::hide()
{
	_Dmg->setVisible(true);
	_labelDmg->setVisible(true);
	_bulletNum->setVisible(true);
	_labelNum->setVisible(true);
	_buyBullet->setVisible(false);
	_labelBuyBullet->setVisible(false);
}
void M4A1::setLabelStats(int Level)
{
		Level++;
		std::string _dmgStr = StringUtils::format("  %i", DAMAGE_M4A1 + (10 * Level));
		_labelDmg->setString(_dmgStr);
		std::string _numStr = StringUtils::format("  %i", NUMBER_BULLET_SHOOT + (10 * Level));
		_labelNum->setString(_numStr);
		int price = PRICE_M4A1 * 1.5*Level;
		std::string _priceStr = StringUtils::format("  %i", price);
		_labelUpgrade->setString(_priceStr);
}
void M4A1::show()
{
	_Dmg->setVisible(false);
	_labelDmg->setVisible(false);
	_bulletNum->setVisible(false);
	_labelNum->setVisible(false);
	Size winSize = Director::getInstance()->getWinSize();
	_buyBullet = Sprite::create("images/bulletNum.png");
	_buyBullet->setPosition(_panel.width * 0.14f, _panel.height * 0.45f);
	_buyBullet->setScale(0.4f);
	this->addChild(_buyBullet);
	std::string _dmgStr = StringUtils::format("  +  %i", _Stats._BulletNumber * 2);
	_labelBuyBullet = Label::createWithTTF(_dmgStr, "fonts/kenvector_future.ttf", winSize.height * 0.06f);
	_labelBuyBullet->setPosition(_panel.width * 0.27f, _panel.height * 0.45f);
	this->addChild(_labelBuyBullet);
	int test = (PRICE_BULLET_M4A1*_Stats._BulletNumber);
	std::string _priceStr = StringUtils::format("  %i", test);
	_labelUpgrade->setString(_priceStr);

}
