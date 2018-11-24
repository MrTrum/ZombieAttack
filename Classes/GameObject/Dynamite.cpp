#include "Dynamite.h"

Dynamite::Dynamite()
{
	_Dmg = 100.0f;
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
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_physics = PhysicsBody::createCircle(60.0f);
	_physics->setContactTestBitmask(true);
	_physics->setDynamic(false);
	_physics->setGroup(-2);
	this->setPhysicsBody(_physics);
	_particle = ParticleSystemQuad::create("explo.plist");
	this->addChild(_particle);
	_particle->setScale(0.5f);
	_particle->setPosition(_physics->getPosition());
	this->setTag(TAG_DYNAMITE);
	scheduleUpdate();
	return true;
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