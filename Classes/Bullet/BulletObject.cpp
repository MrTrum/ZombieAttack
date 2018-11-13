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
	//_sprBullet->setPosition(winSize.width * 0.25f, winSize.height * 0.25f);
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
	DelayTime *delay = DelayTime::create(1.5);
	CallFunc *callback = CallFunc::create([=]
	{
		_willBeDestroy = true;
	}
	);

	this->runAction(Sequence::create(bulletFire, delay, callback, NULL));
}

void BulletObject::removeBullet()
{
	this->removeFromParent();
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
}