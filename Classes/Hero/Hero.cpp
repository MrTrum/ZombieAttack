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
	{Hero::AnimationType::IDLE, AnimationInfo("idle%02.png",16,8,CC_REPEAT_FOREVER)}
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
	this->setTag(HERO_TAG);
	_sprhero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setContentSize(_sprhero->getContentSize());
	_sprhero->setScale(1.0f);
	this->setHealthBar(100);

	auto physicForHero = PhysicsBody::createBox(_sprhero->getContentSize() * 2.0f);
	physicForHero->setDynamic(false);
	physicForHero->setContactTestBitmask(true);
	physicForHero->setGroup(-2);
	this->setPhysicsBody(physicForHero);
	playAnimation(AnimationType::IDLE);
	/*Animation* fatguyanim = Animation::create();

	for (int i = 0; i < 8; i++)
	{
		std::string name = StringUtils::format("Redneck%d.png", i);
		fatguyanim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	fatguyanim->setDelayPerUnit(1 / 4.0f);
	Animate* animate = Animate::create(fatguyanim);
	_sprhero->runAction(RepeatForever::create(animate));*/

	return true;
}

void Hero::onCollission(GameObject *obj)
{
	if (obj->getTag() == ZOMBIE_TAG && PZombie::damageOfZombie <= 0)
	{
		PZombie::damageOfZombie = DAMAGE_OF_ZOMBIE2;
		scheduleOnce(schedule_selector(Hero::heroWounded), 0.0f);
		schedule(schedule_selector(Hero::heroWounded), 0.5f);
		theHealthOfZombiesAreAttacking(obj);
	}
	else if (obj->getTag() == ZOMBIE_TAG && PZombie::damageOfZombie > 0)
	{
		PZombie::damageOfZombie += 0.5;
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
	if (this->_health <= 0)
	{
		CCLOG("Dead");
	}
}

void Hero::theHealthOfZombiesAreAttacking(GameObject *obj)
{
	PZombie *pZombie = static_cast<PZombie*>(obj);
	if (pZombie->getHealthBar() <= 0)
	{
		PZombie::damageOfZombie -= 0.5;
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
	auto tintTo = TintTo::create(0.5f, 255, 50, 50);
	_healthbarHero->runAction(tintTo);
}


void Hero::shootAnimation()
{
	Size winSize = Director::getInstance()->getWinSize();
	Animation* animation = Animation::create();

	for (int i = 1; i < 11; i++)
	{
		std::string name = StringUtils::format("fireSG%02d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(1 / 30.0f);
	Animate* animate = Animate::create(animation);
	_sprhero->runAction(animate);
}

void Hero::playAnimation(AnimationInfo info)
{
	cocos2d::Animation* charAnimation = cocos2d::AnimationCache::getInstance()->getAnimation(info._name);
	if (charAnimation == NULL) {
		cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
		for (int i = 0; i < info._numframe; i++) {
			cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(info._name.c_str(), i)->getCString());
			if (frame == nullptr || frame == (void*)0x1)
			{
				continue;
			}
			else
			{
				animFrames.pushBack(frame);
			}
		}
		charAnimation = cocos2d::Animation::createWithSpriteFrames(animFrames, 1.0f / info._fps);
		cocos2d::AnimationCache::getInstance()->addAnimation(charAnimation, info._name);
	}
	auto sequenceAction = cocos2d::Sequence::create(Repeat::create(cocos2d::Animate::create(charAnimation), info._loop), nullptr);
	_sprhero->runAction(sequenceAction);
}

void Hero::playAnimation(AnimationType type)
{
	std::map<Hero::AnimationType, AnimationInfo>::iterator it = _mapAnimation.find(type);
	if (it != _mapAnimation.end())
	{
		playAnimation(it->second);
	}
}

//void Hero::playAnimation(std::string name, int numframe, int fps, int loop)
//{
//	cocos2d::Animation* charAnimation = cocos2d::AnimationCache::getInstance()->getAnimation(_name);
//	if (charAnimation == NULL) { 
//		cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
//		for (int i = 0; i < numframe; i++) {
//			cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat(_name.c_str(), i)->getCString());
//			if (frame == nullptr || frame == (void*)0x1)
//			{
//				continue;
//			}
//			else
//			{
//				animFrames.pushBack(frame);
//			}
//		}
//		charAnimation = cocos2d::Animation::createWithSpriteFrames(animFrames, 1.0f / fps);
//		cocos2d::AnimationCache::getInstance()->addAnimation(charAnimation, name);
//	}
//	auto sequenceAction = cocos2d::Sequence::create(Repeat::create(cocos2d::Animate::create(charAnimation), loop), nullptr);
//	_sprhero->runAction(sequenceAction);
//}