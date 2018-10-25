#include "Coin.h"
int Coin::_totalVal = 0;
USING_NS_CC;

Coin::Coin()
{
}

Coin::~Coin()
{
}
bool Coin::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/coin.plist",
		"images/coin.png");
	_Coin = Sprite::createWithSpriteFrameName("coin_0.png");
	_Coin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Coin->setPosition(Vec2(winSize*0.5f));
	_Coin->setScale(0.7f);
	this->addChild(_Coin,2);
	return true;
}
void Coin::PlayAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 0; i < 4; i++)
	{
		std::string name = StringUtils::format("coin_%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_Coin->runAction(RepeatForever::create(animate));
}
bool Coin::FlyAnimation()
{
	Size winSize = Director::getInstance()->getWinSize();
	MoveTo* coinFly = MoveTo::create(0.5f,Vec2(winSize.width*0.24f, winSize.height*0.975f));
	_Coin->runAction(coinFly);
	return true;
}
void Coin::update(float dt)
{

}