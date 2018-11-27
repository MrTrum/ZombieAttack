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
USING_NS_CC;
M4A1::M4A1()
{
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
void M4A1::setIcon()
{
	Size winSize = Director::getInstance()->getWinSize();
	_iconGun = Sprite::create("images/M4A1.png");
	_iconGun->setPosition(winSize.height*0.28f, winSize.width*0.42f);
	_iconGun->setScale(2.5f,2.0f);
	this->addChild(_iconGun);
	_Dmg = Sprite::create("images/damage.png");
	_Dmg->setPosition(winSize.height*0.18f, winSize.width*0.31f);
	_Dmg->setScale(0.12f);
	this->addChild(_Dmg);
	std::string _dmgStr = StringUtils::format("  %i", _Stats._Damage);
	_labelDmg = Label::createWithTTF(_dmgStr, "fonts/kenvector_future.ttf", 30);
	_labelDmg->setPosition(winSize.height*0.33f, winSize.width*0.31f);
	this->addChild(_labelDmg);
	_bulletNum = Sprite::create("images/bulletNum.png");
	_bulletNum->setPosition(winSize.height*0.18f, winSize.width*0.24f);
	_bulletNum->setScale(0.18f);
	this->addChild(_bulletNum);
	std::string _numStr = StringUtils::format("  %i", _Stats._BulletNumber);
	_labelNum = Label::createWithTTF(_numStr, "fonts/kenvector_future.ttf", 30);
	_labelNum->setPosition(winSize.height*0.33f, winSize.width*0.24f);
	this->addChild(_labelNum);
	_Price = Sprite::createWithSpriteFrameName("coin1.png");
	_Price->setPosition(Vec2(winSize.width*(PRICE_WIDTH_POSITION), winSize.height*PRICE_HEIGHT_POSITION));
	_Price->setScale(0.15f);
	this->addChild(_Price);
	std::string _priceStr = StringUtils::format("  %i", _Stats._Price);
	_labelUpgrade = Label::createWithTTF(_priceStr, "fonts/kenvector_future.ttf", 25);
	_labelUpgrade->setPosition(Vec2(winSize.width*(PRICE_LABEL_WIDTH_POSITION), winSize.height*PRICE_LABEL_HEIGHT_POSITION));
	_labelUpgrade->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelUpgrade);
	

}
void M4A1::hide()
{
	this->setVisible(false);
}
void M4A1::setLabelStats()
{
	std::string _dmgStr = StringUtils::format("  %i", _Stats._Damage);
	_labelDmg->setString(_dmgStr);
	std::string _numStr = StringUtils::format("  %i", _Stats._BulletNumber);
	_labelNum->setString(_numStr);
}
void M4A1::show()
{
	this->setVisible(true);
}
