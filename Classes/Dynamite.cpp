#include "Dynamite.h"

Dynamite::Dynamite()
{
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
	_sprDynamite = Sprite::create("weapon_dynamite.png");
	addChild(_sprDynamite);


	return true;
}

void Dynamite::throwDynamite(float posX, float posY)
{
	
	auto throwTo = JumpTo::create(1.0f, Vec2(posX, posY), (posY + 20.0f), 1);

	CallFunc *callback = CallFunc::create([=]
	{
		_sprDynamite = Sprite::createWithSpriteFrameName("explo00.png");
		addChild(_sprDynamite);
		_sprDynamite->setPosition(Vec2(posX, posY));
		_sprDynamite->setScale(5.0f);
		Animation* explosion = Animation::create();

		for (int i = 1; i < 8; i++)
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
		_sprDynamite->removeFromParent();
	}
	);
	_sprDynamite->runAction(Sequence::create(throwTo, callback, delcallback, NULL));
}