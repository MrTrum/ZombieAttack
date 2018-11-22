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
#include <ui/UIWidget.h>
#include "Zombie/CreateTestLine.h"
#include "PoolObject/PoolBullet.h"
#include "Dynamite.h"
#include "PoolObject/PoolExplo.h"
#include "ShakeAction.h"

USING_NS_CC;

GamePlayLayer::GamePlayLayer() : scenePlay(4)
{
	_totalBullet = 90;
	_dynStock = 5;
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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist",
		"icon.png");
	//add BG
	_bg = BackgroundLayer::create();
	this->addChild(_bg);
	//add hero
	_hero = Hero::create();
	this->addChild(_hero, 3);
	_hero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_hero->setPosition(winSize.width * 0.17f, winSize.height * 0.16f);
	this->schedule(schedule_selector(GamePlayLayer::updatePressed), 0.18f);
	_poolBullet = new PoolBullet();
	//dynamite
	_poolDynamite = new PoolExplo();
	_dynamite = _poolDynamite->createExplo(Vec2(0.0f, 0.0f));
	this->addChild(_dynamite);
	_iconDynamite = Sprite::create("btn_dynamite.png");
	addChild(_iconDynamite, 200);
	_iconDynamite->setPosition(Vec2(winSize.width * 0.75f, winSize.height * 0.87f));
	_iconDynamite->setTag(555);
	_dynLeft = Label::createWithTTF(StringUtils::format("%02d", _dynStock), "fonts/Marker Felt.ttf", 20);
	_iconDynamite->addChild(_dynLeft);
	_dynLeft->setPosition(Vec2(50.0f,15.0f));
	_dynLeft->enableOutline(cocos2d::Color4B::BLACK, 3);
	_outputTxt = Label::createWithTTF("", "fonts/Creepster-Regular.ttf", 80);
	_outputTxt->setVisible(false);
	addChild(_outputTxt, 2);
	_outputTxt->setColor(cocos2d::Color3B::GREEN);
	_outputTxt->enableOutline(cocos2d::Color4B::RED, 2);
	_outputTxt->enableShadow(Color4B::RED, Size(10, -10), -5);
	_outputTxt->setPosition(winSize.width * 0.5f, winSize.height * 0.75f);
	Blink *rdTxtBlink = Blink::create(5, 12);
	_outputTxt->runAction(rdTxtBlink);
	_bulletInMag = Label::createWithTTF(StringUtils::format("%02d", _Bullet) , "fonts/Marker Felt.ttf", 20);
	addChild(_bulletInMag, 2);
	_bulletInMag->enableOutline(cocos2d::Color4B::RED, 2);
	_bulletInMag->setPosition(winSize.width * 0.1f, winSize.height * 0.95f);

	throwOutputText("READY !!!!", 5);
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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsSkill.plist", "images/assetsSkill.png");

	auto poolZombie = PoolZombie::create(this, scenePlay);
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
	// tạo số tiền
	_Money = Money::create();
	_Money->setMoney(_totalMoney);
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
	//Level
	_Bullet = NUMBER_BULLET_M4A1;
	_gunM4A1 = M4A1::create();
	_gunM4A1->_Stats.setStats(DAMAGE_M4A1*1.5*_gunM4A1->_Level, NUMBER_BULLET_M4A1*1.5*_gunM4A1->_Level, PRICE_M4A1*1.5*_gunM4A1->_Level);
	this->addChild(_gunM4A1);
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

void GamePlayLayer::createItems(int randomitem, Vec2 deadPos)
{

}

void GamePlayLayer::createGoldBag(Vec2 deadPos)
{
	auto goldBag = Sprite::create("goldBag.png");
	this->addChild(goldBag, 3);
	goldBag->setName("goldBag");
	goldBag->setScale(0.2f);
	goldBag->setPosition(deadPos);

	auto scaleto = ScaleTo::create(2.0f, 0.3f);

	auto button = CallFunc::create([=]
	{
		auto buttonHide = cocos2d::ui::Button::create("goldBag.png");
		this->addChild(buttonHide, 2);
		buttonHide->setName("buttonHide");
		buttonHide->setScale(0.2f);
		buttonHide->setPosition(deadPos);
		buttonHide->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::testButton, this));
	});

	auto sqe = Sequence::create(scaleto, button, nullptr);
	goldBag->runAction(sqe);
}

void GamePlayLayer::testButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	Size winSize = Director::getInstance()->getWinSize();
	auto goldBag2 = Sprite::create("goldBag.png");
	goldBag2->setName("goldBag2");
	this->addChild(goldBag2, 3);
	goldBag2->setScale(0.2f);
	goldBag2->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	auto scaleto = ScaleTo::create(2.0f, 0.4f);

	auto removeSpritesBag = CallFunc::create([=]
	{
		this->removeChildByName("goldBag");
		this->removeChildByName("goldBag2");
		this->removeChildByName("buttonHide");
	});

	auto sqe = Sequence::create(scaleto, removeSpritesBag, nullptr);
	goldBag2->runAction(sqe);
}

/*Tú*/
void GamePlayLayer::setTotalMoney(int shopMoney)
{
	_totalMoney = shopMoney;
	_Money->setMoney(_totalMoney);
}
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
	_totalMoney = _totalMoney + 100;
	_Money->setMoney(_totalMoney);
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
		_Shop->setCallBack([=](M4A1* Gun)
		{
			this->_Level = Gun->_Level;
			this->_Bullet += Gun->_Stats._BulletNumber;
			_gunM4A1->_Stats = Gun->_Stats;
		});
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
bool GamePlayLayer::isTouchingSprite(Touch* touch)
{
	if (_getDynTag == 555)
	{
		return (ccpDistance(_iconDynamite->getPosition(), this->touchToPoint(touch)) < 100.0f);
	}
	return false;
}
Point GamePlayLayer::touchToPoint(Touch* touch)
{
	return Director::getInstance()->convertToGL(touch->getLocationInView());
}


bool GamePlayLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*)
{
	Point location = touch->getLocationInView();
	_location = CCDirector::sharedDirector()->convertToGL(location);
	if (_iconDynamite->boundingBox().containsPoint(_location) && _iconDynamite->getTag() == 555)
	{
		_getDynTag = 555;
		if (this->isTouchingSprite(touch))
		{
			this->_touchOffset = ccpSub(_iconDynamite->getPosition(),
				this->touchToPoint(touch));
		}
		_isPressed = false;
		return true;
	}
	else
	{
		_isPressed = true;
		return true;
	}
	return false;

}

void GamePlayLayer::onTouchMoved(Touch* touch, Event* event)
{
	Point location = touch->getLocationInView();
	_location = CCDirector::sharedDirector()->convertToGL(location);
	if (touch && _touchOffset.x && _touchOffset.y)
	{
		if (_getDynTag == 555)
			this->_iconDynamite->setPosition(ccpAdd(this->touchToPoint(touch), this->_touchOffset));
	}
}

void GamePlayLayer::onTouchEnded(Touch* touch, Event* event)
{
	Size winSize = Director::getInstance()->getWinSize();
	_isPressed = false;
	Vec2 droppedPos = _iconDynamite->getPosition();
	throwDynamite(droppedPos);
	_iconDynamite->setPosition(Vec2(winSize.width * 0.75f, winSize.height * 0.87f));
	_getDynTag = 0;

}

void GamePlayLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void GamePlayLayer::throwOutputText(std::string txt, int duration)
{
	_outputTxt->setString(txt);
	_outputTxt->setVisible(true);
	DelayTime *readyTime = DelayTime::create(duration);
	CallFunc *removeRdTxt = CallFunc::create([=]
	{

		
		_outputTxt->setVisible(false);
	}
	);
	runAction(Sequence::create(readyTime, removeRdTxt, NULL));
}
void GamePlayLayer::updatePressed(float dt)
{
	if (!_isReloading)
	{
		if (_isPressed)
		{
			if (_Bullet > 0)
			{

				Shooting();
				_Bullet--;
			}
			else
			{
				_isReloading = true;
				throwOutputText("Reloading", 3);
				scheduleOnce(schedule_selector(GamePlayLayer::reloading), 3.0f);
			}
		}
	}
	
	if (_dynStock <= 0)
	{
		_iconDynamite->setSpriteFrame("btn_dynamite_empty.png");
		_iconDynamite->setTag(554);
	}
	if (_dynStock > 0)
	{
		_iconDynamite->setTag(555);
	}
	_dynLeft->setString(StringUtils::format("%02d", _dynStock));
	_bulletInMag->setString(StringUtils::format("%02d", _Bullet));
}

void GamePlayLayer::reloading(float dt)
{
	_totalBullet -= 30;
	_Bullet += 30;
	_isReloading = false;
}

void GamePlayLayer::Shooting()
{
	Size winSize = Director::getInstance()->getWinSize();
	_hero->shootAnimation();
	_bullet = _poolBullet->createBullet(_location.x, _location.y);
	this->addChild(_bullet, 2);
	_bullet->setDamageBullet(_gunM4A1->_Stats._Damage);
	_bullet->setPosition(Vec2(winSize.width * 0.25f, winSize.height * 0.25f));
}

void GamePlayLayer::throwDynamite(Vec2 droppedPos)
{
	Size winSize = Director::getInstance()->getWinSize();
	if (droppedPos.y < winSize.height * 0.3f)
	{
		auto dynamite = Sprite::create("weapon_dynamite.png");
		this->addChild(dynamite, 2);
		dynamite->setPosition(Vec2(winSize.width * 0.25f, winSize.height * 0.25f));
		auto throwto = JumpTo::create(0.5f, droppedPos, droppedPos.y + 10.0f, 1);
		CallFunc *del = CallFunc::create([=] {
			dynamite->removeFromParent();
			_dynStock--;
		});

		dynamite->runAction(Sequence::create(
			throwto, del, nullptr
		));
		CallFunc *callExplo = CallFunc::create([=] {
			_dynamite = _poolDynamite->createExplo(droppedPos);
			this->addChild(_dynamite, 3);
			_dynamite->setPosition(droppedPos);
		});
		runAction(Sequence::create(DelayTime::create(0.5), callExplo, nullptr));
	}
}

