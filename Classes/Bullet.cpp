#include "BulletObject.h"
#include "Bullet.h"
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
	Size winSize = Director::getInstance()->getWinSize();
	_bullet = BulletObject::create();
	addChild(_bullet);
	/*for (int i = 0; i < 8; i++)
	{
		_bullet = BulletObject::create();
		addChild(_bullet);
		BulletPool.pushBack(_bullet);
	}
	_bullet = this->createBullet();
	if (_bullet = nullptr)
	{
		_bullet->removeFromParent();
		addChild(_bullet);
		_bullet->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		_bullet->setVisible(true);
	}*/


	#pragma region sprite and physic Bullet
	//_sprBullet = Sprite::create("test_bullet.png");
	//_sprBullet->setPosition(winSize.width * 0.1f, winSize.height * 0.12f);
	////this->setContentSize(_sprBullet->getContentSize());
	//this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//this->addChild(_sprBullet);
	//_sprBullet->setScale(0.01f);
	////apply physics
	//PhysicsBody* _BulletPhysicsBody = PhysicsBody::createBox(Size(820, 450));
	//_BulletPhysicsBody->setCollisionBitmask(12);
	//_BulletPhysicsBody->setContactTestBitmask(true);
	//_BulletPhysicsBody->setDynamic(false);
	//_sprBullet->setPhysicsBody(_BulletPhysicsBody);
	#pragma endregion

	return true;
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