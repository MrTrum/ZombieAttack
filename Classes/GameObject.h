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

	/*virtual void   					    dead()=0;
	virtual void   					    attack() = 0;
	void								onCollissionDead(GameObject *obj);
	void								onCollissionAttack(GameObject *obj);*/
	virtual void						onCollission(GameObject *obj) = 0;
};




#endif // !_GAMEOBJECT_H_

