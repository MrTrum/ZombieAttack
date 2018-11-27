#include "BackgroundLayer.h"

USING_NS_CC;

BackgroundLayer::BackgroundLayer()
{
}

BackgroundLayer::~BackgroundLayer()
{
}

bool BackgroundLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	//add background
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprBG = Sprite::create("background3.png");
	this->addChild(_sprBG);
	_sprBG->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	float scale = winSize.width / _sprBG->getContentSize().width;
	_sprBG->setScale(scale);
	//add base
	_sprBase = Sprite::create("house.png");
	this->addChild(_sprBase);
	_sprBase->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	return true;
}