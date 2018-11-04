#include "Bullet/BulletObject.h"
#include "Parameter.h"
#include "Zombie/PZombie.h"

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
	this->addChild(_sprBullet);


	PhysicsBody* _bulletPhysicBody = PhysicsBody::createBox(Size(820, 450));
	_bulletPhysicBody->setContactTestBitmask(true);
	_bulletPhysicBody->setDynamic(false);
	_bulletPhysicBody->setGroup(-2);
	this->setPhysicsBody(_bulletPhysicBody);

	this->setTag(BULLET_TAG);
	return true;
}


void BulletObject::onCollission(GameObject *obj)
{
	if (obj->getTag() == ZOMBIE_TAG)
	{
		auto callfunc = CallFunc::create([=]
		{
			removeBullet();
		});

		auto sqe = Sequence::create(DelayTime::create(0.01f), callfunc, nullptr);
		this->runAction(sqe);
	}

}

void BulletObject::bulletFire(float locationX, float locationY)
{
	Size winSize = Director::getInstance()->getWinSize();

	int offX = locationX - _sprBullet->getPosition().x;
	int offY = locationY - _sprBullet->getPosition().y;

	if (offX <= 0) return;

	int realX = winSize.width + (_sprBullet->getContentSize().width / 2);

	float ratio = (float)offY / (float)offX;
	int realY = (realX * ratio) + _sprBullet->getPosition().y;
	auto realDest = Point(realX, realY);
	float angleRadians = atan2f(realY, realX);
	angleRadians = CC_RADIANS_TO_DEGREES(angleRadians);

	int offRealX = realX - _sprBullet->getPosition().x;
	int offRealY = realY - _sprBullet->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));

	float velocity = BULLET_VEC;

	float realMoveDuration = length / velocity;
	auto bulletFire = MoveTo::create(realMoveDuration, realDest);
	_sprBullet->setRotation(-angleRadians);

	_sprBullet->runAction(bulletFire);
}

void BulletObject::removeBullet()
{
	this->removeFromParent();
}