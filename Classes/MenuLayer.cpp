#include "MenuLayer.h"
MenuLayer::MenuLayer()
{
}

MenuLayer::~MenuLayer()
{
}
bool MenuLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();	
	return true;
}
