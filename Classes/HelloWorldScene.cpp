#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GamePlayLayer.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

   // Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//background Menu
	_menuSpr = Sprite::create("images/MenuScene.jpg");
	_menuSpr->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_menuSpr->setPosition(Vec2(0.0f, 0.0f));
	_menuSpr->setContentSize(Size(visibleSize.width, visibleSize.height));
	this->addChild(_menuSpr,1);

	//Button Play
	_playBtn = cocos2d::ui::Button::create("images/PlayButton4.png");
	_playBtn->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height*0.2f));
	_playBtn->setScale((0.5f));
	_playBtn->setTag(1);
	_playBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::TouchPlayButton, this));
	this->addChild(_playBtn,2);

	////Label Play
	//_labelPlay = Label::createWithTTF("Play", "fonts/kenvector_future.ttf", 25);
	//_labelPlay->setPosition(_playBtn->getPosition());
	//this->addChild(_labelPlay,2);

	////Button Quit
	//_quitBtn = ui::Button::create("images/QuitButton3.png");
	//_quitBtn->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height*0.1f));
	//_quitBtn->setScale((0.5f));
	//_quitBtn->setTag(2);
	//_quitBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::TouchQuitButton, this));
	//this->addChild(_quitBtn, 2);

	////Label Quit
	//_labelQuit = Label::createWithTTF("Quit", "fonts/kenvector_future.ttf", 25);
	//_labelQuit->setPosition(_quitBtn->getPosition());
	//this->addChild(_labelQuit, 2);
    return true;
}

void HelloWorld::TouchPlayButton(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	Director::getInstance()->replaceScene(GamePlayLayer::createGamePlayLayer());
}

void HelloWorld::TouchQuitButton(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	Director::getInstance()->end();
}


