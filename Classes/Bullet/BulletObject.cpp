#include "Bullet/BulletObject.h"
#include "Parameter.h"
#include "Zombie/PZombie.h"

#define M16_RECOIL	0.005f

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
	xFromParent = x;
	yFromParent = y;
	//this->setPosition(winSize.width * 0.25f, winSize.height * 0.25f);
	PhysicsBody* _bulletPhysicBody = PhysicsBody::createBox(_sprBullet->getContentSize());
	_bulletPhysicBody->setContactTestBitmask(true);
	_bulletPhysicBody->setDynamic(false);
	_bulletPhysicBody->setGroup(-2);
	this->setPhysicsBody(_bulletPhysicBody);
	this->setTag(TAG_BULLET);
	setScale(0.1f);
	//scheduleOnce(schedule_selector(BulletObject::gunRecoil), M16_RECOIL);
	bulletFire(x, y);
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
	auto winSize = Director::getInstance()->getWinSize();
	this->setPosition(winSize.width * 0.25f, winSize.height * 0.25f);
	this->setVisible(true);
	//scheduleOnce(schedule_selector(BulletObject::gunRecoil), M16_RECOIL);
	bulletFire(x, y);
	scheduleUpdate();
}


void BulletObject::onCollission(GameObject *obj)
{
	if (obj->getTag() == TAG_ZOMBIE)
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
	//Size winSize = Director::getInstance()->getWinSize();
	//float offX = locationX - _sprBullet->getPosition().x;
	//float offY = locationY - _sprBullet->getPosition().y;
	//if (offX <= 0) return;
	//float realX = winSize.width + (_sprBullet->getContentSize().width / 2);
	//float ratio = (float)offY / (float)offX;
	//float realY = (realX * ratio) + _sprBullet->getPosition().y;
	//auto realDest = Point(realX, realY);
	//float angleRadians = atan2f(realY, realX);
	//angleRadians = CC_RADIANS_TO_DEGREES(angleRadians);
	//float offRealX = realX - _sprBullet->getPosition().x;
	//float offRealY = realY - _sprBullet->getPosition().y;
	//float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
	//float velocity = BULLET_VEC;
	//float realMoveDuration = length / velocity;
	//auto aBulletFire = MoveTo::create(realMoveDuration, realDest);
	//_sprBullet->setRotation(-angleRadians);
	auto startPos = this->getPosition();
	auto target = Vec2(locationX, locationY);
	auto distance = target - startPos;
	auto vector = distance.getNormalized() * BULLET_VEC;
	auto aBulletFire = MoveBy::create(1.0f, vector);
	DelayTime *delay = DelayTime::create(1.5);
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