﻿#include "MapScene.h"
#include "UI/CocosGUI.h"
#include "ui/UIButton.h"
#include <climits>
#include <cstdlib>
#include <iostream>
#include "GamePlayLayer.h"
#include "StageBtn.h"
#include "AudioEngine.h"

MapScene::MapScene()
{
	_isTouchingBG = true;
}

MapScene::~MapScene()
{
}

Scene * MapScene::createMap()
{
	Scene* scene = Scene::create();
	MapScene* node = MapScene::create();
	scene->addChild(node);
	return scene;
}

bool MapScene::init()
{
	if (!Node::init())
	{
		return false;
	}
	experimental::AudioEngine::stopAll();
	experimental::AudioEngine::play2d("audio/nhacMap.mp3");

	winSize = Director::getInstance()->getWinSize();

	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MapScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MapScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MapScene::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(MapScene::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	#pragma region add BackGround
	auto background01 = Sprite::create("selectLevelBG01.png");
	addChild(background01);
	background01->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	float scale = winSize.width / background01->getContentSize().width;
	background01->setScale(scale);
	auto background02 = Sprite::create("selectLevelBG02.png");
	addChild(background02);
	background02->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background02->setScale(scale);
	background02->setPosition(winSize.width, 0.0f);
	#pragma endregion
	
	auto house = Sprite::create("SelectLevel_House.png");
	addChild(house);
	house->setScale(scale);
	house->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	for (int i = 1; i < 7; i++)
	{
		auto posX = winSize.width * (0.25f + i * 0.25f);
		auto posY = winSize.height * random(0.20f, 0.55f);
		_stageBtn = StageBtn::create(i, Vec2(posX, posY));
		addChild(_stageBtn);
	}

	_parallaxBG = InfiniteParallaxNode::create();
	addChild(_parallaxBG);
	for (int i = 0; i < 10; i++)
	{
		auto _fog = Sprite::create("fog2.png");
		_fog->setOpacity(30);
		_fog->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_fog->setScale(random(1.5f, 3.0f));
		_parallaxBG->addChild(
			_fog,
			random(-4, 3),
			Vec2(0.5, 3),
			Vec2(winSize.width *
				random(0.1f, 1.5f)
				, winSize.height * random(0.1f, 0.9f))
		);
	}
	scheduleUpdate();
	return true;
}

void MapScene::update(float delta)
{
	if (this->getPosition().x > 0)
	{
		this->setPosition(0.0f, 0.0f);
	}
	if (this->getPosition().x < -winSize.width)
	{
		this->setPosition(-winSize.width, 0.0f);
	}
	Vec2 scrollDecrement = Point(1, 0);
	_parallaxBG->setPosition(_parallaxBG->getPosition() - scrollDecrement);
	_parallaxBG->updatePosition();
}

bool MapScene::onTouchBegan(Touch *touch, Event *event)
{
	_location = touch->getLocationInView();
	_location = Director::getInstance()->convertToGL(_location);
	if (_isTouchingBG)
	{
		_startPos = _location;
		return true;
	}
	return false;
}

void MapScene::onTouchMoved(Touch *touch, Event *event)
{
	_location = touch->getLocationInView();
	_location = Director::getInstance()->convertToGL(_location);
}

void MapScene::onTouchEnded(Touch *touch, Event *event)
{
	if (_isTouchingBG)
	{
		_endPos = touch->getLocationInView();
		_endPos = Director::getInstance()->convertToGL(_endPos);
		auto distance = Vec2(_endPos.x - _startPos.x, 0.0f);
		auto backgroundMove = MoveBy::create(0.5f, distance);
		this->runAction(backgroundMove);
	}
}

void MapScene::onTouchCancelled(Touch *touch, Event *event)
{

}