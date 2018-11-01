#include "BulletObject.h"
#include "Parameter.h"


BulletObject::BulletObject()
{
}

BulletObject::~BulletObject()
{
}

bool BulletObject::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	_sprBullet = Sprite::create("test_bullet.png");
	addChild(_sprBullet);
	_sprBullet->setScale(0.01f);
	PhysicsBody* _BulletPhysicsBody = PhysicsBody::createBox(Size(820, 450));
	_BulletPhysicsBody->setCollisionBitmask(12);
	_BulletPhysicsBody->setContactTestBitmask(true);
	_BulletPhysicsBody->setDynamic(true);
	_sprBullet->setPhysicsBody(_BulletPhysicsBody);

	setTag(BULLET_TAG);
	return true;
}

void BulletObject::dead()
{
	this->removeFromParent();
}

void BulletObject::attack()
{

}

void BulletObject::onCollission(GameObject *obj)
{

}