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
	auto anchorpointX = _sprBase->getContentSize().width;
	_sprBase->setAnchorPoint(Vec2(0.75f, 0.0f));

	PhysicsBody *_basePhysic = PhysicsBody::createBox(Size(_sprBase->getContentSize()),
		PhysicsMaterial(0.1f,0.1f,0.1f),Vec2(0.f, 0.f));
	_basePhysic->setDynamic(false);
	_sprBase->setPhysicsBody(_basePhysic);

	return true;
}