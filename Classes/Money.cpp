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
	for (int i = 0; i < 6; i++)
	{
		_money = Sprite::createWithSpriteFrameName("0.png");
		if (i == 0)
		{
			_money->setPosition(Vec2(winSize.width*NUMBER_GAMEPLAY_POSITION_WIDTH, winSize.height*NUMBER_GAMEPLAY_POSITION_HEIGHT));
		}
		else
		{
			_money->setPosition(Vec2(winSize.width*(NUMBER_GAMEPLAY_POSITION_WIDTH+(NUMBER_DISTANT*i)), winSize.height*NUMBER_GAMEPLAY_POSITION_HEIGHT));
		}
		_money->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_money->setScale(0.15f);
		_listSprite.pushBack(_money);
		this->addChild(_money, 2);
	}
	return true;
}
void Money::setShopMoneyPos()
{
	Size winSize = Director::getInstance()->getWinSize();
	for (int i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			_listSprite.at(i)->setPosition(Vec2(winSize.width*NUMBER_SHOP_POSITION_WIDTH, winSize.height*NUMBER_SHOP_POSITION_HEIGHT));
		}
		else
		{
			_listSprite.at(i)->setPosition(Vec2(winSize.width*(NUMBER_SHOP_POSITION_WIDTH + (NUMBER_DISTANT*i)), winSize.height*NUMBER_SHOP_POSITION_HEIGHT));
		}
	}
}
void Money::setMoney(int money)
{
	if (money >= ENDNUM)
	{
		int max = 9;
		std::string tempscore = StringUtils::format("%i.png", max);
		for (int i = 0; i < 6; i++)
		{
			_listSprite.at(i)->setSpriteFrame(tempscore);
		}

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
		_listSprite.at(5)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(4)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(3)->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_listSprite.at(2)->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_listSprite.at(1)->setSpriteFrame(tempscore5);
		std::string tempscore6 = StringUtils::format("%i.png", hundredofthousands);
		_listSprite.at(0)->setSpriteFrame(tempscore6);
	}
	else if (money >= TENSOFTHOUSANDS)
	{
		int unit = money % UNIT;
		int dozens = (money / DOZENS) % UNIT;
		int hundreds = (money / HUNDREDS) % DOZENS;
		int thousands = (money / THOUSANDS) % DOZENS;
		int tensofthousands = money / TENSOFTHOUSANDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_listSprite.at(5)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(4)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(3)->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_listSprite.at(2)->setSpriteFrame(tempscore4);
		std::string tempscore5 = StringUtils::format("%i.png", tensofthousands);
		_listSprite.at(1)->setSpriteFrame(tempscore5);
	}
	else if (money >= THOUSANDS)
	{
		int unit = money % UNIT;
		int dozens = (money / DOZENS) % UNIT;
		int hundreds = (money / HUNDREDS)  % DOZENS;
		int thousands = money / THOUSANDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_listSprite.at(5)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(4)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(3)->setSpriteFrame(tempscore3);
		std::string tempscore4 = StringUtils::format("%i.png", thousands);
		_listSprite.at(2)->setSpriteFrame(tempscore4);
	}
	else if (money >= HUNDREDS)
	{
		int unit = money % UNIT;
		int dozens = (money / DOZENS) % UNIT;
		int hundreds = money / HUNDREDS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_listSprite.at(5)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(4)->setSpriteFrame(tempscore2);
		std::string tempscore3 = StringUtils::format("%i.png", hundreds);
		_listSprite.at(3)->setSpriteFrame(tempscore3);
	}
	else if (money >= DOZENS)
	{
		int unit = money % UNIT;
		int dozens = money / DOZENS;
		std::string tempscore1 = StringUtils::format("%i.png", unit);
		_listSprite.at(5)->setSpriteFrame(tempscore1);
		std::string tempscore2 = StringUtils::format("%i.png", dozens);
		_listSprite.at(4)->setSpriteFrame(tempscore2);
	}
	else
	{
		std::string tempscore = StringUtils::format("%i.png", money);
		_listSprite.at(5)->setSpriteFrame(tempscore);
	}
	_moneyGO = money;
}