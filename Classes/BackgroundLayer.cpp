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
	_sprBG = Sprite::create("BG.png");
	this->addChild(_sprBG);
	_sprBG->setPosition(winSize * 0.5f);

	float scaleX = winSize.width / _sprBG->getContentSize().width;
	float scaleY = winSize.height / _sprBG->getContentSize().height;
	_sprBG->setScaleX(scaleX);
	_sprBG->setScaleY(scaleY);

	//add base
	_sprBase = Sprite::create("house.png");
	this->addChild(_sprBase);
	_sprBase->setScale(1.0f);
	_sprBase->setAnchorPoint(Vec2(0.0f, 0.0f));


	return true;
}