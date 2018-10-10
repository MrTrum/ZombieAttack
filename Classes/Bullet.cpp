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
	//add sprite
	_sprBullet = Sprite::create("test_bullet.png");
	_sprBullet->setPosition(winSize.width * 0.1f, winSize.height * 0.12f);
	//this->setContentSize(_sprBullet->getContentSize());
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(_sprBullet);
	_sprBullet->setScale(0.01f);
	//apply physics
	PhysicsBody* _BulletPhysicsBody = PhysicsBody::createBox(Size(820,450),
		PhysicsMaterial(0.1f, 0.5f, 0.0f));
	_BulletPhysicsBody->setDynamic(false);
	_BulletPhysicsBody->setCategoryBitmask(BULLET_CATEGORY_BITMASK); // 0010
	_BulletPhysicsBody->setCollisionBitmask(BULLET_COLLISION_AND_CONTACT_BITMASK); // 0001
	_BulletPhysicsBody->setContactTestBitmask(BULLET_COLLISION_AND_CONTACT_BITMASK);
	_sprBullet->setPhysicsBody(_BulletPhysicsBody);

	return true;
}
void Bullet::BulletFire(float locationX, float locationY)
{	
	Size winSize = Director::getInstance()->getWinSize();
	int offX = locationX - _sprBullet->getPosition().x;
	int offY = locationY - _sprBullet->getPosition().y;

	if (offX <= 0) return;

	int realX = winSize.width + (_sprBullet->getContentSize().width / 2);

	float ratio = (float)offY / (float)offX;

	//int realY = winSize.height + (_bullet->getContentSize().height / 2);
	int realY = (realX * ratio) + _sprBullet->getPosition().y;
	auto realDest = Point(realX, realY);

	int offRealX = realX - _sprBullet->getPosition().x;
	int offRealY = realY - _sprBullet->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));

	float velocity = BULLET_VEC;

	float realMoveDuration = length / velocity;
	auto bulletFire = MoveTo::create(realMoveDuration, realDest);
	_sprBullet->runAction(bulletFire);
}