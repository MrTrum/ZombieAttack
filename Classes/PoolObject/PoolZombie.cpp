#include "PoolObject/PoolZombie.h"
#include "Zombie/PZombie.h"
#include "Parameter.h"

USING_NS_CC;
#define PositionY1 0.1f
#define PositionY2 0.13f
#define PositionY3 0.16f
#define PositionY4 0.19f

int	PoolZombie::scene = 0;

PoolZombie::PoolZombie() :
	_numberZombie(0),
	_check(1),
	_checkPositionY1(true),
	_checkPositionY2(true),
	_checkPositionY3(true),
	_checkPositionY4(true)
{
}

PoolZombie::~PoolZombie()
{
}

void PoolZombie::initZombie()
{
	std::string stringName;
	for (int indexZombie = 0; indexZombie < ZOMBIE_SIZE; indexZombie++)
	{
		stringName = getNameZombie(_setZombie1);
		auto zombie = PZombie::create(this, stringName, _setZombie1);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setHealthBar(HEALTH_ZOMBIE);
		zombie->setVisible(false);
		_listZombie1.pushBack(zombie);

		stringName = getNameZombie(_setZombie2);
		auto zombie2 = PZombie::create(this, stringName, _setZombie2);
		zombie2->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie2->setHealthBar(HEALTH_ZOMBIE);
		zombie2->setVisible(false);
		_listZombie2.pushBack(zombie2);

		stringName = getNameZombie(_setZombie3);
		auto zombie3 = PZombie::create(this, stringName, _setZombie3);
		zombie3->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie3->setHealthBar(HEALTH_ZOMBIE);
		zombie3->setVisible(false);
		_listZombie3.pushBack(zombie3);

		stringName = getNameZombie(_setZombie4);
		auto zombie4 = PZombie::create(this, stringName, _setZombie4);
		zombie4->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie4->setHealthBar(HEALTH_ZOMBIE);
		zombie4->setVisible(false);
		_listZombie4.pushBack(zombie4);
	}
	for (int index = 0; index < ZOMBIE_SIZE; index++)
	{
		_listZombie2Total.pushBack(_listZombie1.at(index));
		_listZombie2Total.pushBack(_listZombie2.at(index));
		_listZombie2Total.pushBack(_listZombie3.at(index));
		_listZombie2Total.pushBack(_listZombie4.at(index));
	}
	 
}

std::string	PoolZombie::getNameZombie(int setzombie)
{
	std::string stringName = StringUtils::format("Z%dWalk", setzombie);
	return stringName;
}

PZombie* PoolZombie::getZombie1()
{
	PZombie* zombie = nullptr;
	for (int index = 0; index < _listZombie1.size(); index++)
	{
		bool foundZombie = false;
		if (_listZombie1.at(index)->isVisible() == false)
		{
			zombie = _listZombie1.at(index);
			zombie->health = HEALTH_ZOMBIE;
			auto resetHealth = HEALTH_ZOMBIE;
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
		std::string stringName = getNameZombie(_setZombie1);
		zombie = PZombie::create(this, stringName, _setZombie1);
		zombie->setHealthBar(HEALTH_ZOMBIE);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setVisible(false);
		_listZombie1.pushBack(zombie);
	}
	return zombie;
}

PZombie* PoolZombie::getZombie2()
{
	PZombie* zombie = nullptr;
	for (int index = 0; index < _listZombie2.size(); index++)
	{
		bool foundZombie = false;
		if (_listZombie2.at(index)->isVisible() == false)
		{
			zombie = _listZombie2.at(index);
			zombie->health = HEALTH_ZOMBIE;
			auto resetHealth = HEALTH_ZOMBIE;
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
		std::string stringName = getNameZombie(_setZombie2);
		zombie = PZombie::create(this, stringName, _setZombie2);
		zombie->setHealthBar(HEALTH_ZOMBIE);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setVisible(false);
		_listZombie2.pushBack(zombie);
	}
	return zombie;
}


PZombie* PoolZombie::getZombie3()
{
	PZombie* zombie = nullptr;
	for (int index = 0; index < _listZombie3.size(); index++)
	{
		bool foundZombie = false;
		if (_listZombie3.at(index)->isVisible() == false)
		{
			zombie = _listZombie3.at(index);
			zombie->health = HEALTH_ZOMBIE;
			auto resetHealth = HEALTH_ZOMBIE;
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
		std::string stringName = getNameZombie(_setZombie3);
		zombie = PZombie::create(this, stringName, _setZombie3);
		zombie->setHealthBar(HEALTH_ZOMBIE);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setVisible(false);
		_listZombie3.pushBack(zombie);
	}
	return zombie;
}

PZombie* PoolZombie::getZombie4()
{
	PZombie* zombie = nullptr;
	for (int index = 0; index < _listZombie4.size(); index++)
	{
		bool foundZombie = false;
		if (_listZombie4.at(index)->isVisible() == false)
		{
			zombie = _listZombie4.at(index);
			zombie->health = HEALTH_ZOMBIE;
			auto resetHealth = HEALTH_ZOMBIE;
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
		std::string stringName = getNameZombie(_setZombie4);
		zombie = PZombie::create(this, stringName, _setZombie4);
		zombie->setHealthBar(HEALTH_ZOMBIE);
		zombie->setGamePlayLayerPtr(_gamePlayLayerPtr);
		zombie->setVisible(false);
		_listZombie4.pushBack(zombie);
	}
	return zombie;
}

PoolZombie* PoolZombie::create(GamePlayLayer* ptr, int sceneplay)
{
	PoolZombie *pRet = new(std::nothrow) PoolZombie();
	if (pRet && pRet->init(ptr, sceneplay))
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

bool PoolZombie::init(GamePlayLayer* ptr, int sceneplay)
{
	if (!Node::init())
	{
		return false;
	}
	_gamePlayLayerPtr = ptr;

	setFrameBloodBar();
	setBloodBar(0);

	scenePlay(sceneplay);
	

	return true;
}

void PoolZombie::scenePlay(int sceneplay)
{
	if (sceneplay == 1)
	{
		_setZombie1 = 2;
		_setZombie2 = 2;
		_setZombie3 = 2;
		_setZombie4 = 2;
		initZombie();
		schedule(schedule_selector(PoolZombie::createZombie_1), 3.0f);
		
	}
	else if (sceneplay == 2)
	{
		_setZombie1 = 2;
		_setZombie2 = 3;
		_setZombie3 = 2;
		_setZombie4 = 2;
		initZombie();
		schedule(schedule_selector(PoolZombie::createZombie_1), 3.0f);
	}
	else if (sceneplay == 3)
	{
		_setZombie1 = 2;
		_setZombie2 = 3;
		_setZombie3 = 4;
		_setZombie4 = 2;
		initZombie();
		schedule(schedule_selector(PoolZombie::createZombie_1), 3.0f);
	}
}

void PoolZombie::createZombie_1(float delta)
{
	auto zombie = this->getZombie1();
	if (zombie != nullptr)
	{
		// check if it has parent 
		zombie->removeFromParent();

		changeSchedule();

		zombie->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		zombie->setVisible(true);
		zombie->setScale(0.3f);
		float positionY = randomPositionY();
		auto winSize = Director::getInstance()->getWinSize();
		zombie->setPosition(winSize.width * 1.2f, winSize.height * positionY);

		auto Z_Order = ZOrder(positionY);
		this->addChild(zombie, Z_Order);

		float positionX = randomPositionX(positionY);
		auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * positionX, winSize.height * positionY));
		zombie->runAction(moveto);
	}
}

void PoolZombie::createZombie_2(float delta)
{
	auto zombie = this->getZombie2();
	if (zombie != nullptr)
	{
		//check if it has parent 
		zombie->removeFromParent();

		changeSchedule();

		zombie->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		zombie->setVisible(true);
		zombie->setScale(0.3f);
		float positionY = randomPositionY();
		auto winSize = Director::getInstance()->getWinSize();
		zombie->setPosition(winSize.width * 1.2f, winSize.height * positionY);

		auto Z_Order = ZOrder(positionY);
		this->addChild(zombie, Z_Order);

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
		//check if it has parent 
		zombie->removeFromParent();

		changeSchedule();

		zombie->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		zombie->setVisible(true);
		zombie->setScale(0.3f);
		float positionY = randomPositionY();
		auto winSize = Director::getInstance()->getWinSize();
		zombie->setPosition(winSize.width * 1.2f, winSize.height * positionY);

		auto Z_Order = ZOrder(positionY);
		this->addChild(zombie, Z_Order);

		float positionX = randomPositionX(positionY);
		auto moveto = MoveTo::create(TIME_MOVETO_ZOMBIE, Vec2(winSize.width * positionX, winSize.height * positionY));
		zombie->runAction(moveto);
	}
}

void PoolZombie::createZombie_4(float delta)
{
	auto zombie = this->getZombie4();
	if (zombie != nullptr)
	{
		//check if it has parent 
		zombie->removeFromParent();

		changeSchedule();

		zombie->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		zombie->setVisible(true);
		zombie->setScale(0.3f);
		float positionY = randomPositionY();
		auto winSize = Director::getInstance()->getWinSize();
		zombie->setPosition(winSize.width * 1.2f, winSize.height * positionY);

		auto Z_Order = ZOrder(positionY);
		this->addChild(zombie, Z_Order);

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
	if (_numberZombie < 100)
	{
		return false;
	}
	else
	{
		for (int index = 0; index < _listZombie2Total.size(); index++)
		{
			if (_listZombie2Total.at(index)->isVisible() == true)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}


void PoolZombie::changeSchedule()
{
	if (_numberZombie < 8)
	{
		if (_check == 1)
		{
			updateSchedule(_numberZombie);
			_check++;
		}
		_numberZombie =_numberZombie + 2;
		updateBloodBar(_numberZombie);
	}
	else if (_numberZombie >= 8 && _numberZombie < 40)
	{
		if (_check == 2)
		{
			updateSchedule(_numberZombie);
			_check++;
		}
		_numberZombie = _numberZombie + 2;
		updateBloodBar(_numberZombie);
	}
	else if (_numberZombie >= 40 && _numberZombie < 80)
	{
		if (_check == 3)
		{
			updateSchedule(_numberZombie);
			_check++;
		}
		_numberZombie = _numberZombie + 2;
		updateBloodBar(_numberZombie);
	}
	else if (_numberZombie >= 80 && _numberZombie < 100)
	{
		if (_check == 4)
		{
			updateSchedule(_numberZombie);
			_check++;
		}
		_numberZombie = _numberZombie + 2;
		updateBloodBar(_numberZombie);
	}
	else
	{
		unschedule(schedule_selector(PoolZombie::createZombie_1));
		unschedule(schedule_selector(PoolZombie::createZombie_2));
		unschedule(schedule_selector(PoolZombie::createZombie_3));
		unschedule(schedule_selector(PoolZombie::createZombie_4));
	}
}

void PoolZombie::updateSchedule(int numberZombie)
{
	if (numberZombie < 8)
	{
		unschedule(schedule_selector(PoolZombie::createZombie_1));
		schedule(schedule_selector(PoolZombie::createZombie_1), 8.0f);
	}
	else if (numberZombie >= 8 && numberZombie < 40)
	{
		schedule(schedule_selector(PoolZombie::createZombie_2), 6.5f);
	}
	else if (numberZombie >= 40 && numberZombie < 80)
	{
		schedule(schedule_selector(PoolZombie::createZombie_3), 5.0f);
	}
	else if (numberZombie >= 80 && numberZombie < 100)
	{
		schedule(schedule_selector(PoolZombie::createZombie_4), 1.0f);
	}
}

float PoolZombie::randomPositionY()
{
	float position_Y = 0.1f;
	int random1_4 = random(1, 4);
	if (random1_4 == 1 && _checkPositionY1)
	{
		position_Y = PositionY1;
		_checkPositionY1 = false;
		_checkPositionY2 = true;
		_checkPositionY3 = true;
		_checkPositionY4 = true;
	}
	else if (random1_4 == 2 && _checkPositionY2)
	{
		position_Y = PositionY2;
		_checkPositionY1 = true;
		_checkPositionY2 = false;
		_checkPositionY3 = true;
		_checkPositionY4 = true;
	}
	else if (random1_4 == 3 && _checkPositionY3)
	{
		position_Y = PositionY3;
		_checkPositionY1 = true;
		_checkPositionY2 = true;
		_checkPositionY3 = false;
		_checkPositionY4 = true;
	}
	else if(random1_4 == 4 && _checkPositionY4)
	{
		position_Y = PositionY4;
		_checkPositionY1 = true;
		_checkPositionY2 = true;
		_checkPositionY3 = true;
		_checkPositionY4 = false;
	}
	return position_Y;
}
float PoolZombie::randomPositionX(float position_y)
{
	float position_x = 0.1f;
	if (position_y >= PositionY1 && position_y < PositionY2 - 1)
	{
		position_x = 0.23f;
	}
	else if (position_y <= PositionY2)
	{
		position_x = 0.27f;
	}
	else if (position_y <= PositionY3)
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
	if (position_y >= PositionY1 && position_y < PositionY2 - 1)
	{
		zOrder = 4;
	}
	else if (position_y <= PositionY2)
	{
		zOrder = 3;
	}
	else if (position_y <= PositionY3)
	{
		zOrder = 2;
	}
	else
	{
		zOrder = 1;
	}
	return zOrder;
}





