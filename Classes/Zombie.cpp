﻿#include "Zombie.h"
#include "SimpleAudioEngine.h"
#include "Parameter.h"
#include "cocos2d.h"


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

	scheduleOnce(schedule_selector(Zombie::createPools), 0.1f);
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

//Tại đây tạo pool hay gọi dễ nhớ là Kho nhé
void Zombie::createPools(float delta)
{
	_Zombie2 = new Vector<Sprite*>(ZOMBIE_2);

	for (int indexZombie = 0; indexZombie < ZOMBIE_2; indexZombie++)
	{
		auto sprite = Sprite::createWithSpriteFrameName("Z2Walk1.png");
		sprite->setVisible(false);
		addChild(sprite);
		_Zombie2->pushBack(sprite);
	}
}

//Tại đây gọi zombie ra screen
void Zombie::createZombie_2(float delta)
{
	bool check = false;

	//Check trong Kho xem có con nào đang ẩn k hay gọi cách khác là đang rãnh
	for (int index = 0; index < _Zombie2->size(); index++)
	{
		//Nếu có thì gán vào cho zomBie2 rồi goto đến setPosition
		if (_Zombie2->at(index)->isVisible() == false)
		{
			zomBie2 = _Zombie2->at(index);
			check = true;
			goto GoToSetPosition;
		}
	}
	//Chổ này là check xong mà k có con nào rãnh thì tạo mới 1 con
	if (check == false)
	{
		auto spriteNew = Sprite::createWithSpriteFrameName("Z2Walk1.png");
		spriteNew->setVisible(false);
		addChild(spriteNew);
		_Zombie2->pushBack(spriteNew);
		zomBie2 = _Zombie2->at(_Zombie2->size() - 1);
	}
	
	//Phần này setPosition đem ra screen và move nó đến ngôi nhà
	GoToSetPosition : int random0_3 = random(0, 3);
	float positionY = (float)random0_3 / 10;
	zomBie2->setPosition(winSize.width, winSize.height * positionY);
	zomBie2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	zomBie2->setScale(0.3f);
	zomBie2->setTag(ZOMBIE_TAG);


	//Set Physics
	auto physics = PhysicsBody::createBox(zomBie2->getContentSize());
	physics->setCollisionBitmask(ZOMBIE_BITMASK);
	physics->setContactTestBitmask(true);
	physics->setDynamic(false);
	zomBie2->setPhysicsBody(physics);

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
	zomBie2->setVisible(true);
	auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * LOCAL_MOVETO, winSize.height * positionY));
	auto spawn = Spawn::create(Repeat::create(animate, TIME_REPEAT_ANIMATE), moveto, nullptr);
	zomBie2->runAction(spawn);
}
//Hết phần pool

void Zombie::physicsForLine()
{
	auto linePhysics = Node::create();
	addChild(linePhysics);
	linePhysics->setPosition(winSize.width * 0.1, 0.0);
	linePhysics->setTag(LINE_TAG);


	auto physicsForLine = PhysicsBody::createBox(Size(1, winSize.height));
	physicsForLine->setCollisionBitmask(LINE_BITMASK);
	physicsForLine->setContactTestBitmask(true);
	physicsForLine->setDynamic(false);
	linePhysics->setPhysicsBody(physicsForLine);
}

bool Zombie::onContactBegan(PhysicsContact &contact)
{
	auto physicsZombie = (Sprite*)contact.getShapeA()->getBody()->getNode();
	int tagZombie = physicsZombie->getTag();
	auto physicsLine = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tagLine = physicsLine->getTag();

	if (tagZombie == ZOMBIE_TAG && tagLine == LINE_TAG ||
		tagZombie == LINE_TAG && tagLine == ZOMBIE_TAG)
	{
		/*physicsZombie->setPosition(winSize.width, 0.0f);*/
		/*physicsZombie->setVisible(false);*/
		zombie_2Dead(physicsZombie);
	}

	return true;
}

void Zombie::zombie_2Dead(Sprite* sprite)
{
	sprite->stopAllActions();
	sprite->setSpriteFrame("Z2Dead1.png");
	auto *animation = Animation::create();
	for (int i = 1; i < 9; i++)
	{
		auto Z2Walk = StringUtils::format("Z2Dead%i", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Z2Walk));
	}
	animation->setDelayPerUnit(1 / TIME_ACTION_ANIMATION);
	auto animate = Animate::create(animation);
	sprite->runAction(Repeat::create(animate, TIME_REPEAT_ANIMATE));
}

void Zombie::createZombie_3(float delta)
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

void Zombie::createZombie_4(float delta)
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

void Zombie::createZombie_5(float delta)
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

