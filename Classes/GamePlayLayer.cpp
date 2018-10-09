﻿#include "GamePlayLayer.h"
#include "BackgroundLayer.h"
#include "Hero.h"
#include "Base.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include "Zombie.h"
#include "Parameter.h"

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

	winSize = Director::getInstance()->getWinSize();

	/*Phần nhân vật*/
	//add BG
	_bg = BackgroundLayer::create();
	this->addChild(_bg);

	//add hero
	_hero = Hero::create();
	this->addChild(_hero, 200);
	//_hero->setPosition(winSize.width * 0.35f, winSize.height * 0.08f);

	//add base
	_base = Base::create();
	this->addChild(_base);

	//add bullet
	//_bullet = Bullet::create();
	//this->addChild(_bullet,200);

	//touch event
	EventListenerTouchOneByOne *listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	/*Phần Zombie*/
	//Set tấm ảnh sau khi texturePacker
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsZombie.plist", "images/assetsZombie.png");

	//Gọi zombie
	auto zombie = Zombie::create();
	addChild(zombie, 3);

	/*UI*/
	//_Coin = Coin::create();
	//_Coin->setPosition(winSize / 2);
	//this->addChild(_Coin);

	return true;
}

bool GamePlayLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*)
{
	_hero->shootAnimation();
	Shooting(touch);
	return true;
}


void GamePlayLayer::onTouchMoved(Touch* touch, Event* event)
{

}

void GamePlayLayer::onTouchEnded(Touch* touch, Event* event) {
	
}

void GamePlayLayer::Shooting(Touch *touch)
{
	_bullet = Bullet::create();
	this->addChild(_bullet, 200);
	
	Point location = touch->getLocationInView();
	location = Director::getInstance()->convertToGL(location);

	int offX = location.x - _bullet->getPosition().x;
	int offY = location.y - _bullet->getPosition().y;
	if (offX <= 0) return;
	float ratio = (float)offY / (float)offX;

	int realX = winSize.width + (_bullet->getContentSize().width / 2);
	int realY = (realX / ratio) + _bullet->getPosition().y;
	auto realDest = Point(realX, realY);
	int offRealX = realX - _bullet->getPosition().x;
	int offRealY = realY - _bullet->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
	float velocity = BULLET_VEC;
	float realMoveDuration = length / velocity;
	auto bulletFire = MoveTo::create(realMoveDuration, realDest);
	_bullet->runAction(bulletFire);
}