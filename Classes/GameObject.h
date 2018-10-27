#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "cocos2d.h"
#include "Parameter.h"

using namespace cocos2d;

class GameObject : public cocos2d::Node
{
public:
	float _health		= HEALTH_ZOMBIE2;
	float _damge		= DAMGE_ZOMBIE2;
public:
	GameObject();
	~GameObject();
	bool init();

	virtual void   					    dead()=0;
	void								onCollission(GameObject *obj);
};




#endif // !_GAMEOBJECT_H_

