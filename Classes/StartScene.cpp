#include "StartScene.h"
#include "AudioEngine.h"
#include "GamePlayLayer.h"
#include "MapScene.h"
//#include "Store.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

Scene * StartScene::createStartScene()
{
	Scene* scene = Scene::createWithPhysics();
	PhysicsWorld* world = scene->getPhysicsWorld();
	StartScene* node = StartScene::create();
	scene->addChild(node);
	return scene;
}

bool StartScene::init()
{
	if (!Node::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("redneck_idle.plist", "redneck_idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon/M16idle.plist", "weapon/M16idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon/M16firing.plist", "weapon/M16firing.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist", "icon.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsZombie.plist", "images/assetsZombie.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assetsSkill.plist", "images/assetsSkill.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/coin.plist", "images/coin.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/numbers.plist", "images/numbers.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/item.plist", "images/item.png");


	//Load music
	experimental::AudioEngine::preload("audio/nhacMenuScene.mp3");
	experimental::AudioEngine::preload("audio/nhacMap.mp3");
	experimental::AudioEngine::preload("audio/nhacGame.mp3");
	experimental::AudioEngine::preload("audio/nhacVaoShop.mp3");
	experimental::AudioEngine::preload("audio/nhacBoss.mp3");
	experimental::AudioEngine::preload("audio/nhacKhiBamVaoTuiVang.mp3");
	experimental::AudioEngine::preload("audio/m16_fire.ogg");
	experimental::AudioEngine::preload("audio/m16_reload.ogg");
	experimental::AudioEngine::preload("audio/bullet_impact_flesh.ogg");
	experimental::AudioEngine::preload("audio/explosion.ogg");

	//Play music
	experimental::AudioEngine::play2d("audio/nhacMenuScene.mp3");
	/*auto _myStore = MyStore::create();
	addChild(_myStore, 6);*/

	auto _bg = Sprite::create("BG.png");
	addChild(_bg);
	_bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	float scaleX = winSize.width / _bg->getContentSize().width;
	float scaleY = winSize.height / _bg->getContentSize().height;
	_bg->setScale(scaleX, scaleY);
	auto _title = Sprite::create("gameTitle.png");
	addChild(_title, 1);
	_title->setPosition(winSize.width * 0.5f, winSize.height * 0.8f);
	_parallaxBG = InfiniteParallaxNode::create();
	addChild(_parallaxBG);
	for (int i = 0; i < 10; i++)
	{
		auto _fog = Sprite::create("fog.png");
		_fog->setOpacity(30);
		_fog->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_fog->setScale(randomValueBetween(1.5, 3));
		_parallaxBG->addChild(
			_fog,
			randomValueBetween(-4, 3),
			Vec2(0.5, 3),
			Vec2(winSize.width *
				random(0.1f, 1.5f)
				, winSize.height * randomValueBetween(0.1f, 0.9f))
		);
	}
	_startBtnTxt = Label::createWithTTF("START GAME", "fonts/Creepster-Regular.ttf", 50);
	_startBtnTxt->setColor(cocos2d::Color3B::WHITE);
	_startBtnTxt->enableOutline(cocos2d::Color4B::RED, 5);
	_startBtnTxt->enableShadow(Color4B::BLACK, Size(2, -2), -5);
	_startBtnTxt->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_startBtn = ui::Button::create("blankBtn.png");
	addChild(_startBtn,3);
	_startBtnTxt->setPosition(_startBtn->getContentSize() * 0.5f);
	_startBtn->addChild(_startBtnTxt);
	_startBtn->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.55f));
	_startBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_startBtn->addTouchEventListener(CC_CALLBACK_2(StartScene::onTouchStartBtn, this));

	_mapsBtnTxt = Label::createWithTTF("STAGES", "fonts/Creepster-Regular.ttf", 50);
	_mapsBtnTxt->setColor(cocos2d::Color3B::WHITE);
	_mapsBtnTxt->enableOutline(cocos2d::Color4B::RED, 5);
	_mapsBtnTxt->enableShadow(Color4B::BLACK, Size(2, -2), -5);
	_mapsBtnTxt->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_mapsBtn = ui::Button::create("blankBtn.png");
	addChild(_mapsBtn, 3);
	_mapsBtnTxt->setPosition(_mapsBtn->getContentSize() * 0.5f);
	_mapsBtn->addChild(_mapsBtnTxt);
	_mapsBtn->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.45f));
	_mapsBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_mapsBtn->addTouchEventListener(CC_CALLBACK_2(StartScene::onTouchMapsBtn, this));

	_quitBtnTxt = Label::createWithTTF("QUIT", "fonts/Creepster-Regular.ttf", 50);
	_quitBtnTxt->setColor(cocos2d::Color3B::WHITE);
	_quitBtnTxt->enableOutline(cocos2d::Color4B::RED, 5);
	_quitBtnTxt->enableShadow(Color4B::BLACK, Size(2, -2), -5);
	_quitBtnTxt->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_quitBtn = ui::Button::create("blankBtn.png");
	addChild(_quitBtn, 3);
	_quitBtnTxt->setPosition(_quitBtn->getContentSize() * 0.5f);
	_quitBtn->addChild(_quitBtnTxt);
	_quitBtn->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.35f));
	_quitBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_quitBtn->addTouchEventListener(CC_CALLBACK_2(StartScene::onTouchQuitBtn, this));
	
	scheduleUpdate();
	return true;
}

float StartScene::randomValueBetween(float low, float high)
{
	return (((float)RandomHelper::random_int(0,INT_MAX) / INT_MAX) * (high - low)) + low;
}

void StartScene::update(float dt)
{
	Vec2 scrollDecrement = Point(3, 0);
	_parallaxBG->setPosition(_parallaxBG->getPosition() - scrollDecrement);
	_parallaxBG->updatePosition();
}

void StartScene::onTouchStartBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType== ui::Widget::TouchEventType::BEGAN)
	{
		_startBtnTxt->setScale(1.2f);
	}
	if (eEventType == ui::Widget::TouchEventType::CANCELED)
	{
		_startBtnTxt->setScale(1.0f);
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{

		auto scene = GamePlayLayer::createGamePlayLayer(UserDefault::getInstance()->getIntegerForKey("LastEndedStage",1));
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, scene));
	}
}

void StartScene::onTouchMapsBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_mapsBtnTxt->setScale(1.2f);
	}
	if (eEventType == ui::Widget::TouchEventType::CANCELED)
	{
		_mapsBtnTxt->setScale(1.0f);
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		auto scene = MapScene::createMap();
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, scene));
	}
}

void StartScene::onTouchQuitBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::BEGAN)
	{
		_quitBtnTxt->setScale(1.2f);
	}
	if (eEventType == ui::Widget::TouchEventType::CANCELED)
	{
		_quitBtnTxt->setScale(1.0f);
	}
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->end();
	}
}