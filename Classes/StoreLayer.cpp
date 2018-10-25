#include "StoreLayer.h"
#include "GamePlayLayer.h"
StoreLayer::StoreLayer()
{
}

StoreLayer::~StoreLayer()
{
}
bool StoreLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Node::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//shop 
	auto _shop = Sprite::create("images/shop.png");
	_shop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_shop->setPosition(Vec2(0.0f, 0.0f));
	_shop->setContentSize(Size(visibleSize.width, visibleSize.height));
	this->addChild(_shop, 1);
	//quit button
	_quitShop = cocos2d::ui::Button::create("images/quit_shop.png");
	_quitShop->setPosition(Vec2(visibleSize.width*0.95f, visibleSize.height*0.9f));
	_quitShop->addTouchEventListener(CC_CALLBACK_2(StoreLayer::TouchQuitButton, this));
	this->addChild(_quitShop, 1);
	//money number
	_Money = Money::create();
	_Money->setShopMoneyPos();
	this->addChild(_Money,1);
	return true;
}
void StoreLayer::TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (eEventType == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->removeAllChildren();
		_btnGamePlayLayer->resumeGame();
	}
}

void StoreLayer::setGamePlayLayerPtr(GamePlayLayer* ptr)
{
	_btnGamePlayLayer = ptr;
}
void StoreLayer::setTotalMoney(int _GameTotalMoney)
{
	_shopTotalMoney = _GameTotalMoney;
	_Money->setMoney(_shopTotalMoney);
}