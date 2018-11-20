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
	_sprBullet->setScale(0.15);
	_sprBullet->setVisible(false);
	PhysicsBody* _bulletPhysicBody = PhysicsBody::createCircle(4.0f);
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

void BulletObject::bulletFire(float locationX, float locationY)
{
	Size winSize = Director::getInstance()->getWinSize();
	float recoil = random(0, 0);
	auto startPos = this->getPosition();
	auto target = Vec2(locationX, locationY);
	auto distance = target - startPos;
	distance.y += recoil;
	auto vector = distance.getNormalized() * BULLET_VEC;
	auto aBulletFire = MoveBy::create(1.0f, vector);
	auto aBulletFireClone = MoveBy::create(1.0f, vector);
	CallFunc *callback = CallFunc::create([=]
	{
		_willBeDestroy = true;
	}
	);
	motion = MotionStreak::create(0.5, 20, 15, Color3B::WHITE, "trail_red.png");
	this->addChild(motion);
	motion->runAction(aBulletFireClone);
	this->runAction(Sequence::create(aBulletFire, callback, NULL));
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
		motion->removeFromParent();
		_willBeDestroy = false;
	}
}