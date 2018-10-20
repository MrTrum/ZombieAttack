#include "Money.h"
#include "NumberConst.h"
USING_NS_CC;
bool Money::_beginMoney = false;
int Money::_moneyGO = 0;
void Money::resetMoney()
{
	_beginMoney = false;
}
Money::Money()
{
}

Money::~Money()
{
}
bool Money::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size winSize = Director::getInstance()->getWinSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/numbers.plist",
		"images/numbers.png");
	if (_beginMoney == false)
	{
		_money1 = Sprite::createWithSpriteFrameName("0.png");
		_money1->setPosition(Vec2(winSize.width*0.063f, winSize.height*0.968f));
		_money1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		_money1->setScale(0.15f);
		this->addChild(_money1, 2);
		_money2 = Sprite::createWithSpriteFrameName("0.png");
		_money2->setPosition(Vec2(winSize.width*0.089f, winSize.height*0.968f));
		_money1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_money2->setScale(0.15f);
		this->addChild(_money2, 2);
		_money3 = Sprite::createWithSpriteFrameName("0.png");
		_money3->setPosition(Vec2(winSize.width*0.115f, winSize.height*0.968f));
		_money3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_money3->setScale(0.15f);
		this->addChild(_money3, 2);
		_money4 = Sprite::createWithSpriteFrameName("0.png");
		_money4->setPosition(Vec2(winSize.width*0.142f, winSize.height*0.968f)); 
		_money4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_money4->setScale(0.15f);
		this->addChild(_money4, 2);
		_money5 = Sprite::createWithSpriteFrameName("0.png");
		_money5->setPosition(Vec2(winSize.width*0.169f, winSize.height*0.968f)); 
		_money5->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_money5->setScale(0.15f);
		this->addChild(_money5, 2);
		_money6 = Sprite::createWithSpriteFrameName("0.png");
		_money6->setPosition(Vec2(winSize.width*0.196f, winSize.height*0.968f)); 
		_money6->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_money6->setScale(0.15f);
		this->addChild(_money6, 2);
		_beginMoney = true;
	}
	return true;
}
void Money::setMoney(int money)
{
	if (money >= ENDNUM)
	{
		int max = 9;
		std::string tempscore1 = StringUtils::format("%i.png", max);
		_money6->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", max);
		_money5->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", max);
		_money4->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", max);
		_money3->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", max);
		_money2->setSpriteFrame(tempscore5);
		std::string tempscore6 = StringUtils::format("%i.png", max);
		_money1->setSpriteFrame(tempscore6);

	}
	else if (money >= HUNDREDSOFTHOUSANDS)
	{
		int unit = money % UNIT;
		int dozens = (money / DOZENS) % UNIT;
		int hundreds = (money / HUNDREDS) % DOZENS;
		int thousands = (money / THOUSANDS) % DOZENS;
		int tensofthousands = (money / TENSOFTHOUSANDS) % DOZENS;
		int hundredofthousands = money / HUNDREDSOFTHOUSANDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_money6->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_money5->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_money4->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_money3->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_money2->setSpriteFrame(tempscore5);
		std::string tempscore6 = StringUtils::format("%i.png", hundredofthousands);
		_money1->setSpriteFrame(tempscore6);
	}
	else if (money >= TENSOFTHOUSANDS)
	{
		int unit = money % UNIT;
		int dozens = (money / DOZENS) % UNIT;
		int hundreds = (money / HUNDREDS) % DOZENS;
		int thousands = (money / THOUSANDS) % DOZENS;
		int tensofthousands = money / TENSOFTHOUSANDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_money6->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_money5->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_money4->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_money3->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_money2->setSpriteFrame(tempscore5);
	}
	else if (money >= THOUSANDS)
	{
		int unit = money % UNIT;
		int dozens = (money / DOZENS) % UNIT;
		int hundreds = (money / HUNDREDS)  % DOZENS;
		int thousands = money / THOUSANDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_money6->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_money5->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_money4->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_money3->setSpriteFrame(tempscore4);
	}
	else if (money >= HUNDREDS)
	{
		int unit = money % UNIT;
		int dozens = (money / DOZENS) % UNIT;
		int hundreds = money / HUNDREDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_money6->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_money5->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_money4->setSpriteFrame(tempscore3);
	}
	else if (money >= DOZENS)
	{
		int unit = money % UNIT;
		int dozens = money / DOZENS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_money6->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_money5->setSpriteFrame(tempscore2);
	}
	else
	{
		std::string tempscore = StringUtils::format("%i.png", money);
		_money6->setSpriteFrame(tempscore);
	}
	_moneyGO = money;
}