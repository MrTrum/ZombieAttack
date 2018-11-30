#include "GameObject/BulletObject.h"
#include "Parameter.h"
#include "GameObject/PZombie.h"
#include "GamePlayLayer.h"

BulletObject::BulletObject()
{
	_willBeDestroy = false;
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
	_bulletPhysicBody = PhysicsBody::createCircle(8.0f);
	_bulletPhysicBody->setContactTestBitmask(true);
	_bulletPhysicBody->setDynamic(false);
	_bulletPhysicBody->setGroup(-2);
	this->setPhysicsBody(_bulletPhysicBody);
	this->setTag(TAG_BULLET);
	scheduleUpdate();
	return true;
}

BulletObject *BulletObject::create()
{
	BulletObject *pRet = new(std::nothrow) BulletObject();
	if (pRet && pRet->init())
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

void BulletObject::reset()
{
	Size winSize = Director::getInstance()->getWinSize();
	this->setVisible(true);
	scheduleUpdate();
}

float BulletObject::getDamage()
{
	return _Dmg;
}

void BulletObject::onCollission(GameObject *obj)
{
	_willBeDestroy = true;
}

void BulletObject::setOnDestroyCallback(OnBulletDestroyCallback callback)
{
	_onBulletDestroyCallback = callback;
}


void BulletObject::bulletFire(Vec2 location)
{
	Size winSize = Director::getInstance()->getWinSize();
	float recoil = random(-15, 40);
	auto startPos = this->getPosition();
	auto target = location;
	auto distance = target - startPos;
	distance.y += recoil;
	vector = distance.getNormalized() * BULLET_VEC;
	auto aBulletFire = MoveBy::create(1.0f, vector);
	CallFunc *callback = CallFunc::create([=]
	{
		_willBeDestroy = true;
	}
	);
	this->runAction(Sequence::create(aBulletFire, callback, NULL));
	_motion = MotionStreak::create(0.2, 5, 15, Color3B::WHITE, "trail_red.png");
	this->getParent()->addChild(_motion);
	_motion->retain();
	_motion->runAction(aBulletFire->clone());
	_motion->setPosition(this->getPosition());
}

void BulletObject::setDamageBullet(int Dmg)
{
	_Dmg = Dmg;
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
		_motion->removeFromParent();
		_willBeDestroy = false;
	}
}