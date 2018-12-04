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
}

float BulletObject::getDamage()
{
	return _Dmg;
}

void BulletObject::onCollission(GameObject *obj)
{
	poolAndRemoveBullet();
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
		poolAndRemoveBullet();
	}
	);
	this->runAction(Sequence::create(aBulletFire, callback, NULL));
	_motion = MotionStreak::create(0.2f, 5.0f, 15.0f, Color3B::WHITE, "trail_red.png");
	this->getParent()->addChild(_motion);
	_motion->retain();
	_motion->runAction(aBulletFire->clone());
	_motion->setPosition(this->getPosition());
}

void BulletObject::setDamageBullet(int Dmg)
{
	_Dmg = Dmg;
}
void BulletObject::poolAndRemoveBullet()
{
	auto removeBullet = CallFunc::create([=]
	{
		this->removeFromParent();
		stopAllActions();
		_motion->removeFromParent();
		if (_onBulletDestroyCallback)
		{
			_onBulletDestroyCallback(this);
		}
	});
	this->runAction(Sequence::create(DelayTime::create(0.025f), removeBullet, nullptr));
	/*_willBeDestroy = false;*/
}