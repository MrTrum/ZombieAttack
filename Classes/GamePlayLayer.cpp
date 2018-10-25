#include "GamePlayLayer.h"
#include "BackgroundLayer.h"
#include "Hero.h"
#include "Base.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include "Zombie.h"
#include "Parameter.h"
<<<<<<< HEAD
#include "GameObject.h"
#include "PoolZombie.h"


=======

>>>>>>> 66a4e0b2ce8c4a497db11a83ce597bca9992a3bd
USING_NS_CC;

GamePlayLayer::GamePlayLayer()
{
}

GamePlayLayer::~GamePlayLayer()
{
}

Scene * GamePlayLayer::createGamePlayLayer()
{
	Scene* scene = Scene::createWithPhysics();
	PhysicsWorld* world = scene->getPhysicsWorld();
	//remember to turn off debug when release
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	GamePlayLayer* node = GamePlayLayer::create();
	scene->addChild(node);
	return scene;
}
bool GamePlayLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->removeAllChildren();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite.plist",
		"sprite.png");

	Size winSize = Director::getInstance()->getWinSize();

	/*Phần Zombie*/
	//Set tấm ảnh sau khi texturePacker
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsZombie.plist", "images/assetsZombie.png");

<<<<<<< HEAD

	auto poolZombie = PoolZombie::create();
	this->addChild(poolZombie);

	auto listenEventPhysic = EventListenerPhysicsContact::create();
	listenEventPhysic->onContactBegin = CC_CALLBACK_1(GamePlayLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenEventPhysic, this);
=======
	//Gọi zombie
	auto zombie = Zombie::create();
	addChild(zombie, 3);

	/*UI*/
	//_Coin = Coin::create();
	//_Coin->setPosition(winSize / 2);
	//this->addChild(_Coin);
>>>>>>> 66a4e0b2ce8c4a497db11a83ce597bca9992a3bd

	return true;
}

<<<<<<< HEAD
bool GamePlayLayer::onContactBegin(PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	GameObject *objA = static_cast<GameObject*>(a->getNode());
	GameObject *objB = static_cast<GameObject*>(b->getNode());

	if (objA && objB)
	{
		objB->onCollission(objA);
		objA->onCollission(objB);
	}
=======
bool GamePlayLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*)
{
	_hero->shootAnimation();
	Shooting(touch);
>>>>>>> 66a4e0b2ce8c4a497db11a83ce597bca9992a3bd
	return true;
}



<<<<<<< HEAD





=======
void GamePlayLayer::onTouchEnded(Touch* touch, Event* event) {
	
}

void GamePlayLayer::Shooting(Touch *touch)
{

	Point location = touch->getLocationInView();
	location = Director::getInstance()->convertToGL(location);
	_bullet = Bullet::create();
	this->addChild(_bullet, 200);
	_bullet->BulletFire(location.x, location.y);

}
>>>>>>> 66a4e0b2ce8c4a497db11a83ce597bca9992a3bd
