#include "Base.h"
#include "Parameter.h"

USING_NS_CC;

Base::Base()
{
}

Base::~Base()
{
}

bool Base::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	//add base
	_sprBase = Sprite::create("base100.png");
	this->addChild(_sprBase);
	_sprBase->setScale(0.5f * SCALE_PARAMETER_);
	_sprBase->setAnchorPoint(Vec2(0.75f, 0.0f));

	return true;
}