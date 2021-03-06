#include "Dynamite.h"

Dynamite::Dynamite()
{
	_willBeDestroy = false;
}

Dynamite::~Dynamite()
{
}

bool Dynamite::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	setContentSize(Size(winSize.width * 0.15f, winSize.width * 0.15f));
	_physics = PhysicsBody::createCircle(winSize.width * 0.15f);
	_physics->setContactTestBitmask(true);
	_physics->setDynamic(false);
	_physics->setGroup(-2);
	this->setPhysicsBody(_physics);
	_particle = ParticleSystemQuad::create("explo.plist");
	this->addChild(_particle);
	_particle->setScale(1.2);
	_particle->setPosition(_physics->getPosition());
	_Dmg = 200.0f;
	this->setTag(TAG_DYNAMITE);
	scheduleUpdate();
	return true;
}
void Dynamite::show(Size panel)
{
	Size winSize = Director::getInstance()->getWinSize();
	_iconBomb = Sprite::create("btn_dynamite.png");
	_iconBomb->setPosition(panel.width * 0.79f, panel.height * 0.7f);
	_iconBomb->setScale(1.8f);
	this->addChild(_iconBomb);
	_bombNum = Sprite::create("weapon_dynamite.png");
	_bombNum->setPosition(panel.width * 0.72f, panel.height * 0.45f);
	_bombNum->setScale(2.3f);
	this->addChild(_bombNum);
	std::string _dmgStr = StringUtils::format("  +  %i", 5);
	_labelNum = Label::createWithTTF(_dmgStr, "fonts/kenvector_future.ttf", panel.height * 0.06f);
	_labelNum->setPosition(panel.width * 0.85f, panel.height * 0.45f);
	this->addChild(_labelNum);
	int test = (PRICE_BOMB*BOMB_NUMBER);
	_Price = Sprite::createWithSpriteFrameName("coin1.png");
	_Price->setPosition(panel.width * 0.73f, panel.height * 0.3f);
	_Price->setScale(0.3f);
	this->addChild(_Price);
	std::string _priceStr = StringUtils::format("  %i", test);
	_labelUpgrade = Label::createWithTTF(_priceStr, "fonts/kenvector_future.ttf", panel.height * 0.06f);
	_labelUpgrade->setPosition(Vec2(panel.width*0.81f, panel.height*0.3f));
	_labelUpgrade->setColor(cocos2d::Color3B(0, 0, 0));
	_labelUpgrade->setString(_priceStr);
	this->addChild(_labelUpgrade);
}
void Dynamite::hide()
{

}
void Dynamite::setLabelStats()
{

}
Dynamite *Dynamite::create()
{
	Dynamite *pRet = new(std::nothrow) Dynamite();
	if (pRet && pRet->init())
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

void Dynamite::reset()
{
	Size winSize = Director::getInstance()->getWinSize();
	this->setVisible(true);
	scheduleUpdate();
}

void Dynamite::onCollission(GameObject *obj)
{
	
}

void Dynamite::setOnDestroyCallback(OnExploDestroyCallback callback)
{
	_onExploDestroyCallback = callback;
}

void Dynamite::kaBoooom(Vec2 droppedPos)
{
	CallFunc *callback = CallFunc::create([=]
	{
		_particle->start();
	}
	);

	CallFunc *delcallback = CallFunc::create([=]
	{
		_willBeDestroy = true;
		_particle->stop();
	}
	);
	runAction(Sequence::create(callback,DelayTime::create(1), delcallback, NULL));
}

float Dynamite::getDamage()
{
	return _Dmg;
}

void Dynamite::update(float dt)
{
	if (_willBeDestroy)
	{
		if (_onExploDestroyCallback)
		{
			_onExploDestroyCallback(this);
		}
		stopAllActions();
		this->removeFromParent();
		_willBeDestroy = false;
	}
}