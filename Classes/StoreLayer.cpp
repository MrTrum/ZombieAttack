#include "StoreLayer.h"
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
	return true;
}
