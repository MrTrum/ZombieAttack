#include "PoolBullet.h"
#include "GameObject/BulletObject.h"
PoolBullet::PoolBullet()
{
}
		
PoolBullet::~PoolBullet()
{
}

BulletObject * PoolBullet::createBullet(Vec2 location)
{
	BulletObject* instance = nullptr;
	if (_listBullet.size() <= 0) // if pool not have bullet, create new
	{
		instance = BulletObject::create(location);
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolBullet::returnBulletToPool, this));
	}
	else
	{
		instance = _listBullet.back(); // get last element
		instance->reset(location);
		instance->retain();
		_listBullet.popBack(); // erase last element
	}
	return instance;
}

void PoolBullet::returnBulletToPool(BulletObject * bullet)
{
	_listBullet.pushBack(bullet);
}