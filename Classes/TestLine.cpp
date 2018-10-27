#include "TestLine.h"
#include "Parameter.h"



USING_NS_CC;

TestLine::TestLine()
{
}

TestLine::~TestLine()
{
}

bool TestLine::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	scheduleOnce(schedule_selector(TestLine::createLine, this), 1.0f);

	return true;
}

void TestLine::createLine(float delta)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto linePhysics = Node::create();
	addChild(linePhysics);
	linePhysics->setTag(LINE_TAG);
	linePhysics->setPosition(winSize.width * 0.3, 0.0);

	auto physicsForLine = PhysicsBody::createBox(Size(1, winSize.height));
	physicsForLine->setContactTestBitmask(true);
	physicsForLine->setDynamic(false);
	linePhysics->setPhysicsBody(physicsForLine);

	auto linePhysics2 = Node::create();
	addChild(linePhysics2);
	linePhysics2->setTag(LINE_TAG);
	linePhysics2->setPosition(winSize.width * 0.5, 0.0);

	auto physicsForLine2 = PhysicsBody::createBox(Size(1, winSize.height));
	physicsForLine2->setContactTestBitmask(true);
	physicsForLine2->setDynamic(false);
	linePhysics2->setPhysicsBody(physicsForLine2);
}

void TestLine::dead()
{
	this->removeChildByTag(LINE_TAG);
}