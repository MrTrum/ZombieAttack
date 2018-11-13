#include "MenuLayer.h"
#include "GamePlayLayer.h"


MenuLayer::MenuLayer()
{
}

MenuLayer::~MenuLayer()
{
}
Scene * MenuLayer::createScene()
{
	Scene* scene = Scene::createWithPhysics();
	//PhysicsWorld* world = scene->getPhysicsWorld();
	////remember to turn off debug when release
	//world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	MenuLayer* node = MenuLayer::create();
	scene->addChild(node);
	return scene;
}
bool MenuLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*Tú*/
	///background Menu
	auto _menuSpr = Sprite::create("images/MenuScene.jpg");
	_menuSpr->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_menuSpr->setPosition(Vec2(0.0f, 0.0f));
	_menuSpr->setContentSize(Size(visibleSize.width, visibleSize.height));
	this->addChild(_menuSpr, 1);
	//Button Play
	auto _playBtn = cocos2d::ui::Button::create("images/PlayButton4.png");
	_playBtn->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height*0.2f));
	_playBtn->setScale(1.0f);
	_playBtn->setTag(1);
	_playBtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::TouchPlayButton, this));
	this->addChild(_playBtn, 2);
	//Label Play
	auto _labelPlay = Label::createWithTTF("Play", "fonts/kenvector_future.ttf", 25);
	_labelPlay->setPosition(_playBtn->getPosition());
	this->addChild(_labelPlay, 2);
	//Button Quit
	auto _quitBtn = cocos2d::ui::Button::create("images/QuitButton3.png");
	_quitBtn->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height*0.1f));
	_quitBtn->setScale(1.0f);
	_quitBtn->setTag(2);
	_quitBtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::TouchQuitButton, this));
	this->addChild(_quitBtn, 2);
	//Label Quit
	auto _labelQuit = Label::createWithTTF("Quit", "fonts/kenvector_future.ttf", 25);
	_labelQuit->setPosition(_quitBtn->getPosition());
	this->addChild(_labelQuit, 2);
	return true;
}
void MenuLayer::TouchPlayButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::BEGAN)
	{
		Director::getInstance()->replaceScene(GamePlayLayer::createGamePlayLayer());
	}
}
void MenuLayer::TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->end();
	}
}
