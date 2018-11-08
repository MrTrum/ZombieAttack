#include "PoolObject/PoolZombie.h"
#include "Zombie/PZombie.h"
#include "Parameter.h"

USING_NS_CC;

PoolZombie::PoolZombie() : numberZombie(0)
{
}

PoolZombie::~PoolZombie()
{
}

void PoolZombie::initZombie()
{
	for (int indexZombie = 0; indexZombie < ZOMBIE_2; indexZombie++)
	{
		auto zombie = PZombie::create(this);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setHealthBar(zombie->health);
		zombie->setVisible(false);
		_listZombie.pushBack(zombie);
	}
}

PZombie* PoolZombie::getZombie()
{
	PZombie* zombie = nullptr;
	for (int index = 0; index < _listZombie.size(); index++)
	{
		bool foundZombie = false;
		if (_listZombie.at(index)->isVisible() == false)
		{
			zombie = _listZombie.at(index); 
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
		zombie = PZombie::create(this);
		zombie->setHealthBar(zombie->health);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setVisible(false);
		_listZombie.pushBack(zombie);
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

	scheduleOnce(schedule_selector(PoolZombie::createZombie_2), TIME_CREATE_ZOMBIE_2);
	

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

		zombie->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		zombie->setVisible(true);
		zombie->setScale(0.3f);
		float positionY = randomPositionY();
		auto winSize = Director::getInstance()->getWinSize();
		zombie->setPosition(winSize.width * 1.2f, winSize.height * positionY);

		auto Z_Order = ZOrder(positionY);
		this->addChild(zombie, Z_Order);

		if (numberZombie < 80)
		{
			numberZombie = numberZombie + 5;
			updateBloodBar(numberZombie);
		}
		if (numberZombie == 100)
		{
			pauseSchedule();
		}
		else if (numberZombie >= 80)
		{
			numberZombie = numberZombie + 1;
			updateBloodBar(numberZombie);
			updateSchedule();
		}

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
	for (int index = 0; index < _listZombie.size(); index++)
	{
		if (_listZombie.at(index)->isVisible() == true)
		{
			return false;
		}
	}
	if (numberZombie <= 100)
	{
		return true;
	}
	return false;
}


void PoolZombie::pauseSchedule()
{
	this->unschedule(schedule_selector(PoolZombie::createZombie_2));
}
void PoolZombie::updateSchedule()
{
	this->unschedule(schedule_selector(PoolZombie::createZombie_2));
	schedule(schedule_selector(PoolZombie::createZombie_2), 0.7f);
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





