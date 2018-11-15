#include "PZombie.h"
#include "Parameter.h"
#include "GamePlayLayer.h"
#include "PoolObject/PoolZombie.h"



USING_NS_CC;

PZombie::PZombie() :
	damage(DAMAGE_ZOMBIE2)
{
}

PZombie::~PZombie()
{
}

float PZombie::damageOfZombie = 0;

PZombie* PZombie::create(PoolZombie *ptr, std::string zombieName, int tag)
{
	PZombie *pRet = new(std::nothrow) PZombie();
	if (pRet && pRet->init(ptr, zombieName, tag))
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

bool PZombie::init(PoolZombie *ptr, std::string zombieName, int tag)
{
	if (!GameObject::init())
	{
		return false;
	}
	ptrPoolZombie = ptr;
	_tag = tag;
	_stringName = zombieName;

	_spr = Sprite::createWithSpriteFrameName(zombieName + "1.png");
	this->addChild(_spr);


	//Set Physics
	auto physics = PhysicsBody::createBox(_spr->getContentSize());
	physics->setContactTestBitmask(true);
	physics->setDynamic(false);
	physics->setGroup(1);
	this->setPhysicsBody(physics);

	this->setTag(tag);

	playWalkAnimation(zombieName);
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
	if (this->health <= 0)
	{
		auto deadPos = this->getPosition();
		this->getPhysicsBody()->setContactTestBitmask(false);
		auto stringname = convertFromTagToStringDead(this->getTag());
		this->playDeadAnimation(deadPos, stringname);
	}
}

void PZombie::attack()
{
	auto stringName = convertFromTagToStringAttack(this->getTag());
	playAttackAnimation(stringName);
}

void PZombie::reset()
{
	auto stringName = convertFromTagToStringWalk(this->getTag());
	playWalkAnimation(stringName);
}

void PZombie::playWalkAnimation(std::string zombieName)
{
	_spr->stopAllActions();
	auto *animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string zombiename = StringUtils::format("%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(zombieName + zombiename));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);
	_spr->runAction(RepeatForever::create(animate));
}

void PZombie::setGamePlayLayerPtr(GamePlayLayer* ptr)
{
	ptrGamePlayLayer = ptr;
}
void PZombie::playDeadAnimation(Vec2 deadPos, std::string stringname)
{
	_spr->stopAllActions();
	_spr->setSpriteFrame(stringname + "1.png");
	auto *animation = Animation::create();
	for (int i = 1; i < 9; i++)
	{
		std::string Z2Walk = StringUtils::format("%i.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(stringname + Z2Walk));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);

	auto *animate = Animate::create(animation);
	auto *zombieBackPool = CallFunc::create([=]
	{
		this->getPhysicsBody()->setContactTestBitmask(true);
		this->setVisible(false);
		this->droppedItems(deadPos);
		this->removeFromParent();
		this->reset();
	});
	auto squ = Sequence::create(animate, zombieBackPool, nullptr);
	_spr->runAction(squ);
	ptrGamePlayLayer->CoinFly(deadPos);
}

void PZombie::droppedItems(Vec2 deadPos)
{
	if (this->getTag() == 4 || this->getTag() == 5)
	{
		int randomItem = random(1, 100);
		if (this->getTag() == 4)
		{
			if (randomItem <= 20)									// Xác xuất 20% rơi ra đạn M4A1 x15
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
			else if (randomItem > 20 && randomItem <= 40)			// Xác xuất 20% rơi ra đạn lửa x15
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
			else if (randomItem > 40 && randomItem <= 50)			// Xác xuất 10% rơi ra đạn M4A1 x30
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
			else if (randomItem > 50 && randomItem <= 60)			// Xác xuất 10% rơi ra đạn lửa x30
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
			else if (randomItem > 60 && randomItem <= 65)			// Xác xuất 5% rơi ra đạn M4A1 x60
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
			else if (randomItem > 65 && randomItem <= 70)			// Xác xuất 5% rơi ra đạn lửa x60
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
			else if (randomItem > 70 && randomItem <= 75)			// Xác xuất 5% rơi ra skill bơm
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
			else if (randomItem > 75 && randomItem <= 80)			// Xác xuất 5% rơi ra skill băng
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
		}
		else if (this->getTag() == 5)
		{
			if (randomItem > 80 && randomItem <= 85)				// Xác xuất 5% rơi ra đạn M4A1 x120 và 1 suất nâng cấp súng cùng loại
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
			else if (randomItem > 85 && randomItem <= 90)			// Xác xuất 5% rơi ra đạn lửa x120 và 1 suất nâng cấp súng cùng loại
			{
				ptrGamePlayLayer->createItems(randomItem, deadPos);
			}
		}
	}

	if (ptrPoolZombie->checkTheLastZombie())
	{
		ptrGamePlayLayer->createGoldBag(deadPos);
	}
}


void PZombie::playAttackAnimation(std::string stringname)
{
	_spr->stopAllActions();
	_spr->setSpriteFrame(stringname + "1.png");
	auto *animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string zombieName = StringUtils::format("%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(stringname + zombieName));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);
	_spr->runAction(RepeatForever::create(animate));
}

std::string	PZombie::convertFromTagToStringWalk(int tag)
{
	std::string stringName = StringUtils::format("Z%dWalk", tag);
	return stringName;
}

std::string	PZombie::convertFromTagToStringAttack(int tag)
{
	std::string stringName = StringUtils::format("Z%dAttack", tag);
	return stringName;
}

std::string	PZombie::convertFromTagToStringDead(int tag)
{
	std::string stringName = StringUtils::format("Z%dDead", tag);
	return stringName;
}