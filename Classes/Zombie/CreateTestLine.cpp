#include "TestLine2.h"
#include "Parameter.h"
#include "CreateTestLine.h"
#include "GameObject/PZombie.h"


USING_NS_CC;

CreateTestLine::CreateTestLine()
{
}

CreateTestLine::~CreateTestLine()
{
}

CreateTestLine* CreateTestLine::create(int tag, Vec2 location)
{
	CreateTestLine *pRet = new(std::nothrow) CreateTestLine();
	if (pRet && pRet->init(tag, location))
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

bool CreateTestLine::init(int tag, Vec2 location)
{
	if (!GameObject::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	auto linePhysics = Node::create();
	this->addChild(linePhysics);
	this->setTag(tag);


	auto physicsForLine = PhysicsBody::createBox(Size(1, winSize.height));
	physicsForLine->setContactTestBitmask(true);
	physicsForLine->setDynamic(false);
	physicsForLine->setGroup(-2);
	this->setPhysicsBody(physicsForLine);

	_location = location;
	return true;
}
void CreateTestLine::onCollission(GameObject *obj)
{
	/*auto pzombie = static_cast<PZombie*>(obj);
	pzombie->attack();
	if (obj->getTag() == 6 || obj->getTag() == 7)
	{
		auto actionWalk = CallFunc::create([=]
		{
			pzombie->attack();
		});
		auto actionSkill = CallFunc::create([=]
		{
			pzombie->playAnimationSkill(pzombie->getTag());
		});
		auto spawn = Spawn::create(actionWalk, actionSkill, nullptr);
		pzombie->runAction(spawn);
	}*/
}


