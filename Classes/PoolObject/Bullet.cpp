#include "Bullet/BulletObject.h"
#include "PoolObject/Bullet.h"
#include "physics/CCPhysicsBody.h"
#include "Parameter.h"


USING_NS_CC;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}
bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}
	getBullet();

	return true;
}

BulletObject*  Bullet::getBullet()
{
	Size winSize = Director::getInstance()->getWinSize();
	_bullet = BulletObject::create();
	this->addChild(_bullet);
	_bullet->setScale(0.01f);
	_bullet->setPosition(winSize.width * 0.25f, winSize.height * 0.25f);

	return _bullet;
}

void Bullet::BulletFire(float locationX, float locationY)
{	
	Size winSize = Director::getInstance()->getWinSize();
	
	int offX = locationX - _bullet->getPosition().x;
	int offY = locationY - _bullet->getPosition().y;

	if (offX <= 0) return;

	int realX = winSize.width + (_bullet->getContentSize().width / 2);

	float ratio = (float)offY / (float)offX;
	int realY = (realX * ratio) + _bullet->getPosition().y;
	auto realDest = Point(realX, realY);
	float angleRadians = atan2f(realY, realX);
	angleRadians = CC_RADIANS_TO_DEGREES(angleRadians);

	int offRealX = realX - _bullet->getPosition().x;
	int offRealY = realY - _bullet->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));

	float velocity = BULLET_VEC;

	float realMoveDuration = length / velocity;
	auto bulletFire = MoveTo::create(realMoveDuration, realDest);
	_bullet->setRotation(-angleRadians);

	_bullet->runAction(bulletFire);
}
BulletObject* Bullet::createBullet()
{
	_bullet = nullptr;
	for (int index = 0; index < BulletPool.size(); index++)
	{
		if (BulletPool.at(index)->isVisible() == false)
		{
			_bullet = BulletPool.at(index);
		}
	}
	if (_bullet == nullptr)
	{
		_bullet = BulletObject::create();
		BulletPool.pushBack(_bullet);
	}
	return _bullet;
}