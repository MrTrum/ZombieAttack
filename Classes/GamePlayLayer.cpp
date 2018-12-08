#include "GamePlayLayer.h"
#include "Parameter.h"
#include "AudioEngine.h"
#include "GameObject/GameObject.h"
#include "GameObject/Border.h"
#include "GameObject/Hero.h"
#include "GameObject/Dynamite.h"
#include "GameObject/BulletObject.h"
#include "GameObject/CreateTestLine.h"
#include "GameObject/SkillZombie.h"
#include "PoolObject/PoolZombie.h"
#include "PoolObject/PoolBullet.h"
#include "PoolObject/PoolExplo.h"
#include "PoolObject/PoolSkill.h"
#include "BackgroundLayer.h"
#include "UI/Coin/Coin.h"
#include <ui/UIWidget.h>
#include "ShakeAction.h"
#include "Store.h"


USING_NS_CC;

#define TAG_DYNAMITE_BTN	111
#define TAG_HEALTH_BTN		222
GamePlayLayer::GamePlayLayer()
{
	_totalBullet = 0;
	_Bullet = 0;
	_baseBullet = 0;
	_dynStock = 5;
	_getDynTag = 0;
	_Level = 1;
	_LevelHP = 1;
	_totalHP = 0;
}

GamePlayLayer *GamePlayLayer::create(int playStage)
{
	GamePlayLayer *pRet = new(std::nothrow) GamePlayLayer();
	if (pRet && pRet->init(playStage))
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

GamePlayLayer::~GamePlayLayer()
{
}

Scene * GamePlayLayer::createGamePlayLayer(int stage)
{
	Scene* scene = Scene::createWithPhysics();
	PhysicsWorld* world = scene->getPhysicsWorld();
	//remember to turn off debug when release
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	GamePlayLayer* node = GamePlayLayer::create(stage);
	scene->addChild(node);
	return scene;
}

bool GamePlayLayer::init(int playStage)
{
	if (!Node::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	this->removeAllChildren();
	scenePlay = playStage;

#pragma region Plists
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("redneck_idle.plist", "redneck_idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon/M16idle.plist", "weapon/M16idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon/M16firing.plist", "weapon/M16firing.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist", "icon.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsZombie.plist", "images/assetsZombie.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsSkill.plist", "images/assetsSkill.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/coin.plist", "images/coin.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/numbers.plist", "images/numbers.png");
#pragma endregion

#pragma region Components
	//add BG
	Director::getInstance()->setClearColor(cocos2d::Color4F::WHITE);
	_bg = BackgroundLayer::create();
	this->addChild(_bg);
	auto _gBorder = Border::create();
	addChild(_gBorder);
	//add hero
	_hero = Hero::create();
	this->addChild(_hero, 3);
	_hero->setPosition(winSize.width * 0.17f, winSize.height * 0.16f);
	this->schedule(schedule_selector(GamePlayLayer::updatePressed), 0.167f);
	//dynamite
	_poolBullet = new PoolBullet();
	_poolDynamite = new PoolExplo();
	addUI();
	//touch event
	EventListenerTouchOneByOne *listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GamePlayLayer::onTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
	listenerTouch->onTouchCancelled = CC_CALLBACK_2(GamePlayLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	auto locationHero = _hero->getPosition();

	auto getline = CreateTestLine::create(TAG_LINE, locationHero);
	getline->setPosition(winSize.width * 0.9f, 0.0f);
	this->addChild(getline, 3);

	auto getline2 = CreateTestLine::create(TAG_LINE2, locationHero);
	getline2->setPosition(winSize.width * 0.4f, 0.0f);
	this->addChild(getline2, 3);

	auto poolZombie = PoolZombie::create(this, scenePlay);
	this->addChild(poolZombie, 3);

	auto listenEventPhysic = EventListenerPhysicsContact::create();
	listenEventPhysic->onContactBegin = CC_CALLBACK_1(GamePlayLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenEventPhysic, this);
#pragma endregion

#pragma region UI
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
	_resumeBtn = cocos2d::ui::Button::create("btn_style1.png");
	_resumeBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.7f));
	_resumeBtn->setScale(0.7f);
	_resumeBtn->setTag(1);
	_resumeBtn->setVisible(false);

	_resumeBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::TouchResumeButton, this));
	this->addChild(_resumeBtn, 4);
	//Label Play
	_labelResume = Label::createWithTTF("Resume", "fonts/kenvector_future.ttf", 25);
	_labelResume->setPosition(_resumeBtn->getPosition());
	_labelResume->setRotation(5);
	_labelResume->setVisible(false);
	this->addChild(_labelResume, 4);
	_shopBtn = cocos2d::ui::Button::create("btn_style2.png");
	_shopBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));
	_shopBtn->setScale(0.7f);
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
	_quitBtn = cocos2d::ui::Button::create("btn_style3.png");
	_quitBtn->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.3f));
	_quitBtn->setScale(0.7f);
	_quitBtn->setTag(1);
	_quitBtn->setVisible(false);
	_quitBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::TouchQuitButton, this));
	this->addChild(_quitBtn, 4);
	//Label Quit
	_labelQuit = Label::createWithTTF("Quit", "fonts/kenvector_future.ttf", 25);
	_labelQuit->setPosition(_quitBtn->getPosition());
	_labelQuit->setVisible(false);
	_labelQuit->setRotation(-5);
	this->addChild(_labelQuit, 4);
	//Level
	def = UserDefault::getInstance();
	_gunM4A1 = M4A1::create();
	auto test = def->getStringForKey("CheckPlayer", "New");
	def->setIntegerForKey("CurrentBullet", 30);
	_Bullet = def->getIntegerForKey("CurrentBullet");
	def->setIntegerForKey("CurrentBaseBullet", NUMBER_BULLET_SHOOT + (10 * _gunM4A1->_Level));
	_baseBullet = def->getIntegerForKey("CurrentBaseBullet");
	def->setIntegerForKey("CurrentTotalBullet", NUMBER_BULLET_M4A1 + (NUMBER_BULLET_M4A1 * 0.25*_gunM4A1->_Level)-30);
	_totalBullet = def->getIntegerForKey("CurrentTotalBullet");
	/*if (test == "New")
	{
		def->setIntegerForKey("CurrentBullet", 30);
		_Bullet = def->getIntegerForKey("CurrentBullet");
		def->setIntegerForKey("CurrentBaseBullet", NUMBER_BULLET_M4A1 + (30 * _gunM4A1->_Level));
		_baseBullet = def->getIntegerForKey("CurrentBaseBullet");
		def->setIntegerForKey("CurrentTotalBullet", _baseBullet - 30);
		_totalBullet = def->getIntegerForKey("CurrentTotalBullet");

	}
	else
	{
		_Bullet = def->getIntegerForKey("CurrentBullet");
		_baseBullet = def->getIntegerForKey("CurrentBaseBullet");
		_totalBullet = def->getIntegerForKey("CurrentTotalBullet");
	}*/
	_baseBullet = NUMBER_BULLET_M4A1 + (NUMBER_BULLET_M4A1 * 0.25*_gunM4A1->_Level);
	_gunM4A1->baseBullet = _baseBullet;
	_gunM4A1->_Stats.setStats(DAMAGE_M4A1 + (10 * _gunM4A1->_Level), NUMBER_BULLET_SHOOT + (10 * _gunM4A1->_Level), PRICE_M4A1*1.5*_gunM4A1->_Level);
	this->addChild(_gunM4A1);
	//HP
	def->getInstance()->getIntegerForKey("LevelHP", 1);
	_HP = new HP();
	_HP->getLevel();
	this->addChild(_HP);
	scheduleUpdate();
	//Icon HP
	/*_iconHP = Sprite::create("icon_potion.png");
	_iconHP->setPosition(Vec2(winSize.width * 0.85f, winSize.height * 0.87f));
	_iconHP->setTag(TAG_HEALTH_BTN);
	this->addChild(_iconHP);*/
	
	auto buttonHide = cocos2d::ui::Button::create("icon_potion.png");
	this->addChild(buttonHide, 2);
	buttonHide->setPosition(Vec2(winSize.width * 0.85f, winSize.height * 0.87f));
	buttonHide->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::potionButton, this));
	_numberHP = Label::createWithTTF(StringUtils::format("%02d", _totalHP), "fonts/Marker Felt.ttf", 20);
	buttonHide->addChild(_numberHP);
	_numberHP->setPosition(Vec2(50.0f, 15.0f));
	_numberHP->enableOutline(cocos2d::Color4B::BLACK, 3);
#pragma endregion

	return true;
}

#pragma region Buttons Event
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

void GamePlayLayer::TouchPauseButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->pause();
		_iconDynamite->setTag(554);
		_woodPane->setVisible(true);
		_blurBG->setVisible(true);
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
		Director::getInstance()->resume();
		_iconDynamite->setTag(TAG_DYNAMITE_BTN);
		_woodPane->setVisible(false);
		_blurBG->setVisible(false);
		_resumeBtn->setVisible(false);
		_labelResume->setVisible(false);
		_quitBtn->setVisible(false);
		_labelQuit->setVisible(false);
		_shopBtn->setVisible(false);
		_labelShop->setVisible(false);
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
			this->_totalBullet = Gun->baseBullet;
			_Bullet = Gun->_Stats._BulletNumber;
			_gunM4A1->_Stats = Gun->_Stats;
			if (Gun->recharge == true)
			{
				this->rechargeBullet();
			}
		});
		_Shop->setCallBackHP([=](HP* Hp)
		{
			this->_LevelHP = Hp->Level;
			_HP->itemStat = Hp->itemStat;
			if (Hp->recharge == true)
			{
				this->rechargeHP();
			}
		});
		_Shop->setGamePlayLayerPtr(this);
		_Shop->setTotalMoney(_totalMoney);
		_Money->setVisible(false);
		_resumeBtn->setVisible(false);
		_labelResume->setVisible(false);
		_quitBtn->setVisible(false);
		_labelQuit->setVisible(false);
		_shopBtn->setVisible(false);
		_labelShop->setVisible(false);
		this->addChild(_Shop, 10);
	}
}

void GamePlayLayer::TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->end();
		def->setIntegerForKey("CurrentBullet", _Bullet);
		def->setIntegerForKey("CurrentTotalBullet", _totalBullet);
		def->setIntegerForKey("CurrentBaseBullet", _baseBullet);
		def->setStringForKey("CheckPlayer", "Old");
		def->flush();
	}
}

void GamePlayLayer::onTouchReloadBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (_Bullet != 30)
	{
		_isReloading = true;
		throwOutputText("Reloading", 2);
		scheduleOnce(schedule_selector(GamePlayLayer::reloading), 2.0f);
	}
}

#pragma endregion

#pragma region Touch Events
bool GamePlayLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*)
{
	Point location = touch->getLocationInView();
	_location = CCDirector::getInstance()->convertToGL(location);
	if (_iconDynamite->getBoundingBox().containsPoint(_location) && _iconDynamite->getTag() == TAG_DYNAMITE_BTN)
	{
		_getDynTag = TAG_DYNAMITE_BTN;
		if (this->isTouchingSprite(touch))
		{
			this->_touchOffset = _iconDynamite->getPosition() -
				this->touchToPoint(touch);
		}
		_isShootingBegan = false;
		return true;
	}
	else
	{
		_isShootingBegan = true;
		return true;
	}
	return false;

}
void GamePlayLayer::potionButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		if (_totalHP <= 0)
		{
			_totalHP = 0;
		}
		else
		{
			_hero->healHero();
			_totalHP--;
		}
	}
}
void GamePlayLayer::onTouchMoved(Touch* touch, Event* event)
{
	Point location = touch->getLocationInView();
	_location = CCDirector::getInstance()->convertToGL(location);
	if (touch && _touchOffset.x && _touchOffset.y)
	{
		if (_getDynTag == TAG_DYNAMITE_BTN)
		{
			_sprDynamite->setVisible(true);
			_sprDynamite->setPosition(this->touchToPoint(touch) + this->_touchOffset);
		}
	}
}

void GamePlayLayer::onTouchEnded(Touch* touch, Event* event)
{
	Size winSize = Director::getInstance()->getWinSize();
	_isShootingBegan = false;
	if (_getDynTag = TAG_DYNAMITE_BTN)
	{
		Vec2 droppedPos = _sprDynamite->getPosition();
		_sprDynamite->setVisible(false);
		throwDynamite(droppedPos);
		_sprDynamite->setPosition(Vec2(winSize.width * 0.75f, winSize.height * 0.87f));
		_getDynTag = 0;
	}
}

void GamePlayLayer::onTouchCancelled(Touch* touch, Event* event)
{

}
#pragma endregion

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

/*Tú*/
void GamePlayLayer::rechargeBullet()
{
	_Bullet = 30;
	_totalBullet = _gunM4A1->baseBullet - 30;
}

void GamePlayLayer::setTotalMoney(int shopMoney)
{
	_totalMoney = shopMoney;
	_Money->setMoney(_totalMoney);
}

void GamePlayLayer::resumeGame()
{
	_woodPane->setVisible(true);
	_blurBG->setVisible(true);
	_resumeBtn->setVisible(true);
	_labelResume->setVisible(true);
	_quitBtn->setVisible(true);
	_labelQuit->setVisible(true);
	_shopBtn->setVisible(true);
	_labelShop->setVisible(true);
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

void GamePlayLayer::rechargeHP()
{
	_totalHP = _HP->itemStat._NumberItem;
}
/*Khoa*/
void GamePlayLayer::addUI()
{
	//dynamite
	Size winSize = Director::getInstance()->getWinSize();
	_iconDynamite = Sprite::create("btn_dynamite.png");
	addChild(_iconDynamite, 3);
	_iconDynamite->setPosition(Vec2(winSize.width * 0.75f, winSize.height * 0.87f));
	_iconDynamite->setTag(TAG_DYNAMITE_BTN);
	_sprDynamite = Sprite::create("weapon_dynamite.png");
	addChild(_sprDynamite, 2);
	_sprDynamite->setPosition(Vec2(winSize.width * 0.75f, winSize.height * 0.87f));
	_sprDynamite->setVisible(false);
	_dynLeft = Label::createWithTTF(StringUtils::format("%02d", _dynStock), "fonts/Marker Felt.ttf", 20);
	_iconDynamite->addChild(_dynLeft);
	_dynLeft->setPosition(Vec2(50.0f, 15.0f));
	_dynLeft->enableOutline(cocos2d::Color4B::BLACK, 3);
	//warrning txt
	_outputTxt = Label::createWithTTF("", "fonts/Creepster-Regular.ttf", 80);
	_outputTxt->setVisible(false);
	addChild(_outputTxt, 2);
	_outputTxt->setColor(cocos2d::Color3B::GREEN);
	_outputTxt->enableOutline(cocos2d::Color4B::RED, 2);
	_outputTxt->enableShadow(Color4B::RED, Size(10, -10), -5);
	_outputTxt->setPosition(winSize.width * 0.5f, winSize.height * 0.75f);
	Blink *rdTxtBlink = Blink::create(5, 12);
	_outputTxt->runAction(rdTxtBlink);

	throwOutputText("READY !!!!", 3);
	//paused effect
	_blurBG = Sprite::create("Untitled.png");
	addChild(_blurBG, 4);
	_blurBG->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	float scaleX = winSize.width / _blurBG->getContentSize().width;
	float scaleY = winSize.height / _blurBG->getContentSize().height;
	_blurBG->setScaleX(scaleX);
	_blurBG->setScaleY(scaleY);
	_blurBG->setOpacity(30);
	_blurBG->setVisible(false);
	_woodPane = Sprite::create("woodpane.png");
	addChild(_woodPane, 4);
	_woodPane->setPosition(winSize * 0.5f);
	_woodPane->setVisible(false);
	_woodPane->setScale(0.7f);

	//magazine ui
	auto _sprMag = Sprite::create("oval.png");
	_sprMag->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_sprMag->setPosition(Vec2(winSize.width * 0.09f, winSize.height * 0.03f));
	addChild(_sprMag, 2);
	_sprMag->setScale(0.15f);
	auto _reloadBtn = cocos2d::ui::Button::create("MagUI.png");
	_reloadBtn->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_reloadBtn->setPosition(winSize * 0.03f);
	_reloadBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::onTouchReloadBtn, this));
	_reloadBtn->setScale(0.15f);
	this->addChild(_reloadBtn, 2);
	_bulletInMag = Label::createWithTTF("aaa", "fonts/Marker Felt.ttf", 20);
	addChild(_bulletInMag, 2);
	_bulletInMag->enableOutline(cocos2d::Color4B::BLACK, 3);
	_bulletInMag->setPosition(Vec2(winSize.width * 0.17f, winSize.height * 0.06f));
}

bool GamePlayLayer::isTouchingSprite(Touch* touch)
{
	if (_getDynTag == TAG_DYNAMITE_BTN)
	{
		auto diff = _iconDynamite->getPosition() - this->touchToPoint(touch);
		return diff.length() < 100.0f;
	}
	return false;
}

Point GamePlayLayer::touchToPoint(Touch* touch)
{
	return Director::getInstance()->convertToGL(touch->getLocationInView());
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

void GamePlayLayer::update(float dt)
{
	/*if (_Bullet == 0 && _totalBullet == 0)
	{
		_isReloading = false;
		_isShootingBegan = false;
		throwOutputText("OUT OF AMMO", INT_MAX);
	}*/

	if (_dynStock <= 0)
	{
		_iconDynamite->setSpriteFrame("btn_dynamite_empty.png");
		_iconDynamite->setTag(554);
	}
	if (_dynStock > 0)
	{
		_iconDynamite->setTag(TAG_DYNAMITE_BTN);
	}
	/*if (_totalHP <= 0)
	{
		_iconHP->setTag(121);
		_totalHP = 0;
	}
	else if (_totalHP > 0)
	{
		_iconHP->setTag(TAG_HEALTH_BTN);
	}*/

	_numberHP->setString(StringUtils::format("%02d", _totalHP));
	_dynLeft->setString(StringUtils::format("%02d", _dynStock));
	_bulletInMag->setString(StringUtils::format("%02d / %03d", _Bullet, _totalBullet));
	def->setIntegerForKey("CurrentBullet", _Bullet);
	def->setIntegerForKey("CurrentTotalBullet", _totalBullet);
	def->flush();
}

void GamePlayLayer::updatePressed(float dt)
{
	if (!_isReloading)
	{
		if (_isShootingBegan)
		{
			if (_Bullet > 0)
			{
				int _shootingsound = experimental::AudioEngine::play2d("audio/m16_fire.ogg");
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
}

void GamePlayLayer::reloading(float dt)
{
	_totalBullet += _Bullet;
	if (_totalBullet >= 30)
	{
		int _reloadingsound = experimental::AudioEngine::play2d("audio/m16_reload.ogg");
		_Bullet = 30;
		_totalBullet -= 30;
	}
	else if (_totalBullet < 30)
	{
		int _reloadingsound = experimental::AudioEngine::play2d("audio/m16_reload.ogg");
		_Bullet = _totalBullet;
		_totalBullet = 0;
	}
	_isReloading = false;
}

void GamePlayLayer::Shooting()
{
	Size winSize = Director::getInstance()->getWinSize();
	_hero->shootAnimation();
	_bullet = _poolBullet->createBullet();
	this->addChild(_bullet, 2);
	_bullet->setPosition(START_POS);
	_bullet->setDamageBullet(_gunM4A1->_Stats._Damage);
	_bullet->bulletFire(_location);
}

void GamePlayLayer::throwDynamite(Vec2 droppedPos)
{
	Size winSize = Director::getInstance()->getWinSize();
	if (droppedPos.y < winSize.height * 0.3f)
	{
		auto dynamite = Sprite::create("weapon_dynamite.png");
		this->addChild(dynamite, 2);
		dynamite->setPosition(Vec2(winSize.width * 0.25f, winSize.height * 0.25f));
		auto sprRotate = RotateBy::create(0.5f, 1800);
		dynamite->runAction(sprRotate);
		auto throwto = JumpTo::create(0.5f, droppedPos, droppedPos.y + 10.0f, 1);
		CallFunc *del = CallFunc::create([=] {
			dynamite->removeFromParent();
			_dynStock--;
		});
		dynamite->runAction(Sequence::create(
			throwto, del, nullptr
		));
		CallFunc *callExplo = CallFunc::create([=] {
			_dynamite = _poolDynamite->createExplo();
			this->addChild(_dynamite, 3);
			_dynamite->setPosition(droppedPos);
			_dynamite->kaBoooom(droppedPos);
		});
		runAction(Sequence::create(DelayTime::create(0.5), callExplo, nullptr));
	}
}

