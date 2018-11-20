#include "Dynamite.h"

Dynamite::Dynamite()
{
	_Dmg = 100.0f;
}

Dynamite::~Dynamite()
{
}

bool Dynamite::init(Vec2 droppedPos)
{
	if (!GameObject::init())
	{
		return false;
	}
	_sprDynamite = Sprite::createWithSpriteFrameName("explo00.png");
	addChild(_sprDynamite);
	setScale(5.0f);
	auto _physics = PhysicsBody::createCircle(20.0f);
	_physics->setContactTestBitmask(true);
	_physics->setDynamic(false);
	_physics->setGroup(-2);
	this->setPhysicsBody(_physics);
	this->setTag(TAG_DYNAMITE);
	kaBoooom(droppedPos);
	scheduleUpdate();
	return true;
}

Dynamite *Dynamite::create(Vec2 droppedPos)
{
	Dynamite *pRet = new(std::nothrow) Dynamite();
	if (pRet && pRet->init(droppedPos))
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

void Dynamite::reset(Vec2 droppedPos)
{
	Size winSize = Director::getInstance()->getWinSize();
	this->setVisible(true);
	kaBoooom(droppedPos);
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
		_sprDynamite = Sprite::createWithSpriteFrameName("explo00.png");
		addChild(_sprDynamite);
		_sprDynamite->setPosition(droppedPos);
		Animation* explosion = Animation::create();

		for (int i = 0; i < 7; i++)
		{
			std::string name = StringUtils::format("explo%02d.png", i);
			explosion->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
		}
		explosion->setDelayPerUnit(1 / 16.0f);
		Animate* animate = Animate::create(explosion);
		_sprDynamite->runAction(animate);
	}
	);

	CallFunc *delcallback = CallFunc::create([=]
	{
		_willBeDestroy = true;
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