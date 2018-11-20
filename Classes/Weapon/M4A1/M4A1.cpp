#include "Weapon/M4A1/M4A1.h"
#include "Parameter.h"
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
	this->_Level = UserDefault::getInstance()->getIntegerForKey("LevelM4A1");
	return true;
}
void M4A1::setIcon()
{
	Size winSize = Director::getInstance()->getWinSize();
	_iconGun = Sprite::create("images/M4A1.png");
	_iconGun->setPosition(winSize.height*0.28f, winSize.width*0.42f);
	_iconGun->setScale(2.5f,2.0f);
	this->addChild(_iconGun);
	auto _Dmg = Sprite::create("images/damage.png");
	_Dmg->setPosition(winSize.height*0.18f, winSize.width*0.31f);
	_Dmg->setScale(0.12f);
	this->addChild(_Dmg);
	std::string _dmgStr = StringUtils::format("  %i", _Stats._Damage);
	_labelDmg = Label::createWithTTF(_dmgStr, "fonts/kenvector_future.ttf", 30);
	_labelDmg->setPosition(winSize.height*0.33f, winSize.width*0.31f);
	this->addChild(_labelDmg);
	auto _bulletNum = Sprite::create("images/bulletNum.png");
	_bulletNum->setPosition(winSize.height*0.18f, winSize.width*0.24f);
	_bulletNum->setScale(0.18f);
	this->addChild(_bulletNum);
	std::string _numStr = StringUtils::format("  %i", _Stats._BulletNumber);
	_labelNum = Label::createWithTTF(_numStr, "fonts/kenvector_future.ttf", 30);
	_labelNum->setPosition(winSize.height*0.33f, winSize.width*0.24f);
	this->addChild(_labelNum);
	

}
void M4A1::setLabelStats()
{
	std::string _dmgStr = StringUtils::format("  %i", _Stats._Damage);
	_labelDmg->setString(_dmgStr);
	std::string _numStr = StringUtils::format("  %i", _Stats._BulletNumber);
	_labelNum->setString(_numStr);
}

