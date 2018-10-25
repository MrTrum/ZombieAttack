#include "Hero.h"
#include "Parameter.h"

USING_NS_CC;

Hero::Hero()
{
}

Hero::~Hero()
{
}

bool Hero::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	_sprhero = Sprite::createWithSpriteFrameName("Redneck0.png");
	this->addChild(_sprhero);
	_sprhero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setContentSize(_sprhero->getContentSize());
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprhero->setPosition(winSize.width * 0.17f, winSize.height * 0.16f);
	_sprhero->setScale(1.0f * SCALE_PARAMETER_);

	Animation* fatguyanim = Animation::create();

	for (int i = 0; i < 8; i++)
	{
		std::string name = StringUtils::format("Redneck%d.png", i);
		fatguyanim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	fatguyanim->setDelayPerUnit(1 / 16.0f);
	Animate* animate = Animate::create(fatguyanim);
	_sprhero->runAction(RepeatForever::create(animate));

	return true;
}

void Hero::shootAnimation()
{
	Size winSize = Director::getInstance()->getWinSize();
	Animation* animation = Animation::create();

	for (int i = 1; i < 11; i++)
	{
		std::string name = StringUtils::format("%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 30.0f);
	Animate* animate = Animate::create(animation);
	_sprhero->runAction(animate);
}