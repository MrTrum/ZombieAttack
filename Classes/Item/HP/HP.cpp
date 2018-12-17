#include "Item/HP/HP.h"
#include "Parameter.h"

#define UPGRADEBTN_WIDTH_POSITION 0.185f
#define UPGRADEBTN_HEIGHT_POSITION 0.25f
#define UPGRADEBTN_DISTANCT_POSITION 0.45f
#define PRICE_WIDTH_POSITION 0.11f
#define PRICE_HEIGHT_POSITION 0.25f
#define PRICE_LABEL_WIDTH_POSITION 0.18f
#define PRICE_LABEL_HEIGHT_POSITION 0.25f
#define PRICE_DISTANCT_POSITION 0.45f
HP::HP()
{
	Level = 0;
}

HP::~HP()
{
}
void HP::iconItemShow()
{
	_basicStat->setVisible(false);
	_labelStat->setVisible(false);
	_itemNum->setVisible(false);
	_labelNum->setVisible(false);
	Size winSize = Director::getInstance()->getWinSize();
	_iconBuyHP = Sprite::create("images/Heart.png");
	_iconBuyHP->setPosition(_panel.width * 0.43f, _panel.height * 0.45f);
	_iconBuyHP->setScale(0.5f);
	this->addChild(_iconBuyHP);
	std::string _dmgStr = StringUtils::format("  +  %i", itemStat._NumberItem);
	_labelBuyHP = Label::createWithTTF(_dmgStr, "fonts/kenvector_future.ttf", winSize.height * 0.06f);
	_labelBuyHP->setPosition(_panel.width * 0.56f, _panel.height * 0.45f);
	this->addChild(_labelBuyHP);
	std::string _priceStr = StringUtils::format("  %i", (PRICE_NUMBER_HP*itemStat._NumberItem));
	_labelUpgrade->setString(_priceStr);
}
void HP::iconItemHide()
{
	_basicStat->setVisible(true);
	_labelStat->setVisible(true);
	_itemNum->setVisible(true);
	_labelNum->setVisible(true);
	_iconBuyHP->setVisible(false);
	_labelBuyHP->setVisible(false);
}

void HP::setIcon(Size panel)
{
	_panel = panel;
	Size winSize = Director::getInstance()->getWinSize();
	_iconHP = Sprite::create("images/potion.png");
	_iconHP->setPosition(panel.width * 0.51f, panel.height * 0.7f);
	_iconHP->setScale(0.5f);
	this->addChild(_iconHP);
	_basicStat = Sprite::create("images/Plus.png");
	_basicStat->setPosition(panel.width * 0.43f, panel.height * 0.55f);
	_basicStat->setScale(0.75f);
	this->addChild(_basicStat);
	std::string _dmgStr = StringUtils::format("  %i", itemStat._BasicStat);
	_labelStat = Label::createWithTTF(_dmgStr, "fonts/kenvector_future.ttf", winSize.height * 0.06f);
	_labelStat->setPosition(panel.width * 0.56f, panel.height * 0.55f);
	this->addChild(_labelStat);
	_itemNum = Sprite::create("images/Heart.png");
	_itemNum->setPosition(panel.width * 0.43f, panel.height * 0.42f);
	_itemNum->setScale(0.28f);
	this->addChild(_itemNum);
	std::string _numStr = StringUtils::format("  %i", itemStat._NumberItem);
	_labelNum = Label::createWithTTF(_numStr, "fonts/kenvector_future.ttf", winSize.height * 0.06f);
	_labelNum->setPosition(panel.width * 0.56f, panel.height * 0.42f);
	this->addChild(_labelNum);
	_Price = Sprite::createWithSpriteFrameName("coin1.png");
	_Price->setPosition(panel.width * 0.44f, panel.height * 0.3f);
	_Price->setScale(0.3f);
	this->addChild(_Price);
	std::string _priceStr = StringUtils::format("  %i", itemStat._Price);
	_labelUpgrade = Label::createWithTTF(_priceStr, "fonts/kenvector_future.ttf", winSize.height * 0.06f);
	_labelUpgrade->setPosition(panel.width * 0.53f, panel.height * 0.3f);
	_labelUpgrade->setColor(cocos2d::Color3B(0, 0, 0));
	this->addChild(_labelUpgrade);
}
void HP::setLabelStats()
{
	std::string _statStr = StringUtils::format("  %i", itemStat._BasicStat);
	_labelStat->setString(_statStr);
	std::string _numStr = StringUtils::format("  %i", itemStat._NumberItem);
	_labelNum->setString(_numStr);
}
void HP::setLevel()
{
	UserDefault::getInstance()->setIntegerForKey("LevelHP", Level++);
	UserDefault::getInstance()->flush();
}
void HP::getLevel()
{
	this->Level = UserDefault::getInstance()->getIntegerForKey("LevelHP");
}
void HP::hide()
{
	this->setVisible(false);
}
void HP::show()
{
	this->setVisible(true);
}
void HP::setItemIcon()
{

}