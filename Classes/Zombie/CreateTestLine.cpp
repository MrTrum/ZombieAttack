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

CreateTestLine* CreateTestLine::create(int tag)
{
	CreateTestLine *pRet = new(std::nothrow) CreateTestLine();
	if (pRet && pRet->init(tag))
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

bool CreateTestLine::init(int tag)
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
	this->setPhysicsBody(physicsForLine);

	return true;
}
void CreateTestLine::onCollission(GameObject *obj)
{
	if (obj->getTag() == 6 || obj->getTag() == 7)
	{
		auto pzombie = static_cast<PZombie*>(obj);
		auto actionWalk = CallFunc::create([=]
		{
			pzombie->attack();
		});
		auto actionSkill = CallFunc::create([=]
		{
			pzombie->skill();
		});
		auto spawn = Spawn::create(actionWalk, actionSkill, nullptr);
		pzombie->runAction(spawn);
	}
}


