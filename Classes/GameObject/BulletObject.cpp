#include "GameObject/BulletObject.h"
#include "Parameter.h"
#include "GameObject/PZombie.h"

#define BULLET_VEC	1000.0f
BulletObject::BulletObject()
{
}

BulletObject::~BulletObject()
{
	CC_SAFE_RELEASE(_motion);
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
	this->setPosition(winSize.width * 0.25f, winSize.height * 0.25f);
	this->setVisible(true);
	scheduleUpdate();
}

float BulletObject::getDamage()
{
	return _Dmg;
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

void BulletObject::bulletFire(Vec2 location)
{
	Size winSize = Director::getInstance()->getWinSize();
	float recoil = random(-15, 40);
	auto startPos = this->getPosition();
	auto target = location;
	auto distance = target - startPos;
	distance.y += recoil;
	auto vector = distance.getNormalized() * BULLET_VEC;
	auto aBulletFire = MoveBy::create(1.0f, vector);
	CallFunc *callback = CallFunc::create([=]
	{
		_willBeDestroy = true;
	}
	);
	runAction(Sequence::create(aBulletFire, callback, nullptr));
	_motion = MotionStreak::create(0.5, 20, 15, Color3B::WHITE, "trail_red.png");
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