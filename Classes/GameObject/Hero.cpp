#include "Hero.h"
#include "Parameter.h"
#include "GameObject/PZombie.h"

USING_NS_CC;

#define HEALTH_HERO  100.0f;

Hero::Hero()
{
	_health = HEALTH_HERO;
}

Hero::~Hero()
{

}

std::map<Hero::AnimationType, AnimationInfo> Hero::_mapAnimation =
{
	{Hero::AnimationType::IDLE, AnimationInfo("idle%02.png",16,4,CC_REPEAT_FOREVER)}
};

bool Hero::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();

	auto frameBloodBar = Sprite::create("BloodBarHero.png");
	frameBloodBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	frameBloodBar->setPosition(Vec2(90.0f, 520.0f));
	frameBloodBar->setScaleY(0.17f);
	frameBloodBar->setScaleX(0.25f);
	addChild(frameBloodBar, 1);

	_sprhero = Sprite::createWithSpriteFrameName("idle00.png");
	this->addChild(_sprhero);
	this->setTag(TAG_HERO);
	_sprhero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setContentSize(_sprhero->getContentSize());
	_sprhero->setScale(1.0f);
	this->setHealthBar(100);

	_sprheroarm = Sprite::createWithSpriteFrameName("M16idle00.png");
	addChild(_sprheroarm);
	_sprheroarm->setName("Hero");
	_sprheroarm->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprheroarm->setPosition(winSize.width * 0.015f, winSize.height * 0.06f);

	auto physicForHero = PhysicsBody::createBox(_sprhero->getContentSize() * 2.5f);
	physicForHero->setDynamic(false);
	physicForHero->setContactTestBitmask(true);
	physicForHero->setGroup(-2);
	this->setPhysicsBody(physicForHero);

	Animation* fatguyanim = Animation::create();
	for (int i = 0; i < 16; i++)
	{
		std::string heroAnimName = StringUtils::format("idle%02d.png", i);
		fatguyanim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(heroAnimName));
	}
	fatguyanim->setDelayPerUnit(1 / 4.0f);
	Animate* bodyAnimate = Animate::create(fatguyanim);
	_sprhero->runAction(RepeatForever::create(bodyAnimate));

	Animation *fatguyarm = Animation::create();
	for (int j = 0; j < 16; j++)
	{
		std::string armAnimName = StringUtils::format("M16idle%02d.png", j);
		fatguyarm->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(armAnimName));
	}
	fatguyarm->setDelayPerUnit(1 / 4.0f);
	Animate *armAnimate = Animate::create(fatguyarm);
	_sprheroarm->runAction(RepeatForever::create(armAnimate));

	return true;
}

void Hero::onCollission(GameObject *obj)
{
	PZombie *pzombie = static_cast<PZombie*>(obj);
	if (PZombie::damageOfZombie <= 0)
	{
		PZombie::damageOfZombie = DAMAGE_OF_ZOMBIE2;
		schedule(schedule_selector(Hero::heroWounded), 0.5f);
		_listZombieCollision.pushBack(pzombie);
		scheduleUpdate();
	}
	else if (PZombie::damageOfZombie > 0)
	{
		_listZombieCollision.pushBack(pzombie);
		PZombie::damageOfZombie += DAMAGE_OF_ZOMBIE2;
	}
}

void Hero::heroWounded(float delta)
{
	if (PZombie::damageOfZombie <= 0)
	{
		_healthbarHero->stopAllActions();
	}
	this->_health -= PZombie::damageOfZombie;
	this->updateHealthBar(_health);

	auto tintTo = TintTo::create(0.5f, 255, 50, 50);
	_healthbarHero->runAction(tintTo);

	if (this->_health <= 0)
	{
		CCLOG("Dead");
	}
}


void Hero::setHealthBar(float percent)
{
	_healthbarHero = ui::LoadingBar::create("HeroBar.png");
	this->addChild(_healthbarHero, 2);
	_healthbarHero->setDirection(ui::LoadingBar::Direction::LEFT);
	_healthbarHero->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	_healthbarHero->setScaleX(0.26f);
	_healthbarHero->setScaleY(0.20f);
	_healthbarHero->setPercent(percent);
	_healthbarHero->setPosition(Vec2(89.0f, 520.0f));
}

void Hero::updateHealthBar(float percent)
{
	_healthbarHero->removeFromParent();
	setHealthBar(percent);
}

void Hero::update(float delta)
{
	for (int index = 0; index < _listZombieCollision.size(); index++)
	{
		if (_listZombieCollision.at(index)->health == 0)
		{
			PZombie::damageOfZombie -= 0.5f;
			_listZombieCollision.erase(index);
		}
	}
	if (_listZombieCollision.size() == 0)
	{
		this->unschedule(schedule_selector(Hero::heroWounded));
		_healthbarHero->stopAllActions();
		updateHealthBar(_health);
	}
}

void Hero::shootAnimation()
{
	Animation *fatguyarm = Animation::create();
	for (int j = 0; j < 3; j++)
	{
		std::string armAnimName = StringUtils::format("M16firing%02d.png", j);
		fatguyarm->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(armAnimName));
	}
	fatguyarm->setDelayPerUnit(1 / 40.0f);
	Animate *armAnimate = Animate::create(fatguyarm);
	_sprheroarm->runAction(armAnimate);
}

