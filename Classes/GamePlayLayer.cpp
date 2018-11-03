#include "GamePlayLayer.h"
#include "BackgroundLayer.h"
#include "Hero/Hero.h"
#include "Base/Base.h"
#include "PoolObject/Bullet.h"
#include "SimpleAudioEngine.h"
#include "Parameter.h"
#include "GameObject.h"
#include "PoolObject/PoolZombie.h"
#include "UI/Coin/Coin.h"
#include "Zombie/TestLine2.h"
#include "Zombie/TestLine.h"
#include <ui/UIWidget.h>
#include "Zombie/CreateTestLine.h"


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
	Size winSize = Director::getInstance()->getWinSize();
	this->removeAllChildren();
	/*Khoa*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Redneck.plist",
		"Redneck.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shotgun.plist",
		"shotgun.png");

	//add BG
	_bg = BackgroundLayer::create();
	this->addChild(_bg, 1);

	//add hero
	_hero = Hero::create();
	this->addChild(_hero, 3);
	_hero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_hero->setPosition(winSize.width * 0.17f, winSize.height * 0.16f);
	_hero->playAnimation("Redneck", 16, 4,100);
	_hero->getHealthBar(100);

	
	//touch event
	EventListenerTouchOneByOne *listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GamePlayLayer::onTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
	listenerTouch->onTouchCancelled = CC_CALLBACK_2(GamePlayLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	/*Phần Zombie*/
	//Set tấm ảnh sau khi texturePacker
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsZombie.plist", "images/assetsZombie.png");


	auto poolZombie = PoolZombie::create(this);
	this->addChild(poolZombie, 3);

	


	auto testline2 = TestLine2::create();
	this->addChild(testline2, 3);

	auto listenEventPhysic = EventListenerPhysicsContact::create();
	listenEventPhysic->onContactBegin = CC_CALLBACK_1(GamePlayLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenEventPhysic, this);

	/*Tú*/

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/coin.plist", "images/coin.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/numbers.plist", "images/numbers.png");
	//tao icon tien
	this->IconCoinCreate();
	// tạo tiền
	this->scheduleUpdate();
	// tạo số tiền
	_Money = Money::create();
	this->addChild(_Money,4);
	 //tao nut pause
	auto _pauseBtn = cocos2d::ui::Button::create("images/PauseButton.png");
	_pauseBtn->setPosition(Vec2(winSize.width*0.025f, winSize.height*0.968f));
	_pauseBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::TouchPauseButton, this));

	this->addChild(_pauseBtn, 4);
	// all button
	_resumeBtn = cocos2d::ui::Button::create("images/PlayButton4.png");
	_resumeBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.7f));
	_resumeBtn->setScale(1.0f);
	_resumeBtn->setTag(1);
	_resumeBtn->setVisible(false);

	_resumeBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::TouchResumeButton, this));
	this->addChild(_resumeBtn, 4);
	//Label Play
	_labelResume = Label::createWithTTF("Resume", "fonts/kenvector_future.ttf", 25);
	_labelResume->setPosition(_resumeBtn->getPosition());
	_labelResume->setVisible(false);
	this->addChild(_labelResume, 4);
	_shopBtn = cocos2d::ui::Button::create("images/ShopButton.png");
	_shopBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));
	_shopBtn->setScale(1.0f);
	_shopBtn->setTag(1);
	_shopBtn->setVisible(false);
	_shopBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::TouchShopButton, this));
	this->addChild(_shopBtn, 4);
	//Label Play
	_labelShop = Label::createWithTTF("Shop", "fonts/kenvector_future.ttf", 25);
	_labelShop->setPosition(_shopBtn->getPosition());
	_labelShop->setVisible(false);
	this->addChild(_labelShop, 4);
	//Button Quit
	_quitBtn = cocos2d::ui::Button::create("images/QuitButton3.png");
	_quitBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.3f));
	_quitBtn->setScale(1.0f);
	_quitBtn->setTag(1);
	_quitBtn->setVisible(false);
	_quitBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::TouchQuitButton, this));
	this->addChild(_quitBtn, 4);
	//Label Quit
	_labelQuit = Label::createWithTTF("Quit", "fonts/kenvector_future.ttf", 25);
	_labelQuit->setPosition(_quitBtn->getPosition());
	_labelQuit->setVisible(false);
	this->addChild(_labelQuit, 4);

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

/*Tú*/
void GamePlayLayer::resumeGame()
{
	Director::getInstance()->resume();
	_resumeBtn->setVisible(false);
	_labelResume->setVisible(false);
	_quitBtn->setVisible(false);
	_labelQuit->setVisible(false);
	_shopBtn->setVisible(false);
	_labelShop->setVisible(false);
	_Money->setVisible(true);
}
void GamePlayLayer::removeCoin()
{
	_Money->setMoney(_totalMoney);
	this->removeChildByTag(5);
}
void GamePlayLayer::update(float dt)
{
	if (_checkMoney == true)
	{
		_totalMoney = _totalMoney + 1;
		CallFunc* remove = CallFunc::create(CC_CALLBACK_0(GamePlayLayer::removeCoin, this));
		Sequence* delayremove = Sequence::create(DelayTime::create(0.5), remove, nullptr);
		this->runAction(delayremove);
		_checkMoney = false;
	}
}

void GamePlayLayer::IconCoinCreate()
{
	Size winSize = Director::getInstance()->getWinSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/coin.plist",
		"images/coin.png");
	auto _IconCoin = Sprite::createWithSpriteFrameName("coin1.png");
	_IconCoin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_IconCoin->setScale(0.15f);
	_IconCoin->setPosition(Vec2(winSize.width*0.57f, winSize.height*0.968f));
	_iconPos = _IconCoin->getPosition();
	this->addChild(_IconCoin,4);
}

void GamePlayLayer::CoinFly(Vec2 deadPos)
{
	CallFunc* loop = CallFunc::create([=]
	{
		_Coin = Coin::create();
		_Coin->setTag(5);
		this->addChild(_Coin, 10);
		_Coin->setPosition(deadPos);
		_Coin->PlayAnimation();
		_checkMoney = _Coin->FlyAnimation(_iconPos);
	});
	Sequence* coinloop = Sequence::create(loop, DelayTime::create(0.7), nullptr);
	this->runAction(coinloop);
}

void GamePlayLayer::TouchPauseButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->pause();
		_resumeBtn->setVisible(true);
		_labelResume->setVisible(true);
		_quitBtn->setVisible(true);
		_labelQuit->setVisible(true);
		_shopBtn->setVisible(true);
		_labelShop->setVisible(true);
	}
}

void GamePlayLayer::TouchResumeButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->resumeGame();
	}
}

void GamePlayLayer::TouchShopButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		_Shop = StoreLayer::create();
		_Shop->setGamePlayLayerPtr(this);
		_Shop->setTotalMoney(_totalMoney);
		_Money->setVisible(false);
		this->addChild(_Shop, 10);
	}
}
void GamePlayLayer::TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->end();
	}
}

/*Khoa*/
bool GamePlayLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*)
{
	/*Point touchLoc = touch->getLocationInView();

	if (_dynamiteBtn->getBoundingBox().containsPoint(touchLoc))
	{
		return true;
	}
	else
	{
		_hero->shootAnimation();
		Shooting(touch);
		return true;
	}*/
	return false;
	
}


void GamePlayLayer::onTouchMoved(Touch* touch, Event* event)
{
	
	_hero->shootAnimation();
	Shooting(touch);
}

void GamePlayLayer::onTouchEnded(Touch* touch, Event* event) {
}

void GamePlayLayer::onTouchCancelled(Touch* touch, Event* event) {
	Size winSize = Director::getInstance()->getWinSize();
	_dynamiteBtn->setPosition(Vec2(winSize.width * 0.75f, winSize.height * 0.07f));
}

void GamePlayLayer::Shooting(Touch *touch)
{

	_bullet = Bullet::create();
	this->addChild(_bullet, 200);
	Point location = touch->getLocationInView();
	location = Director::getInstance()->convertToGL(location);
	_bullet->BulletFire(location.x, location.y);

}







