#include "UI/Coin/Coin.h"

USING_NS_CC;

int Coin::_totalVal = 0;
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

	_Coin = Sprite::createWithSpriteFrameName("coin0.png");
	_Coin->setScale(0.15f);
	this->addChild(_Coin);
	return true;
}
void Coin::PlayAnimation()
{
	Animation* animation = Animation::create();
	for (int i = 0; i < 4; i++)
	{
		std::string name = StringUtils::format("coin%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 12.0f);

	Animate* animate = Animate::create(animation);
	_Coin->runAction(RepeatForever::create(animate));
}
bool Coin::FlyAnimation(cocos2d::Vec2 iconPos, std::function<void()> callback)
{
	_callback = callback;
	Size winSize = Director::getInstance()->getWinSize();
	MoveTo* coinFly = MoveTo::create(0.5f,Vec2(iconPos));
	auto callfunc = CallFunc::create([=]
	{
		if (_callback)
		{
			_callback();
		}
		this->removeFromParent();
	});
	Sequence* seq = Sequence::create(DelayTime::create(0.3f), coinFly, callfunc, nullptr);
	this->runAction(seq);
	return true;
}
void Coin::update(float dt)
{

}