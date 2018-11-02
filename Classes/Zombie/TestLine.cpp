#include "TestLine.h"
#include "Parameter.h"
#include "PZombie.h"



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

	auto linePhysics = Node::create();
	this->addChild(linePhysics);
	this->setTag(LINE_TAG);
	

	auto physicsForLine = PhysicsBody::createBox(Size(1, winSize.height));
	physicsForLine->setContactTestBitmask(true);
	physicsForLine->setDynamic(false);
	this->setPhysicsBody(physicsForLine);
	return true;
}

void TestLine::onCollission(GameObject *obj)
{

}