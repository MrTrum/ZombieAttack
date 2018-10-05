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

	_sprBG = Sprite::create("BG.png");
	this->addChild(_sprBG);
	_sprBG->setPosition(winSize * 0.5f);

	float scaleX = winSize.width / _sprBG->getContentSize().width;
	float scaleY = winSize.height / _sprBG->getContentSize().height;
	_sprBG->setScaleX(scaleX);
	_sprBG->setScaleY(scaleY);

	return true;
}