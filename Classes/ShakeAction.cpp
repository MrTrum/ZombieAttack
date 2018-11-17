#include "ShakeAction.h"

USING_NS_CC;

ShakeAction::ShakeAction()
{
	_strength = Vec2::ZERO;
}

ShakeAction::~ShakeAction()
{

}

inline float rangedRand(float min, float max)
{
	return CCRANDOM_0_1() * (max - min) + min;
}

ShakeAction* ShakeAction::create(float d, float strength)
{
	return create(d, Vec2(strength, strength));
}

ShakeAction* ShakeAction::create(float duration, cocos2d::Vec2 strength)
{
	ShakeAction* action = new ShakeAction();
	if (action && action->initWithDuration(duration, strength))
	{
		action->autorelease();
		return action;
	}
	CC_SAFE_DELETE(action);
	return nullptr;
}

bool ShakeAction::initWithDuration(float duration, cocos2d::Vec2 strength)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_strength = strength;
		return true;
	}

	return false;
}

void ShakeAction::update(float time)
{
	Vec2 rand = Vec2(rangedRand(-_strength.x, _strength.x),
		rangedRand(-_strength.y, _strength.y));

	_target->setPosition(_initial + rand);
}

void ShakeAction::startWithTarget(Node* target)
{
	ActionInterval::startWithTarget(target);

	_initial = target->getPosition();
}

void ShakeAction::stop(void)
{
	_target->setPosition(_initial);

	ActionInterval::stop();
}