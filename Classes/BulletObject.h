#ifndef _BULLETOBJECT_H_
#define _BULLETOBJECT_H_

#include "cocos2d.h"
#include "GameObject.h"

class BulletObject : public GameObject
{
public:
	BulletObject();
	~BulletObject();
	virtual bool init();
	CREATE_FUNC(BulletObject);
	

private:
	void   					    attack();
	void    dead();
private:
	cocos2d::Sprite *_sprBullet;
};

#endif // !_BULLETOBJECT_H_
