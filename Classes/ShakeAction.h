#ifndef SHAKE_ACTION_H
#define SHAKE_ACTION_H

#include "cocos2d.h"

class ShakeAction : public cocos2d::ActionInterval
{
public:
	ShakeAction();
	~ShakeAction();
	static ShakeAction* create(float duration, float strength);
	static ShakeAction* create(float duration, cocos2d::Vec2 strength);

	bool initWithDuration(float duration, cocos2d::Vec2 strength);

	virtual void startWithTarget(cocos2d::Node* target);
	virtual void update(float time);
	virtual void stop(void);

protected:
	cocos2d::Vec2 _initial;
	cocos2d::Vec2 _strength;
};

#endif // !SHAKE_ACTION_H