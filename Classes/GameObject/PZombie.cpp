#include "PZombie.h"
#include "Parameter.h"
#include "GamePlayLayer.h"
#include "PoolObject/PoolZombie.h"
#include "PoolObject/PoolSkill.h"


USING_NS_CC;


PZombie::PZombie() : _isDead(false)
{
	_poolSkill = new PoolSkill();
	for (int i = 0; i < 11; i++)
	{
		float constHealth = returnHealth(i);
		_listHealthZombie.push_back(constHealth);
	}
}

float PZombie::returnHealth(int i)
{
	float health = 0.0f;
	if (i == 0)
	{
		health = HEALTH_ZOMBIE2;
	}
	else if (i == 1)
	{
		health = HEALTH_ZOMBIE3;
	}
	else if (i == 2)
	{
		health = HEALTH_ZOMBIE4;
	}
	else if (i == 3)
	{
		health = HEALTH_ZOMBIE5;
	}
	else if (i == 4)
	{
		health = HEALTH_ZOMBIE6;
	}
	else if (i == 5)
	{
		health = HEALTH_ZOMBIE7;
	}
	else if (i == 6)
	{
		health = HEALTH_ZOMBIE8;
	}
	else if (i == 7)
	{
		health = HEALTH_ZOMBIE9;
	}
	else if (i == 8)
	{
		health = HEALTH_ZOMBIE10;
	}
	else if (i == 9)
	{
		health = HEALTH_ZOMBIE11;
	}
	else if (i == 10)
	{
		health = HEALTH_ZOMBIE100;
	}
	return health;
}

PZombie::~PZombie()
{
	CC_SAFE_DELETE(_poolSkill);
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
	auto physics = PhysicsBody::createBox(Size(_spr->getContentSize().width - 60.0f, _spr->getContentSize().height));
	physics->setContactTestBitmask(true);
	physics->setDynamic(false);
	physics->setGroup(-1);
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
	healthbarZombie->setName("HealthBar");
	healthbarZombie->setDirection(ui::LoadingBar::Direction::LEFT);
	healthbarZombie->setScaleX(0.35f);
	healthbarZombie->setScaleY(1.2f);
	healthbarZombie->setPercent(percent);
	healthbarZombie->setPosition(Vec2(0.0f, 200.0f));
}

void PZombie::resetHealthBar(float percent)
{
	healthbarZombie->removeFromParent();
	setHealthBar(percent);
}

void PZombie::updateHealthBar(float health, PZombie *ptrZombie)
{
	float percent = 0.0f;
	if (ptrZombie->getTag() == 2)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(0);
	}
	else if (ptrZombie->getTag() == 3)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(1);
	}
	else if (ptrZombie->getTag() == 4)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(2);
	}
	else if (ptrZombie->getTag() == 5)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(3);
	}
	else if (ptrZombie->getTag() == 6)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(4);
	}
	else if (ptrZombie->getTag() == 7)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(5);
	}
	else if (ptrZombie->getTag() == 8)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(6);
	}
	else if (ptrZombie->getTag() == 9)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(7);
	}
	else if (ptrZombie->getTag() == 10)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(8);
	}
	else if (ptrZombie->getTag() == 11)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(9);
	}
	else if (ptrZombie->getTag() == 100)
	{
		percent = (health * 100.0f) / _listHealthZombie.at(10);
	}
	healthbarZombie->setPercent(percent);
}

void PZombie::onCollission(GameObject *obj)
{
	auto objtag = obj->getTag();
	auto zombirtag = this->getTag();
	if (obj->getTag() == TAG_BULLET || obj->getTag() == TAG_DYNAMITE)
	{
		this->damage = obj->getDamage();
		checkDamage();
	}
	else if (obj->getTag() == TAG_LINE && (this->getTag() >= TAG_ZOMBIE6 && this->getTag() <= TAG_ZOMBIE11))
	{
		scheduleOnce(schedule_selector(PZombie::attackSkill), 0.0f);
	}
	else if (obj->getTag() == TAG_LINE2)
	{
		Attack();
	}
}

void PZombie::checkDamage()
{
	this->health -= this->damage;
	if (this->health <= 0)
	{
		this->stopActionByTag(TAG_ACTION_MOVETO_ZOMBIE);
		this->Dead();
	}
	this->updateHealthBar(this->health, this);
}

void PZombie::Dead()
{
	this->getPhysicsBody()->setContactTestBitmask(false);
	this->unschedule(schedule_selector(PZombie::attackAndFire));
	auto deadPos = this->getPosition();
	auto stringName = convertFromTagToStringDead(this->getTag());
	this->playDeadAnimation(deadPos, stringName);
}

void PZombie::Attack()
{
	if (_isDead == false)
	{
		auto stringName = convertFromTagToStringAttack(this->getTag());
		playAttackAnimation(stringName);
	}
}


void PZombie::Walk()
{
	auto stringName = convertFromTagToStringWalk(this->getTag());
	playWalkAnimation(stringName);
}

std::string	PZombie::convertFromTagToStringWalk(int tag)
{
	std::string stringName = StringUtils::format("Z%dWalk", tag);
	return stringName;
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

std::string	PZombie::convertFromTagToStringAttack(int tag)
{
	std::string stringName = StringUtils::format("Z%dAttack", tag);
	return stringName;
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
	auto repeatAnimate = RepeatForever::create(animate);
	repeatAnimate->setTag(TAG_ACTION_ATTACK_ZOMBIE);
	_spr->runAction(repeatAnimate);
}

std::string PZombie::convertFromTagToStringSkill(int tag)
{
	std::string stringName = StringUtils::format("Z%dSkill", tag);
	return stringName;
}


std::string	PZombie::convertFromTagToStringDead(int tag)
{
	std::string stringName = StringUtils::format("Z%dDead", tag);
	return stringName;
}

void PZombie::playDeadAnimation(Vec2 deadPos, std::string stringname)
{
	_isDead = true;
	_spr->stopAllActions();
	_spr->setSpriteFrame(stringname + "1.png");
	auto *animation = Animation::create();
	for (int i = 1; i < 9; i++)
	{
		std::string png = StringUtils::format("%i.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(stringname + png));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);

	auto *zombieBackPool = CallFunc::create([=]
	{
		this->getPhysicsBody()->setContactTestBitmask(true);
		this->setVisible(false);
		this->droppedItems(deadPos);
		this->removeFromParent();
		this->Walk();
	});
	auto callback = CallFunc::create([=]
	{
		_isDead = false;
	});
	auto squ = Sequence::create(animate, zombieBackPool, callback, nullptr);
	_spr->runAction(squ);
	ptrGamePlayLayer->CoinFly(deadPos);
}

void PZombie::attackSkill(float delta)
{
	auto stringName = convertFromTagToStringAttack(this->getTag());
	playAttackAnimation(stringName);

	auto playAttackAnimate = DelayTime::create(1.0f);

	auto fire = CallFunc::create([=]
	{
		scheduleOnce(schedule_selector(PZombie::attackAndFire), 0.0f);
	});

	auto waitScheduleOnce = DelayTime::create(0.0f);

	auto walk = CallFunc::create([=]
	{
		walkAndMove();
	});
	auto sqe = Sequence::create(playAttackAnimate, fire, waitScheduleOnce, walk, nullptr);
	this->runAction(sqe);
}

void PZombie::attackAndFire(float delta)
{
	_skill = _poolSkill->createSkill(this->getTag());
	ptrGamePlayLayer->addChild(_skill);

	// calculate start fire pos
	auto worldPosZombie = this->getParent()->convertToWorldSpace(this->getPosition());
	auto startFirePos = ptrGamePlayLayer->convertToNodeSpace(worldPosZombie);

	// calculate target pos
	auto winSize = Director::getInstance()->getWinSize();
	auto worldPosHero = this->getParent()->convertToWorldSpace(Vec2(winSize.width * 0.25f, winSize.height * 0.25f));
	auto targetFirePos = ptrGamePlayLayer->convertToNodeSpace(worldPosHero);

	float speedFire;
	if (startFirePos.x >= winSize.width * 0.8f)
	{
		speedFire = 1.0f;
	}
	else
	{
		speedFire = 0.5f;
	}
	_skill->fireSkill(speedFire, startFirePos, targetFirePos);
}

void PZombie::walkAndMove()
{
	this->stopActionByTag(TAG_ACTION_ATTACK_ZOMBIE); // stop action Attack
	auto stringName = convertFromTagToStringWalk(this->getTag());
	this->playWalkAnimation(stringName);
	int speed = _target.x / TIME_MOVETO_ZOMBIE_SKILL;
	int distance = this->getPositionX() - _target.x;
	float time = distance / speed - 2.0f;

	auto move = CallFunc::create([=]
	{
		this->Move(time, _target);
	});
	auto fire = CallFunc::create([=]
	{
		Attack();
		schedule(schedule_selector(PZombie::attackAndFire), 1.0f);
	});
	this->runAction(Sequence::create(move, DelayTime::create(time), fire, nullptr));
}

void PZombie::Move(float time, Vec2& target)
{
	_target = target;
	this->stopActionByTag(TAG_ACTION_MOVETO_ZOMBIE);
	auto moveto = MoveTo::create(time, target);
	moveto->setTag(TAG_ACTION_MOVETO_ZOMBIE);
	this->runAction(moveto);
}

void PZombie::setGamePlayLayerPtr(GamePlayLayer* ptr)
{
	ptrGamePlayLayer = ptr;
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

