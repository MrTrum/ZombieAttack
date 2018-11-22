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
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_physics = PhysicsBody::createCircle(60.0f);
	_physics->setContactTestBitmask(true);
	_physics->setDynamic(false);
	_physics->setGroup(-2);
	this->setPhysicsBody(_physics);
	_particle = ParticleSystemQuad::create("particle_texture.plist");
	this->addChild(_particle);
	_particle->setPosition(_physics->getPosition());
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
		
		auto scaleto = ScaleTo::create(0.5, 1.3f);
		runAction(scaleto);
		_particle->runAction(scaleto->clone());
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