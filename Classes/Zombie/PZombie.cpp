#include "PZombie.h"
#include "Parameter.h"
#include "GamePlayLayer.h"
#include "PoolObject/PoolZombie.h"



USING_NS_CC;

PZombie::PZombie() : 
	health(HEALTH_ZOMBIE2),
	damage(DAMAGE_ZOMBIE2)
{
}

PZombie::~PZombie()
{
}

float PZombie::damageOfZombie = 0;

PZombie* PZombie::create(PoolZombie *ptr)
{
	PZombie *pRet = new(std::nothrow) PZombie();
	if (pRet && pRet->init(ptr))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool PZombie::init(PoolZombie *ptr)
{
	if (!GameObject::init())
	{
		return false;
	}
	ptrPoolZombie = ptr;

	std::string zombieName = "Z2Walk";
	_spr = Sprite::createWithSpriteFrameName(zombieName + "1.png");
	this->addChild(_spr);


	//Set Physics
	auto physics = PhysicsBody::createBox(_spr->getContentSize());
	physics->setContactTestBitmask(true);
	physics->setDynamic(false);
	physics->setGroup(1);
	this->setPhysicsBody(physics);

	this->setTag(TAG_ZOMBIE);

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

float PZombie::getHealthBar()
{
	return this->health;
}

void PZombie::updateHealthBar(float percent)
{
	healthbarZombie->removeFromParent();
	setHealthBar(percent);
}

void PZombie::onCollission(GameObject *obj)
{
	if (obj->getTag() == TAG_LINE || obj->getTag() == TAG_HERO || obj->getTag() == TAG_BULLET)
	{
		this->dead();
	}
	else if (obj->getTag() == TAG_LINE2)
	{
		this->attack();
	}
}

void PZombie::dead()
{
	this->health -= this->damage;
	this->updateHealthBar(this->health);
	if (this->health == 0)
	{
		//Tú đã sửa
		auto deadPos = this->getPosition();
		this->getPhysicsBody()->setContactTestBitmask(false);
		this->playDeadAnimation(deadPos);
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
	_spr->runAction(RepeatForever::create(animate));
}
//Tú đã sửa
void PZombie::setGamePlayLayerPtr(GamePlayLayer* ptr)
{
	ptrGamePlayLayer = ptr;
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
		this->getPhysicsBody()->setContactTestBitmask(true);
		this->setVisible(false);
		if (ptrPoolZombie->checkTheLastZombie())
		{
			ptrGamePlayLayer->createGoldBag(deadPos);
		}
		this->removeFromParent();
		this->reset();
	});
	auto squ = Sequence::create(animate, zombieBackPool, nullptr);
	_spr->runAction(squ);
	ptrGamePlayLayer->CoinFly(deadPos);
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
