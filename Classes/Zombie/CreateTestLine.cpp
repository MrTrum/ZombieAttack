#include "TestLine2.h"
#include "Parameter.h"
#include "CreateTestLine.h"


USING_NS_CC;

CreateTestLine::CreateTestLine()
{
}

CreateTestLine::~CreateTestLine()
{
}

bool CreateTestLine::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	auto linePhysics = Node::create();
	this->addChild(linePhysics);
	this->setTag(TAG_LINE2);


	auto physicsForLine = PhysicsBody::createBox(Size(1, winSize.height));
	physicsForLine->setContactTestBitmask(true);
	physicsForLine->setDynamic(false);
	this->setPhysicsBody(physicsForLine);

	return true;
}
void CreateTestLine::onCollission(GameObject *obj)
{

}


