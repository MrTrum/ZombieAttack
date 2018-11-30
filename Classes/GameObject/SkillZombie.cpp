﻿#include "PZombie.h"
#include "Parameter.h"
#include "GamePlayLayer.h"
#include "GameObject/SkillZombie.h"


USING_NS_CC;
#define TAG_SKILL 10;

SkillZombie::SkillZombie()
{
}

SkillZombie::~SkillZombie()
{
	CC_SAFE_RELEASE(_particle);
}


SkillZombie* SkillZombie::create(int tagZombie)
{
	SkillZombie *pRet = new(std::nothrow) SkillZombie();
	if (pRet && pRet->init(tagZombie))
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

bool SkillZombie::init(int tagZombie)
{
	if (!GameObject::init())
	{
		return false;
	}
	std::string skillName = StringUtils::format("Z%dSkill", tagZombie);
	_skill = Sprite::createWithSpriteFrameName(skillName + "1.png");
	this->addChild(_skill);

	auto physicSkill = PhysicsBody::createBox(_skill->getContentSize());
	physicSkill->setContactTestBitmask(true);
	physicSkill->setDynamic(false);
	physicSkill->setGroup(-1);
	this->setPhysicsBody(physicSkill);

	_particle = ParticleSystemQuad::create("skilldestroyed.plist");
	this->addChild(_particle);
	_particle->setScale(0.5f);
	_particle->setPosition(physicSkill->getPosition());
	_particle->retain();
	this->setTag(tagZombie + 10);
	playSkillAnimation(skillName);
	return true;
}

void SkillZombie::playSkillAnimation(std::string skillname)
{
	auto *animation = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		std::string numberSpriteSkill = StringUtils::format("%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(skillname + numberSpriteSkill));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);
	_skill->runAction(RepeatForever::create(animate));
}

void SkillZombie::fireSkill(Vec2 startPos, Vec2 targetPos)
{
	auto setPos =  CallFunc::create([=] 
	{
		this->setPosition(startPos.x - 10.0f, startPos.y - 15.0f);
		this->setVisible(true);
	});

	auto moveTo = MoveTo::create(1.0f, targetPos);

	auto callfunc = CallFunc::create([=]
	{
		this->removeFromParent();
		if (_skillzombie)
		{
			_skillzombie(this);
		}
	});
	auto sqe = Sequence::create(setPos, moveTo, callfunc, nullptr);
	this->runAction(sqe);
}

void SkillZombie::assignSkillToPoll(skillZombie skillzombie)
{
	_skillzombie = skillzombie;
}

void SkillZombie::onCollission(GameObject *obj)
{
	if (obj != nullptr)
	{
		cocos2d::log("WTF");
	}
	if (obj->getTag() == TAG_BULLET)
	{

		auto start = CallFunc::create([=] {
			_particle->start();
		});
		auto stop = CallFunc::create([=] {
			_particle->stop();
			this->removeFromParent();
			_particle->removeFromParent();
		});
		runAction(Sequence::create(start, DelayTime::create(0.2), stop, nullptr));
	}
}

void SkillZombie::setPosition(float x, float y)
{
	Node::setPosition(x, y);
}