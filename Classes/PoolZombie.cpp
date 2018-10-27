#include "PoolZombie.h"
#include "PZombie.h"
#include "Parameter.h"

USING_NS_CC;

PoolZombie::PoolZombie()
{
}

PoolZombie::~PoolZombie()
{
}

void PoolZombie::initZombie()
{
	for (int indexZombie = 0; indexZombie < ZOMBIE_2; indexZombie++)
	{
		auto zombie = PZombie::create();
		zombie->getLoadingHealth(zombie->_health);
		_listZombie.pushBack(zombie);
	}
}

PZombie* PoolZombie::getZombie() 
{
	PZombie* zombie = nullptr;
	for (int index = 0; index < _listZombie.size(); index++)
	{
		if (_listZombie.at(index)->isVisible() == false)
		{
			zombie = _listZombie.at(index); //Nếu nó tìm thấy rồi tại sao k thoát khỏi vòng lặp mà lại chạy hết size???
			auto resetHealth = zombie->_health;
			zombie->updateLoadingHealth(resetHealth);
		}
	}
	if (zombie == nullptr)
	{
		zombie = PZombie::create();
		zombie->getLoadingHealth(zombie->_health);
		_listZombie.pushBack(zombie);
	}
	return zombie;
}


bool PoolZombie::init()
{
	if (!Node::init())
	{
		return false;
	}
	

	initZombie();
	schedule(schedule_selector(PoolZombie::createZombie_2), TIME_CREATE_ZOMBIE_2);
	/*schedule(schedule_selector(PoolZombie::createLine), 2.0f);*/

	return true;
}



void PoolZombie::createZombie_2(float delta)
{
	auto zombie = this->getZombie();
	if (zombie != nullptr)
	{
		// check if it has parent 
		zombie->removeFromParent();
		addChild(zombie);
		zombie->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		zombie->setVisible(true);
		
		float positionY = 0.1f;
		int random1_2 = random(1, 4);
		if (random1_2 == 3)
		{
			positionY = 0.15f;
		}
		else if (random1_2 == 4)
		{
			positionY = 0.25f;
		}
		else
		{
			positionY = (float)random1_2 / 10;
		}

		auto winSize = Director::getInstance()->getWinSize();
		zombie->setPosition(winSize.width * 0.8f, winSize.height * positionY);
		zombie->setScale(0.3f);


		//Move zombie 2		
		auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * LOCAL_MOVETO, winSize.height * positionY));
		zombie->runAction(moveto);
	}
}
void PoolZombie::createLine(float delta)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto linePhysics = Node::create();
	this->addChild(linePhysics);
	this->setTag(LINE_TAG);
	linePhysics->setPosition(winSize.width * 0.1, 0.0);

	auto physicsForLine = PhysicsBody::createBox(Size(1, winSize.height));
	physicsForLine->setContactTestBitmask(true);
	physicsForLine->setDynamic(false);
	linePhysics->setPhysicsBody(physicsForLine);

	auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * 0.9f, 0.0f));
	linePhysics->runAction(moveto);
}



