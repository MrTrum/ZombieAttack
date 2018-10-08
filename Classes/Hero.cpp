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
	_sprhero = Sprite::createWithSpriteFrameName("1.png");
	this->addChild(_sprhero);
	_sprhero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setContentSize(_sprhero->getContentSize());
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//_sprhero->setPosition(winSize.width * 0.15f, winSize.height * 0.5f);
	_sprhero->setScale(0.3f * SCALE_PARAMETER_);
	return true;
}

void Hero::shootAnimation()
{
	Size winSize = Director::getInstance()->getWinSize();
	Animation* animation = Animation::create();

	for (int i = 0; i < 7; i++)
	{
		std::string name = StringUtils::format("%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 24.0f);
	Animate* animate = Animate::create(animation);
	_sprhero->runAction(animate);
}