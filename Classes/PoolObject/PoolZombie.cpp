#include "PoolObject/PoolZombie.h"
#include "Zombie/PZombie.h"
#include "Parameter.h"

USING_NS_CC;

PoolZombie::PoolZombie() :
	numberZombie(0),
	_check(1)
{
}

PoolZombie::~PoolZombie()
{
}

void PoolZombie::initZombie()
{
	for (int indexZombie = 0; indexZombie < ZOMBIE_2; indexZombie++)
	{
		auto zombie = PZombie::create(this, "Z2Walk");
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setHealthBar(HEALTH_ZOMBIE2);
		zombie->setVisible(false);
		_listZombie1.pushBack(zombie);

		auto zombie2 = PZombie::create(this, "Z3Walk");
		zombie2->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie2->setHealthBar(HEALTH_ZOMBIE3);
		zombie2->setVisible(false);
		_listZombie2.pushBack(zombie2);
	}
}

PZombie* PoolZombie::getZombie()
{
	PZombie* zombie = nullptr;
	for (int index = 0; index < _listZombie1.size(); index++)
	{
		bool foundZombie = false;
		if (_listZombie1.at(index)->isVisible() == false)
		{
			zombie = _listZombie1.at(index);
			zombie->health = HEALTH_ZOMBIE2;
			auto resetHealth = HEALTH_ZOMBIE2;
			zombie->updateHealthBar(resetHealth);
			foundZombie = true;
		}
		if (foundZombie)
		{
			break;
		}
	}
	if (zombie == nullptr)
	{
		zombie = PZombie::create(this, "Z2Walk");
		zombie->setHealthBar(zombie->health);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setVisible(false);
		_listZombie1.pushBack(zombie);
	}
	return zombie;
}

PZombie* PoolZombie::getZombie3()
{
	PZombie* zombie = nullptr;
	for (int index = 0; index < _listZombie2.size(); index++)
	{
		bool foundZombie = false;
		if (_listZombie2.at(index)->isVisible() == false)
		{
			zombie = _listZombie2.at(index);
			zombie->health3 = HEALTH_ZOMBIE3;
			auto resetHealth = HEALTH_ZOMBIE3;
			zombie->updateHealthBar(resetHealth);
			foundZombie = true;
		}
		if (foundZombie)
		{
			break;
		}
	}
	if (zombie == nullptr)
	{
		zombie = PZombie::create(this, "Z3Walk");
		zombie->setHealthBar(zombie->health3);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setVisible(false);
		_listZombie2.pushBack(zombie);
	}
	return zombie;
}



bool PoolZombie::init(GamePlayLayer* ptr)
{
	if (!Node::init())
	{
		return false;
	}
	//Tú đã sửa
	_gamePlayLayerPtr = ptr;
	//
	setFrameBloodBar();
	setBloodBar(0);
	initZombie();

	schedule(schedule_selector(PoolZombie::createZombie_2), 3.0f);
	schedule(schedule_selector(PoolZombie::createZombie_3), 3.0f);

	return true;
}

PoolZombie* PoolZombie::create(GamePlayLayer* ptr)
{
	PoolZombie *pRet = new(std::nothrow) PoolZombie();
	if (pRet && pRet->init(ptr))
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

void PoolZombie::createZombie_2(float delta)
{
	auto zombie = this->getZombie();
	if (zombie != nullptr)
	{
		// check if it has parent 
		zombie->removeFromParent();

		changeSchedule(2);

		zombie->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		zombie->setVisible(true);
		zombie->setScale(0.3f);
		float positionY = randomPositionY();
		auto winSize = Director::getInstance()->getWinSize();
		zombie->setPosition(winSize.width * 1.2f, winSize.height * positionY);

		auto Z_Order = ZOrder(positionY);
		this->addChild(zombie, Z_Order);

		//Move zombie 2	
		float positionX = randomPositionX(positionY);
		auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * positionX, winSize.height * positionY));
		zombie->runAction(moveto);
	}
}

void PoolZombie::createZombie_3(float delta)
{
	auto zombie = this->getZombie3();
	if (zombie != nullptr)
	{
		// check if it has parent 
		zombie->removeFromParent();

		changeSchedule(3);

		zombie->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		zombie->setVisible(true);
		zombie->setScale(0.3f);
		float positionY = randomPositionY();
		auto winSize = Director::getInstance()->getWinSize();
		zombie->setPosition(winSize.width * 1.2f, winSize.height * positionY);

		auto Z_Order = ZOrder(positionY);
		this->addChild(zombie, Z_Order);

		//Move zombie 2	
		float positionX = randomPositionX(positionY);
		auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * positionX, winSize.height * positionY));
		zombie->runAction(moveto);
	}
}

void PoolZombie::setFrameBloodBar()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto frameBloodBar = Sprite::create("FrameBloodBar.png");
	frameBloodBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	frameBloodBar->setPosition(winSize.width - 10.0f, winSize.height - 20.0f);
	frameBloodBar->setScaleY(0.17f);
	frameBloodBar->setScaleX(0.25f);
	addChild(frameBloodBar, 1);

	auto booshead = Sprite::create("BossHead.png");
	booshead->setPosition(winSize.width - 175.0f, winSize.height - 42.0f);
	booshead->setScale(0.1f);
	addChild(booshead, 1);

	auto zombiehead = Sprite::create("ZombieHead.png");
	zombiehead->setPosition(winSize.width - 230.0f, winSize.height - 20.0f);
	zombiehead->setScale(0.25f);
	addChild(zombiehead, 1);
}

void PoolZombie::setBloodBar(float percent)
{
	auto winSize = Director::getInstance()->getWinSize();

	bloodbar = ui::LoadingBar::create("BloodBar.png");
	this->addChild(bloodbar, 2);
	bloodbar->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodbar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	bloodbar->setScaleX(0.26f);
	bloodbar->setScaleY(0.20f);
	bloodbar->setPercent(percent);
	bloodbar->setPosition(Vec2(winSize.width - 10.0f, winSize.height - 20.0f));
}

void PoolZombie::updateBloodBar(float percent)
{
	bloodbar->removeFromParent();
	setBloodBar(percent);
}

bool PoolZombie::checkTheLastZombie()
{
	for (int index = 0; index < _listZombie1.size(); index++)
	{
		if (_listZombie1.at(index)->isVisible() == true)
		{
			return false;
		}
	}
	if (numberZombie >= 100)
	{
		return true;
	}
	return false;
}


void PoolZombie::changeSchedule(int NOZombie)
{
	if (numberZombie < 10)
	{
		if (_check == 1)
		{
			updateSchedule(1.0f, NOZombie);
			_check++;
		}
		numberZombie = numberZombie + 2;
		updateBloodBar(numberZombie);
	}
	else if (numberZombie >= 10 && numberZombie < 40)
	{
		if (_check == 2)
		{
			updateSchedule(2.0f, NOZombie);
			_check++;
		}
		numberZombie = numberZombie + 2;
		updateBloodBar(numberZombie);
	}
	else if (numberZombie >= 40 && numberZombie < 80)
	{
		if (_check == 3)
		{
			updateSchedule(3.0f, NOZombie);
			_check++;
		}
		numberZombie = numberZombie + 2;
		updateBloodBar(numberZombie);
	}
	else if (numberZombie >= 80 && numberZombie < 100)
	{
		if (_check == 4)
		{
			updateSchedule(6.0f, NOZombie);
			_check++;
		}
		numberZombie = numberZombie + 1;
		updateBloodBar(numberZombie);
	}
	else
	{
		if (NOZombie == 2)
		{
			unschedule(schedule_selector(PoolZombie::createZombie_2));
		}
		else if (NOZombie == 3)
		{
			unschedule(schedule_selector(PoolZombie::createZombie_3));
		}
	}
}

void PoolZombie::updateSchedule(int NOZombie, float time)
{
	if (NOZombie == 2)
	{
		this->unschedule(schedule_selector(PoolZombie::createZombie_2));
		this->schedule(schedule_selector(PoolZombie::createZombie_2), TIME_CREATE_ZOMBIE_2 / time);
	}
	else if (NOZombie == 3)
	{
		this->unschedule(schedule_selector(PoolZombie::createZombie_3));
		this->schedule(schedule_selector(PoolZombie::createZombie_3), TIME_CREATE_ZOMBIE_3 / time);
	}
}

float PoolZombie::randomPositionY()
{
	float position_Y = 0.1f;
	int random1_4 = random(1, 4);
	if (random1_4 == 1)
	{
		position_Y = 0.1f;
	}
	else if (random1_4 == 2)
	{
		position_Y = 0.13f;
	}
	else if (random1_4 == 3)
	{
		position_Y = 0.16f;
	}
	else
	{
		position_Y = 0.19f;
	}
	return position_Y;
}
float PoolZombie::randomPositionX(float position_y)
{
	float position_x = 0.1f;
	if (position_y >= 0.1 && position_y < 0.12)
	{
		position_x = 0.23f;
	}
	else if (position_y <= 0.13)
	{
		position_x = 0.27f;
	}
	else if (position_y <= 0.16)
	{
		position_x = 0.3f;
	}
	else
	{
		position_x = 0.33f;
	}
	return position_x;
}

int PoolZombie::ZOrder(float position_y)
{
	auto zOrder = 1;
	if (position_y >= 0.1 && position_y < 0.12)
	{
		zOrder = 4;
	}
	else if (position_y <= 0.13)
	{
		zOrder = 3;
	}
	else if (position_y <= 0.16)
	{
		zOrder = 2;
	}
	else
	{
		zOrder = 1;
	}
	return zOrder;
}





