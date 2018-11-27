#include "Item/HP/HP.h"
USING_NS_CC;
HP::HP()
{
}

HP::~HP()
{
}
void HP::setIcon()
{
	Size winSize = Director::getInstance()->getWinSize();
	_iconHP = Sprite::create("images/potion.png");
	_iconHP->setPosition(winSize.height*0.28f, winSize.width*0.42f);
	_iconHP->setScale(0.5f);
	this->addChild(_iconHP);
	_basicStat = Sprite::create("images/Heart.png");
	_basicStat->setPosition(winSize.height*0.18f, winSize.width*0.31f);
	_basicStat->setScale(0.12f);
	this->addChild(_basicStat);
	std::string _dmgStr = StringUtils::format("  %i", itemStat._BasicStat);
	_labelStat = Label::createWithTTF(_dmgStr, "fonts/kenvector_future.ttf", 30);
	_labelStat->setPosition(winSize.height*0.33f, winSize.width*0.31f);
	this->addChild(_labelStat);
	_itemNum = Sprite::create("images/bulletNum.png");
	_itemNum->setPosition(winSize.height*0.18f, winSize.width*0.24f);
	_itemNum->setScale(0.18f);
	this->addChild(_itemNum);
	std::string _numStr = StringUtils::format("  %i", itemStat._NumberItem);
	_labelNum = Label::createWithTTF(_numStr, "fonts/kenvector_future.ttf", 30);
	_labelNum->setPosition(winSize.height*0.33f, winSize.width*0.24f);
	this->addChild(_labelNum);

}
void HP::setLabelStats()
{
	std::string _statStr = StringUtils::format("  %i", itemStat._BasicStat);
	_labelStat->setString(_statStr);
	std::string _numStr = StringUtils::format("  %i", itemStat._NumberItem);
	_labelNum->setString(_numStr);
}
void HP::hide()
{
	this->setVisible(false);
}
void HP::show()
{
	this->setVisible(true);
}