#include "Bullet/BulletObject.h"
#include "Parameter.h"
#include "Zombie/PZombie.h"

BulletObject::BulletObject()
{
}

BulletObject::~BulletObject()
{
}

bool BulletObject::init(float x, float y)
{
	if (!GameObject::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	_sprBullet = Sprite::create("test_bullet.png");
	addChild(_sprBullet);
	setScale(0.15f);
	PhysicsBody* _bulletPhysicBody = PhysicsBody::createBox(_sprBullet->getContentSize() / 2);
	_bulletPhysicBody->setContactTestBitmask(true);
	_bulletPhysicBody->setDynamic(false);
	_bulletPhysicBody->setGroup(-2);
	this->setPhysicsBody(_bulletPhysicBody);
	bulletFire(x, y);
	this->setTag(TAG_BULLET);
	scheduleUpdate();
	return true;
}

BulletObject *BulletObject::create(float x, float y)
{
	BulletObject *pRet = new(std::nothrow) BulletObject();
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

void BulletObject::reset(float x, float y)
{
	Size winSize = Director::getInstance()->getWinSize();
	this->setPosition(winSize.width * 0.25f, winSize.height * 0.25f);
	this->setVisible(true);
	bulletFire(x, y);
	scheduleUpdate();
}

void BulletObject::onCollission(GameObject *obj)
{
	if (obj->getTag() == TAG_ZOMBIE1 || obj->getTag() == TAG_ZOMBIE2 || 
		obj->getTag() == TAG_ZOMBIE3 || obj->getTag() == TAG_ZOMBIE4)
	{
		_willBeDestroy = true;
	}

}

void BulletObject::setOnDestroyCallback(OnBulletDestroyCallback callback)
{
	_onBulletDestroyCallback = callback;
}

void BulletObject::bulletFire(float locationX, float locationY)
{
	Size winSize = Director::getInstance()->getWinSize();
	float recoil = random(-20, 10);
	auto startPos = this->getPosition();
	auto target = Vec2(locationX, locationY);
	auto distance = target - startPos;
	distance.y += recoil;
	auto vector = distance.getNormalized() * BULLET_VEC;
	auto aBulletFire = MoveBy::create(1.0f, vector);
	float angleRadians = atan2f(locationY - winSize.height * 0.25f, locationX - winSize.width * 0.25f);
	angleRadians = CC_RADIANS_TO_DEGREES(angleRadians);
	this->setRotation(-angleRadians);
	DelayTime *delay = DelayTime::create(0.5);
	CallFunc *callback = CallFunc::create([=]
	{
		_willBeDestroy = true;
	}
	);

	this->runAction(Sequence::create(aBulletFire, delay, callback, NULL));
}

void BulletObject::removeBullet()
{
	this->removeFromParent();
}
void BulletObject::preventShooting()
{
	_isShooting = false;
}

void BulletObject::update(float delta)
{
	if (_willBeDestroy)
	{
		if (_onBulletDestroyCallback)
		{
			_onBulletDestroyCallback(this);
		}
		stopAllActions();
		this->removeFromParent();
		_willBeDestroy = false;
	}
	if (!_isShooting)
	{
		this->removeFromParent();
	}
}