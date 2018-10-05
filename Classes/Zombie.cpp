#include "Zombie.h"
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


	schedule(schedule_selector(Zombie::createZombie_2), TIME_CREATE_ZOMBIE_2);
	/*schedule(schedule_selector(Zombie::createZombie_3), TIME_CREATE_ZOMBIE_3);
	schedule(schedule_selector(Zombie::createZombie_4), TIME_CREATE_ZOMBIE_4);
	schedule(schedule_selector(Zombie::createZombie_5), TIME_CREATE_ZOMBIE_5);*/

	Zombie::physicsForLine();

	auto listenerContact = EventListenerPhysicsContact::create();
	listenerContact->onContactBegin = CC_CALLBACK_1(Zombie::onContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerContact, this);


	return true;
}

void Zombie::createZombie_2(float unknow)
{
	//Zombie 2
	zomBie2 = Sprite::createWithSpriteFrameName("Z2Walk1.png");
	
	zomBie2->setPosition(winSize.width, 0.0);
	zomBie2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	zomBie2->setScale(0.15f);
	zomBie2->setTag(ZOMBIE_TAG);

	//Set Physics
	auto physics = PhysicsBody::createBox(zomBie2->getContentSize());
	physics->setCollisionBitmask(ZOMBIE_BITMASK);
	physics->setContactTestBitmask(true);
	physics->setDynamic(false);
	zomBie2->setPhysicsBody(physics);

	addChild(zomBie2, 6);
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
	auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * LOCAL_MOVETO, 0.0));
	auto spawn = Spawn::create(Repeat::create(animate, TIME_REPEAT_ANIMATE), moveto, nullptr);
	zomBie2->runAction(spawn);
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
		this->removeChildByTag(ZOMBIE_TAG, true);
	}

	return true;
}

void Zombie::createZombie_3(float unknow)
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

void Zombie::createZombie_4(float unknow)
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

void Zombie::createZombie_5(float unknow)
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

