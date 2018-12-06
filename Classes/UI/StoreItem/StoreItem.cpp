#include "UI/StoreItem/StoreItem.h"
#define ITEM_WIDTH_POSITION 0.05f
#define ITEM_HEIGHT_POSITION 0.25f
#define ITEM_DISTANCT_POSITION 0.32f
#define UPGRADEBTN_WIDTH_POSITION 0.185f
#define UPGRADEBTN_HEIGHT_POSITION 0.25f
#define UPGRADEBTN_DISTANCT_POSITION 0.32f
#define PRICE_LABEL_WIDTH_POSITION 0.18f
#define PRICE_LABEL_HEIGHT_POSITION 0.25f
StoreItem::StoreItem()
{
}

StoreItem::~StoreItem()
{
}
void StoreItem::setData(int id, int money)
{
	_Id = id;
	_money = money;
	_labelUpgrade->setString(StringUtils::format("%d", money));
}
void StoreItem::setCallBack(std::function<void(int idItem)> callback)
{
	_callback = callback;
}

StoreItem* StoreItem::create(cocos2d::Size size)
{
	auto instance = new StoreItem();
	if (instance && instance->init(size))
	{
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return instance;
}
bool StoreItem::init(cocos2d::Size size)
{
	if (!Layout::init())
	{
		return false;
	}
	this->setContentSize(size);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_ItemWeapon = Sprite::create("images/ItemWeapon.png");
	_ItemWeapon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_ItemWeapon->setScale(1.0f, 1.5f);
	_ItemWeapon->setPosition(Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height - 10.0f - _ItemWeapon->getContentSize().height * 0.5f * _ItemWeapon->getScaleY()));
	this->addChild(_ItemWeapon);
	_upgradeBtn = cocos2d::ui::Button::create("images/UpgradeWeapon.png");
	_upgradeBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_upgradeBtn->setPosition(Vec2(this->getContentSize().width * 0.5f, 10.0f));
	this->addChild(_upgradeBtn);
	_labelUpgrade = Label::createWithTTF(0, "fonts/kenvector_future.ttf", 25);
	_labelUpgrade->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_labelUpgrade->setColor(cocos2d::Color3B(0, 0, 0));
	_labelUpgrade->setPosition(_upgradeBtn->getContentSize() * 0.5f);
	_upgradeBtn->addChild(_labelUpgrade);

	this->setBackGroundColorType(BackGroundColorType::SOLID);
	this->setBackGroundColor(Color3B::RED);
	return true;
}