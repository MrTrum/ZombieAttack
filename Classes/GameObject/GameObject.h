#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "cocos2d.h"
#include "Parameter.h"

using namespace cocos2d;

class GameObject : public cocos2d::Node
{

public:
	GameObject();
	~GameObject();
	bool init();
	virtual float getDamage();
	virtual void						onCollission(GameObject *obj) = 0;
protected:
	float _Dmg;
};




#endif // !_GAMEOBJECT_H_

