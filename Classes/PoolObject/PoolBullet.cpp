#include "PoolBullet.h"
#include "Bullet/BulletObject.h"
PoolBullet::PoolBullet()
{
}
		
PoolBullet::~PoolBullet()
{
}
PoolBullet *PoolBullet::create(float x, float y)
{
	PoolBullet *pRet = new(std::nothrow) PoolBullet();
	if (pRet && pRet->init(x, y))
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

bool PoolBullet::init(float x, float y)
{
	if (!Node::init())
	{
		return false;
	}
	xFromGameLayer = x;
	yFromGameLayer = y;
	initBullet(x,y);
	addBullet();
	createBullet(x,y);
	return true;
}


void PoolBullet::addBullet()
{
	Size winSize = Director::getInstance()->getWinSize();
	auto bullet = this->createBullet(xFromGameLayer, yFromGameLayer);
	if (bullet != nullptr)
	{
		//bullet->removeFromParent();
		bullet->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		bullet->setVisible(true);
		//bullet->setScale(0.01f);
		bullet->setPosition(winSize.width * 0.25f, winSize.height * 0.25f);
		bullet->setPosition(winSize.width * 1.2f, winSize.height * 0.5f);
		this->addChild(bullet);
		bullet->reset(xFromGameLayer, yFromGameLayer);
	}
}


void PoolBullet::initBullet(float x ,float y)
{
	for (int i = 0; i < 25; i++)
	{
		auto bullet = BulletObject::create(x,y);
		bullet->setVisible(true);
		_listBullet.pushBack(bullet);
	}
}
BulletObject * PoolBullet::createBullet(float x, float y)
{
	BulletObject* instance = nullptr;
	if (_listBullet.size() <= 0) // if pool not have bullet, create new
	{
		instance = BulletObject::create(x, y);
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolBullet::returnBulletToPool, this));
	}
	else
	{
		instance = _listBullet.back(); // get last element
		instance->reset(x, y);
		instance->retain();
		_listBullet.popBack(); // erase last element
	}
	return instance;
}

void PoolBullet::returnBulletToPool(BulletObject * bullet)
{
	_listBullet.pushBack(bullet);
}