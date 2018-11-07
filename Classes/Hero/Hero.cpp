#include "Hero.h"
#include "Parameter.h"
#include "Zombie/PZombie.h"

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
	{Hero::AnimationType::IDLE, AnimationInfo("idle%2d.png",1,6,CC_REPEAT_FOREVER)}
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

	_sprhero = Sprite::createWithSpriteFrameName("Redneck0.png");
	this->addChild(_sprhero);
	this->setTag(TAG_HERO);
	_sprhero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setContentSize(_sprhero->getContentSize());
	_sprhero->setScale(1.0f);
	this->setHealthBar(100);

	_sprheroarm = Sprite::createWithSpriteFrameName("SGidle00.png");
	addChild(_sprheroarm);
	_sprheroarm->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprheroarm->setPosition(winSize.width * 0.015f, winSize.height * 0.06f);

	auto physicForHero = PhysicsBody::createBox(_sprhero->getContentSize() * 2.0f);
	physicForHero->setDynamic(false);
	physicForHero->setContactTestBitmask(true);
	physicForHero->setGroup(-2);
	this->setPhysicsBody(physicForHero);

	Animation* fatguyanim = Animation::create();

	for (int i = 0; i < 8; i++)
	{
		std::string heroAnimName = StringUtils::format("idle%02d.png", i);
		fatguyanim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(heroAnimName));
	}
	fatguyanim->setDelayPerUnit(1 / 4.0f);


	Animation *fatguyarm = Animation::create();
	for (int j = 0; j < 16; j++)
	{
		std::string armAnimName = StringUtils::format("SGidle%02d.png", j);
		fatguyarm->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(armAnimName));
	}
	fatguyarm->setDelayPerUnit(1 / 4.0f);
	Animate *armAnimate = Animate::create(fatguyarm);
	_sprheroarm->runAction(RepeatForever::create(armAnimate));
	#pragma endregion

	return true;
}

void Hero::onCollission(GameObject *obj)
{
	PZombie *pzombie = static_cast<PZombie*>(obj);
	if (obj->getTag() == ZOMBIE_TAG && PZombie::damageOfZombie <= 0)
	{
		PZombie::damageOfZombie = DAMAGE_OF_ZOMBIE2;
		schedule(schedule_selector(Hero::heroWounded), 0.5f);
		_listZombieCollision.pushBack(pzombie);
		scheduleUpdate();
	}
	else if (obj->getTag() == TAG_ZOMBIE && PZombie::damageOfZombie > 0)
	{
		_listZombieCollision.pushBack(pzombie);
		PZombie::damageOfZombie += 0.5;
	}
}

void Hero::heroWounded(float delta)
{
	this->_health -= PZombie::damageOfZombie;
	this->updateHealthBar(_health);
	auto tintTo = TintTo::create(0.5f, 255, 50, 50);
	_healthbarHero->runAction(tintTo);
	if (this->_health <= 0)
	{
		CCLOG("Dead");
	}
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

void Hero::setHealthBar(float percent)
{
	auto winSize = Director::getInstance()->getWinSize();

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

void Hero::shootAnimation()
{
	Animation *fatguyarm = Animation::create();
	for (int j = 0; j < 10; j++)
	{
		std::string armAnimName = StringUtils::format("fireSG%02d.png", j);
		fatguyarm->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(armAnimName));
	}
	fatguyarm->setDelayPerUnit(1 / 45.0f);
	Animate *armAnimate = Animate::create(fatguyarm);
	_sprheroarm->runAction(armAnimate);
}

void Hero::playAnimation(AnimationInfo info)
{
	Animation* animation = Animation::create();
	for (int i = 0; i < info._numframe; i++)
	{
		std::string name = StringUtils::format("%02d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(info._name + name));
	}
	animation->setDelayPerUnit(1 / info._fps);
	Animate* animate = Animate::create(animation);
	_sprhero->runAction(animate);
}

void Hero::playAnimation(std::string name, int numframe, int fps, int loop)
{
	cocos2d::Animation* charAnimation = cocos2d::AnimationCache::getInstance()->getAnimation(_name);
	if (charAnimation == NULL) { // not in cached yet
		cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
		for (int i = 0; i < numframe; i++) {
			cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(_name.c_str(), i)->getCString());
			if (frame == nullptr || frame == (void*)0x1)
			{
				continue;
			}
			else
			{
				animFrames.pushBack(frame);
			}
		}
		charAnimation = cocos2d::Animation::createWithSpriteFrames(animFrames, 1.0f / fps);
		cocos2d::AnimationCache::getInstance()->addAnimation(charAnimation, name);
	}
	auto sequenceAction = cocos2d::Sequence::create(Repeat::create(cocos2d::Animate::create(charAnimation), loop), nullptr);
	_sprhero->runAction(sequenceAction);
}