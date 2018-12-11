#include "UI/EndGame/EndGame.h"
#include "GamePlayLayer.h"
#include "MapScene.h"
USING_NS_CC;
using namespace ui;
EndGame::EndGame()
{
	min = 0;
	max = 0;
}

EndGame::~EndGame()
{
}
EndGame *EndGame::create(std::string endStr, int curStage)
{
	EndGame *pRet = new(std::nothrow) EndGame();
	if (pRet && pRet->init(endStr, curStage))
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
bool EndGame::init(std::string endStr, int curStage)
{
	if (!Layout::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	this->setContentSize(winSize);
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->setTouchEnabled(true);
	_curStage = curStage;

	_outputTxt = Label::createWithTTF(endStr, "fonts/Creepster-Regular.ttf", 100);
	_outputTxt->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.8f));
	_outputTxt->setColor(cocos2d::Color3B::GREEN);
	_outputTxt->enableOutline(cocos2d::Color4B::RED, 2);
	_outputTxt->enableShadow(Color4B::RED, Size(10, -10), -5);
	this->addChild(_outputTxt,2);
	_bgEndgame = Sprite::create("images/bgEndGame.png");
	_bgEndgame->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.5f));
	_bgEndgame->setScale(1.2f,1.08f);
	this->addChild(_bgEndgame);
	_labelScore = Sprite::create("images/labelScore2.png");
	_labelScore->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.55f));
	_labelScore->setScale(0.8f,0.9f);
	this->addChild(_labelScore,2);
	auto labelTotal = Label::createWithTTF("Total", "fonts/kenvector_future.ttf", 40);
	labelTotal->setPosition(Vec2(winSize.width*0.32f, winSize.height*0.55f));
	this->addChild(labelTotal,2);
	_labelScore2 = Label::createWithTTF("0", "fonts/kenvector_future.ttf", 40);
	_labelScore2->setPosition(Vec2(winSize.width*0.7f, winSize.height*0.55f));
	this->addChild(_labelScore2, 2);
	_btnNext = cocos2d::ui::Button::create("images/next.png");
	_btnNext->setPosition(Vec2(winSize.width*0.7f, winSize.height*0.35f));
	_btnNext->addTouchEventListener(CC_CALLBACK_2(EndGame::TouchNextButton, this));
	_btnNext->setScale(0.9f);
	this->addChild(_btnNext);
	_btnMap = cocos2d::ui::Button::create("images/map.png");
	_btnMap->setPosition(Vec2(winSize.width*0.3f, winSize.height*0.35f));
	_btnMap->addTouchEventListener(CC_CALLBACK_2(EndGame::TouchMapButton, this));
	_btnMap->setScale(0.9f);
	this->addChild(_btnMap);
	_btnReplay = cocos2d::ui::Button::create("images/replay.png");
	_btnReplay->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.35f));
	_btnReplay->addTouchEventListener(CC_CALLBACK_2(EndGame::TouchReplayButton, this));
	_btnReplay->setScale(0.9f);
	this->addChild(_btnReplay);
	this->scheduleUpdate();
	return true;
}
void EndGame::getMax(int number)
{
	max = number;
}
void EndGame::plusNumber(float dt)
{
	std::string _numberIncrease = StringUtils::format("%i",min);
	_labelScore2->setString(_numberIncrease);
	min += 10;
	if (min > max)
	{
		this->unschedule(schedule_selector(EndGame::plusNumber));
	}
}
void EndGame::runNumber()
{
	this->schedule(schedule_selector(EndGame::plusNumber,0.0001f));
}
void EndGame::setGamePlayLayerPtr(GamePlayLayer* ptr)
{
	_ptrGamePlayLayer = ptr;
}
void EndGame::TouchNextButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{

	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		int checkStage = UserDefault::getInstance()->getIntegerForKey("UnlockedStage", 1);
		if (_curStage < checkStage)
		{
			auto scene = GamePlayLayer::createGamePlayLayer(++_curStage);
			Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, scene));
		}
	}

}
void EndGame::TouchReplayButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		int checkStage = UserDefault::getInstance()->getIntegerForKey("UnlockedStage", 1);
		if (_curStage <= checkStage)
		{
			auto scene = GamePlayLayer::createGamePlayLayer(_curStage);
			Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, scene));
		}
	}
}
void EndGame::TouchMapButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		auto scene = MapScene::createMap();
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, scene));
	}
}