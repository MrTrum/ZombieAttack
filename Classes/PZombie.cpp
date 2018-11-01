﻿#include "PZombie.h"
#include "Parameter.h"
#include "GamePlayLayer.h"


USING_NS_CC;

PZombie::PZombie()
{
}

PZombie::~PZombie()
{
}

bool PZombie::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	std::string zombieName = "Z2Walk";
	_spr = Sprite::createWithSpriteFrameName(zombieName + "1.png");
	addChild(_spr);


	//Set Physics
	auto physics = PhysicsBody::createBox(_spr->getContentSize());
	physics->setContactTestBitmask(true);
	physics->setDynamic(false);
	physics->setGroup(-1);
	this->setPhysicsBody(physics);

	this->setTag(ZOMBIE_TAG);

	playWalkAnimation();
	return true;
}

void PZombie::setHealthBar(float percent)
{
	auto winSize = Director::getInstance()->getWinSize();

	healthbarZombie = ui::LoadingBar::create("HealthBar.png");
	this->addChild(healthbarZombie);
	healthbarZombie->setDirection(ui::LoadingBar::Direction::LEFT);
	healthbarZombie->setScaleX(0.25f);
	healthbarZombie->setScaleY(1.2f);
	healthbarZombie->setPercent(percent);
	healthbarZombie->setPosition(Vec2(0.0f, 200.0f));
}

void PZombie::getHealthBar(float percent)
{
	setHealthBar(percent);
}

void PZombie::updateHealthBar(float percent)
{
	healthbarZombie->removeFromParent();
	setHealthBar(percent);
}


void PZombie::dead()
{
	this->_health = this->_health - _damge;
	this->updateHealthBar(this->_health);
	if (this->_health == 0)
	{
		auto deadPos = this->getPosition();
		//Tú đã sửa
		playDeadAnimation(deadPos);
		
		this->updateHealthBar(this->_health);
		this->_health = HEALTH_ZOMBIE2;
	}
}

void PZombie::attack()
{
	playAttackAnimation();
}

void PZombie::reset()
{
	playWalkAnimation();
}

void PZombie::playWalkAnimation()
{
	_spr->stopAllActions();
	auto *animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string zombieName = StringUtils::format("Z2Walk%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(zombieName));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);
	_spr->runAction(Repeat::create(animate, TIME_REPEAT_ANIMATE));
}
//Tú đã sửa
void PZombie::setGamePlayLayerPtr(GamePlayLayer* ptr)
{
	_coinFunc = ptr;
}
void PZombie::playDeadAnimation(Vec2 deadPos)
{
	
	_spr->stopAllActions();
	_spr->setSpriteFrame("Z2Dead1.png");
	auto *animation = Animation::create();
	for (int i = 1; i < 9; i++)
	{
		std::string Z2Walk = StringUtils::format("Z2Dead%i.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Z2Walk));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);

	auto *animate = Animate::create(animation);
	auto *zombieBackPool = CallFunc::create([=]
	{
		auto winSize = Director::getInstance()->getWinSize();
		this->setVisible(false);
		this->removeFromParent();
		this->reset();
	});
	auto squ = Sequence::create(animate, DelayTime::create(0.5f), zombieBackPool, nullptr);
	_spr->runAction(squ);
	//Tú đã sửa
	_coinFunc->CoinFly(deadPos);
}

void PZombie::playAttackAnimation()
{
	_spr->stopAllActions();
	_spr->setSpriteFrame("Z2Attack1.png");
	auto *animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string zombieName = StringUtils::format("Z2Attack%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(zombieName));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);
	_spr->runAction(RepeatForever::create(animate));

}
