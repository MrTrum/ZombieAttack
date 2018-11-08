#include "GamePlayLayer.h"
#include "BackgroundLayer.h"
#include "Hero/Hero.h"
#include "SimpleAudioEngine.h"
#include "Parameter.h"
#include "GameObject.h"
#include "Bullet/BulletObject.h"
#include "PoolObject/PoolZombie.h"
#include "UI/Coin/Coin.h"
#include "Zombie/TestLine2.h"
#include "Zombie/TestLine.h"
#include <ui/UIWidget.h>
#include "Zombie/CreateTestLine.h"
#include "PoolObject/PoolBullet.h"
#include "Dynamite.h"

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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("redneck_idle.plist",
		"redneck_idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon/shotgun.plist",
		"weapon/shotgun.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("explosion.plist",
		"explosion.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SGidle.plist",
		"SGidle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon/SGidle.plist",
		"weapon/SGidle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon/M16idle.plist",
		"weapon/M16idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon/M16firing.plist",
		"weapon/M16firing.png");

	//add BG
	_bg = BackgroundLayer::create();
	this->addChild(_bg, 1);

	//add hero
	_hero = Hero::create();
	this->addChild(_hero, 3);
	_hero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_hero->setPosition(winSize.width * 0.17f, winSize.height * 0.16f);

	_poolBullet = new PoolBullet();
	//dynamite
	_iconDynamite = Sprite::create("btn_dynamite.png");
	addChild(_iconDynamite, 2);
	_iconDynamite->setPosition(Vec2(winSize.width * 0.75f, winSize.height * 0.06f));
	_iconDynamite->setTag(200);
	auto readyTxt = Label::createWithTTF("READY !!!", "fonts/Creepster-Regular.ttf", 80);
	addChild(readyTxt, 2);
	readyTxt->setColor(cocos2d::Color3B::GREEN);
	readyTxt->enableOutline(cocos2d::Color4B::RED, 2);
	readyTxt->enableShadow(Color4B::RED, Size(10, -10), -5);
	readyTxt->setPosition(winSize.width * 0.5f, winSize.height * 0.75f);
	Blink *rdTxtBlink = Blink::create(5, 12);
	readyTxt->runAction(rdTxtBlink);
	DelayTime *readyTime = DelayTime::create(5);
	CallFunc *removeRdTxt = CallFunc::create([=]
	{
		readyTxt->removeFromParent();
	}
	);
	runAction(Sequence::create(readyTime, removeRdTxt, NULL));
	//touch event
	EventListenerTouchOneByOne *listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GamePlayLayer::onTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
	listenerTouch->onTouchCancelled = CC_CALLBACK_2(GamePlayLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	/*Thanh*/
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
	this->addChild(_Money, 4);
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

void GamePlayLayer::createGoldBag(Vec2 deadPos)
{
	auto goldBag = Sprite::create("goldBag.png");
	this->addChild(goldBag, 3);
	goldBag->setScale(0.2f);
	goldBag->setPosition(deadPos);

	auto scaleto = ScaleTo::create(3.0f, 0.4f);
	goldBag->runAction(scaleto);
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
void GamePlayLayer::moneyChange()
{
	_totalMoney = _totalMoney + 1;
	_Money->setMoney(_totalMoney);
}
void GamePlayLayer::update(float dt)
{

}
void GamePlayLayer::CoinFly(Vec2 deadPos)
{
	CallFunc* loop = CallFunc::create([=]
	{
		_Coin = Coin::create();
		this->addChild(_Coin, 10);
		_Coin->setPosition(deadPos);
		_Coin->PlayAnimation();
		_checkMoney = _Coin->FlyAnimation(_iconPos, [=] {
			this->moneyChange();
		});

	});
	Sequence* coinloop = Sequence::create(loop, DelayTime::create(0.5), nullptr);
	this->runAction(coinloop);
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
	this->addChild(_IconCoin, 4);
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
	Point location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	if (_iconDynamite->boundingBox().containsPoint(location) && _iconDynamite->getTag() == 200)
	{
		getTag = 200;
		if (this->isTouchingSprite(touch))
		{
			this->touchOffset = ccpSub(_iconDynamite->getPosition(),
				this->touchToPoint(touch));
		}
		return true;
	}
	else
	{
		_hero->shootAnimation();
		Shooting(touch);
		return true;
	}
	return false;
}

void GamePlayLayer::onTouchMoved(Touch* touch, Event* event)
{
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);


	if (touch && touchOffset.x && touchOffset.y)
	{
		if (getTag == 1)
			this->_iconDynamite->setPosition(ccpAdd(this->touchToPoint(touch), this->touchOffset));
	}
	else
	{
		_hero->shootAnimation();
		Shooting(touch);
	}
}

void GamePlayLayer::onTouchEnded(Touch* touch, Event* event)
{
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 droppedPos = _iconDynamite->getPosition();
	/*_dynamite = Dynamite::create();
	this->addChild(_dynamite);
	_dynamite->throwDynamite(droppedPos.x, droppedPos.y);
	_iconDynamite->setPosition(Vec2(winSize.width * 0.75f, winSize.height * 0.12f));*/
}

void GamePlayLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void GamePlayLayer::Shooting(Touch *touch)
{
	auto winSize = Director::getInstance()->getWinSize();
	Point location = touch->getLocationInView();
	location = Director::getInstance()->convertToGL(location);
	//_poolBullet = PoolBullet::create(location.x, location.y);
	//this->addChild(_poolBullet,10);
	auto bullet = _poolBullet->createBullet(location.x, location.y);
	this->addChild(bullet);
	bullet->setPosition(winSize.width * 0.25f, winSize.height * 0.25f);
}
bool GamePlayLayer::isTouchingSprite(Touch* touch)
{
	if (getTag == 200)
	{
		return (ccpDistance(_iconDynamite->getPosition(), this->touchToPoint(touch)) < 100.0f);
	}
	return false;
}
Point GamePlayLayer::touchToPoint(Touch* touch)
{
	// convert the touch object to a position in our cocos2d space
	return Director::getInstance()->convertToGL(touch->getLocationInView());
}









