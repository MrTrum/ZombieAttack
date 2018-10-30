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
	_sprhero = Sprite::createWithSpriteFrameName("idle00.png");
	this->addChild(_sprhero);
	_sprhero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setContentSize(_sprhero->getContentSize());
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprhero->setPosition(winSize.width * 0.17f, winSize.height * 0.16f);
	_sprhero->setScale(1.0f * SCALE_PARAMETER_);
/*
	Animation* fatguyanim = Animation::create();

	for (int i = 0; i < 16; i++)
	{
		std::string name = StringUtils::format("idle%02d.png", i);
		fatguyanim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	fatguyanim->setDelayPerUnit(1 / 4.0f);
	Animate* animate = Animate::create(fatguyanim);
	_sprhero->runAction(RepeatForever::create(animate));*/

	return true;
}

void Hero::shootAnimation()
{
	/*Size winSize = Director::getInstance()->getWinSize();
	Animation* animation = Animation::create();

	for (int i = 1; i < 11; i++)
	{
		std::string name = StringUtils::format("fireSG%02d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 30.0f);
	Animate* animate = Animate::create(animation);
	_sprhero->runAction(animate);*/
}

void Hero::playAnimation(AnimationInfo info)
{
	Animation* animation = Animation::create();
	for (int i = 0; i < info._numframe; i++)
	{
		std::string name = StringUtils::format("%02d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(info._name + name));
	}
	animation->setDelayPerUnit(1 / info._fps);
	Animate* animate = Animate::create(animation);
	_sprhero->runAction(animate);
}

void Hero::playAnimation(std::string _name, int _numframe, int _fps, int _loop )
{
	Animation* animation = Animation::create();
	for (int i = 0; i < _numframe; i++)
	{
		std::string name = StringUtils::format("%02d.png", i);

		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_name + name));
	}
	animation->setDelayPerUnit(1 / _fps);
	Animate *animate = Animate::create(animation);
	_sprhero->runAction(Repeat::create(animate, _loop));
}