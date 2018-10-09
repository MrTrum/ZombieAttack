﻿#include "Zombie.h"
#include "SimpleAudioEngine.h"
#include "Parameter.h"


USING_NS_CC;

Size		winSize;

Node* Zombie::createNode()
{
	return Zombie::create();
}


bool Zombie::init()
{
	if (!Node::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();

	scheduleOnce(schedule_selector(Zombie::createPools), 1.0f);
	schedule(schedule_selector(Zombie::createZombie_2), TIME_CREATE_ZOMBIE_2);
	/*schedule(schedule_selector(Zombie::createZombie_3), TIME_CREATE_ZOMBIE_3);
	schedule(schedule_selector(Zombie::createZombie_4), TIME_CREATE_ZOMBIE_4);
	schedule(schedule_selector(Zombie::createZombie_5), TIME_CREATE_ZOMBIE_5);*/


	physicsForLine();

	auto listenerContact = EventListenerPhysicsContact::create();
	listenerContact->onContactBegin = CC_CALLBACK_1(Zombie::onContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerContact, this);


	return true;
}

void Zombie::createPools(float unknown)
{
	Sprite *sprite;
	_Zombie2 = new Vector<Sprite*>(5);
	
	for (int indexZombie = 0; indexZombie < 5; indexZombie++)
	{
		sprite = Sprite::createWithSpriteFrameName("Z2Walk1.png");
		sprite->setVisible(false);
		addChild(sprite);
		_Zombie2->pushBack(sprite);
	}
}

int i = 0;
void Zombie::createZombie_2(float unknown)
{
	//Zombie 2
	/*zomBie2 = Sprite::createWithSpriteFrameName("Z2Walk1.png");*/
	if (i < 5)
	{
		_Zombie2->at(i)->stopAllActions();
		_Zombie2->at(i)->setPosition(winSize.width, 0.0);
		_Zombie2->at(i)->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		_Zombie2->at(i)->setScale(0.15f);
		_Zombie2->at(i)->setTag(ZOMBIE_TAG);
		/*_Zombie2->at(i)->retain();*/


		//Set Physics
		auto physics = PhysicsBody::createBox(_Zombie2->at(i)->getContentSize());
		physics->setCollisionBitmask(ZOMBIE_BITMASK);
		physics->setContactTestBitmask(true);
		physics->setDynamic(false);
		_Zombie2->at(i)->setPhysicsBody(physics);

		/*addChild(zomBie2, 6);*/
		//Diễn hoạt cho Zombie 2
		auto *animation = Animation::create();
		for (int i = 1; i < 7; i++)
		{
			std::string zombieName = StringUtils::format("Z2Walk%d.png", i);
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(zombieName));
		}
		animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
		auto *animate = Animate::create(animation);



		//Move zombie 2
		_Zombie2->at(i)->setVisible(true);
		auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * LOCAL_MOVETO, 0.0));
		auto spawn = Spawn::create(Repeat::create(animate, TIME_REPEAT_ANIMATE), moveto, nullptr);
		_Zombie2->at(i)->runAction(spawn);
		i++;
	}
	if (i >= 4)
	{
		i = 0;
	}
}

void Zombie::physicsForLine()
{
	auto linePhysics = Node::create();
	addChild(linePhysics);
	linePhysics->setPosition(winSize.width * 0.1, 0.0);

	auto physicsForLine = PhysicsBody::createBox(Size(1, winSize.height * 0.5));
	physicsForLine->setCollisionBitmask(LINE_BITMASK);
	physicsForLine->setContactTestBitmask(true);
	physicsForLine->setDynamic(false);
	linePhysics->setPhysicsBody(physicsForLine);
}

bool Zombie::onContactBegan(PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == ZOMBIE_BITMASK && b->getCollisionBitmask() == LINE_BITMASK ||
		a->getCollisionBitmask() == LINE_BITMASK && b->getCollisionBitmask() == ZOMBIE_BITMASK);
	{
		_Zombie2->at(i)->removeChildByTag(ZOMBIE_TAG);
	}

	return true;
}

void Zombie::createZombie_3(float unknown)
{
	//Zombie 3
	auto zomBie3 = Sprite::createWithSpriteFrameName("Z3Walk1.png");
	addChild(zomBie3, 5);
	zomBie3->setPosition(winSize.width, winSize.height * HEIGHT_POSITION_Z3);
	zomBie3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	zomBie3->setScale(winSize.width * ZOMBIE_SIZE_WIDTH, winSize.height * ZOMBIE_SIZE_HEIGHT);

	//Diễn hoạt cho Zombie 3
	auto *animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string zombieName = StringUtils::format("Z3Walk%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(zombieName));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);


	//Move zombie 3
	auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * LOCAL_MOVETO, winSize.height * HEIGHT_POSITION_Z3));
	auto spawn = Spawn::create(Repeat::create(animate, TIME_REPEAT_ANIMATE), moveto, nullptr);
	zomBie3->runAction(spawn);

}

void Zombie::createZombie_4(float unknown)
{
	//Zombie 4
	auto zomBie4 = Sprite::createWithSpriteFrameName("Z4Walk1.png");
	addChild(zomBie4, 4);
	zomBie4->setPosition(winSize.width, winSize.height * HEIGHT_POSITION_Z4);
	zomBie4->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	zomBie4->setScale(winSize.width * ZOMBIE_SIZE_WIDTH, winSize.height * ZOMBIE_SIZE_HEIGHT);

	//Diễn hoạt cho Zombie 4
	auto *animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string zombieName = StringUtils::format("Z4Walk%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(zombieName));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);


	//Move zombie 4
	auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * LOCAL_MOVETO, winSize.height * HEIGHT_POSITION_Z4));
	auto spawn = Spawn::create(Repeat::create(animate, TIME_REPEAT_ANIMATE), moveto, nullptr);
	zomBie4->runAction(spawn);
}

void Zombie::createZombie_5(float unknown)
{
	//Zombie 5
	auto zomBie5 = Sprite::createWithSpriteFrameName("Z5Walk1.png");
	addChild(zomBie5, 3);
	zomBie5->setPosition(winSize.width, winSize.height * HEIGHT_POSITION_Z5);
	zomBie5->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	zomBie5->setScale(winSize.width * ZOMBIE_SIZE_WIDTH, winSize.height * ZOMBIE_SIZE_HEIGHT);

	//Diễn hoạt cho Zombie 5
	auto *animation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		std::string zombieName = StringUtils::format("Z5Walk%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(zombieName));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto *animate = Animate::create(animation);


	//Move zombie 5
	auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * LOCAL_MOVETO, winSize.height * HEIGHT_POSITION_Z5));
	auto spawn = Spawn::create(Repeat::create(animate, TIME_REPEAT_ANIMATE), moveto, nullptr);
	zomBie5->runAction(spawn);
}
