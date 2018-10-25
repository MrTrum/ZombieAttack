#include "GameObject.h"
#include "PoolZombie.h"


USING_NS_CC;


GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

bool GameObject::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();
	auto linePhysics = Node::create();
	this->addChild(linePhysics);
	this->setTag(LINE_TAG);
	linePhysics->setPosition(winSize.width * 0.1, 0.0);

	auto physicsForLine = PhysicsBody::createBox(Size(1, winSize.height));
	physicsForLine->setCollisionBitmask(12);
	physicsForLine->setContactTestBitmask(true);
	physicsForLine->setDynamic(false);
	linePhysics->setPhysicsBody(physicsForLine);

	auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * 0.9f, 0.0f));
	linePhysics->runAction(moveto);

	return true;
}


void GameObject::onCollission(GameObject *obj)
{
	if (obj->getTag() == ZOMBIE_TAG)
	{
		obj->dead();
	}
	//else if (obj->getTag() == LINE_TAG)
	//{
	//	this->removeChildByTag(LINE_TAG);
	//}
}




