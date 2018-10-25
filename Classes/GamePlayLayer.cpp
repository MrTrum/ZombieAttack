#include "GamePlayLayer.h"
#include "BackgroundLayer.h"
#include "Hero.h"
#include "Base.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include "Zombie.h"
#include "Parameter.h"
#include "GameObject.h"
#include "PoolZombie.h"


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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite.plist", "sprite.png");

	Size winSize = Director::getInstance()->getWinSize();

	/*Phần Zombie*/
	//Set tấm ảnh sau khi texturePacker
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsZombie.plist", "images/assetsZombie.png");


	auto poolZombie = PoolZombie::create();
	this->addChild(poolZombie);

	auto listenEventPhysic = EventListenerPhysicsContact::create();
	listenEventPhysic->onContactBegin = CC_CALLBACK_1(GamePlayLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenEventPhysic, this);

	return true;
}

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
	return true;
}








