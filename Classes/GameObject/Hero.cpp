#include "Hero.h"
#include "Parameter.h"
#include "GameObject/PZombie.h"
#include "GameObject/SkillZombie.h"
#include "UI/EndGame/EndGame.h"

USING_NS_CC;

#define HEALTH_HERO  1.0f;

Hero::Hero()
{
	_health = HEALTH_HERO;
}

Hero::~Hero()
{

}
bool Hero::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	//add base
	_sprBase = Sprite::create("house.png");
	this->addChild(_sprBase);
	_sprBase->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprBase->setScale(winSize.height / _sprBase->getContentSize().height * 0.7f);

	_frameBloodBar = Sprite::create("OutLine.png");
	_frameBloodBar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_frameBloodBar->setPosition(Vec2(winSize.width * 0.05f, winSize.height * 0.94f));
	_frameBloodBar->setScale(
		(winSize.width / _frameBloodBar->getContentSize().width) * 0.25f,
		(winSize.height / _frameBloodBar->getContentSize().height) * 0.04f
	);
	addChild(_frameBloodBar, 1);

	_sprhero = Sprite::createWithSpriteFrameName("idle00.png");
	_sprhero->setScale(winSize.height / _sprhero->getContentSize().height * 0.15f);
	this->addChild(_sprhero);
	this->setTag(TAG_HERO);
	_sprhero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprhero->setPosition(Vec2(winSize.width * 0.14f,
		winSize.height * 0.17f));
	this->setHealthBar(100);

	_sprheroarm = Sprite::createWithSpriteFrameName("M16idle00.png");
	_sprhero->addChild(_sprheroarm);
	_sprheroarm->setName("Hero");
	_sprheroarm->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprheroarm->setPosition(_sprhero->getContentSize().width * 0.14f, _sprhero->getContentSize().height * 0.32f);

	auto physicForHero = PhysicsBody::createBox(Size(winSize.width * 0.3f, winSize.height * 0.7));
	physicForHero->setDynamic(false);
	physicForHero->setContactTestBitmask(true);
	physicForHero->setGroup(-2);
	physicForHero->setPositionOffset(Vec2(winSize.width * 0.20f, winSize.height * 0.375f));
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
void Hero::healHero()
{
	if (_health <= 50)
	{

		_health += 50;
	}
	else
	{
		_health = 100;
	}
}

void Hero::onCollission(GameObject *obj)
{
	if (obj->getTag() >= TAG_SKILL2 && obj->getTag() <= TAG_SKILL11)
	{
		this->_health -= 2.0f;
		this->updateHealthBar(_health);
	}
	else
	{
		PZombie *pzombie = static_cast<PZombie*>(obj);
		if (PZombie::damageOfZombie <= 0)
		{
			if (pzombie->getTag() == 100)
			{
				PZombie::damageOfZombie = DAMAGE_OF_BOSS;
			}
			else
			{
				PZombie::damageOfZombie = DAMAGE_OF_ZOMBIE2;
			}
			schedule(schedule_selector(Hero::heroWounded), 0.5f);
			_listZombieCollision.pushBack(pzombie);
			scheduleUpdate();
		}
		else if (PZombie::damageOfZombie > 0)
		{
			_listZombieCollision.pushBack(pzombie);
			if (pzombie->getTag() == 100)
			{
				PZombie::damageOfZombie += DAMAGE_OF_BOSS;
			}
			else
			{
				PZombie::damageOfZombie += DAMAGE_OF_ZOMBIE2;
			}
		}
	}
}

void Hero::heroWounded(float delta)
{
	if (PZombie::damageOfZombie <= 0)
	{
		_healthbarHero->stopAllActions();
	}
	else
	{
		this->_health -= PZombie::damageOfZombie;
	}
	this->updateHealthBar(_health);
	auto tintTo = TintTo::create(0.5f, 255, 50, 50);
	_healthbarHero->runAction(tintTo);
	if (this->_health <= 0)
	{
		this->getPhysicsBody()->setContactTestBitmask(false);
		this->unschedule(schedule_selector(Hero::heroWounded));
		if (_callback)
		{
			_callback();
		}
	}

}
void Hero::setCallBack(std::function<void()> callback)
{
	_callback = callback;
}

void Hero::setHealthBar(float percent)
{
	_healthbarHero = ui::LoadingBar::create("HeroBar.png");
	_healthbarHero->setPercent(percent);
	_frameBloodBar->addChild(_healthbarHero, 2);
	_healthbarHero->setDirection(ui::LoadingBar::Direction::LEFT);
	_healthbarHero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
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
		if (_listZombieCollision.at(index)->health <= 0)
		{
			PZombie::damageOfZombie -= 0.5f;
			_listZombieCollision.erase(index);
			if (_listZombieCollision.empty())
			{
				this->unschedule(schedule_selector(Hero::heroWounded));
				updateHealthBar(_health);
			}
		}
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

