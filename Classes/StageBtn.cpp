#include "StageBtn.h"
#include "GamePlayLayer.h"
#include "InfiniteParallaxNode.h"

StageBtn::StageBtn()
{
	_currentStage = UserDefault::getInstance()->getIntegerForKey("UnlockedStage",1);
}

StageBtn::~StageBtn()
{
}

bool StageBtn::init(int tag, Vec2 position)
{
	if (!Node::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	_stageBtn = ui::Button::create("tombLevel.png");
	addChild(_stageBtn);
	_stageBtn->setTag(tag);
	_stageBtn->addTouchEventListener(CC_CALLBACK_2(StageBtn::onTouchStageBtn, this));
	_stageBtn->setPosition(position);
	auto _lblevel = cocos2d::Label::create(StringUtils::format("%02d", tag), "fonts/Creepster-Regular.ttf", 15);
	_lblevel->enableBold();
	_lblevel->enableOutline(cocos2d::Color4B::RED, 2);
	_lblevel->setPosition(Vec2(_stageBtn->getContentSize().width * 0.8f, _stageBtn->getContentSize().height*0.9f));
	_stageBtn->addChild(_lblevel);
	_stageBtn->setScale((winSize.width/_stageBtn->getContentSize().width) * 0.15f);
	if (tag > _currentStage)
	{
		_stageBtn->setEnabled(false);
		auto _enableTxt = cocos2d::Label::create(StringUtils::format("Locked"), "fonts/Creepster-Regular.ttf", 25);
		_enableTxt->enableBold();
		_enableTxt->enableOutline(cocos2d::Color4B::GRAY, 2);
		_enableTxt->setPosition(Vec2(_stageBtn->getContentSize().width* 0.5f, _stageBtn->getContentSize().height*0.2f));
		_stageBtn->addChild(_enableTxt);
	}
	return true;
}

StageBtn *StageBtn::create(int tag, Vec2 position)
{
	StageBtn *pRet = new(std::nothrow) StageBtn();
	if (pRet && pRet->init(tag, position))
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

void StageBtn::onTouchStageBtn(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		auto scene = GamePlayLayer::createGamePlayLayer(_stageBtn->getTag());
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, scene));
	}
}
