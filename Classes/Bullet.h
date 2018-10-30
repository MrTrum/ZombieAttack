#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

class BulletObject;
class Bullet: public cocos2d::Node
{
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	virtual bool init();
	void BulletFire(float locationX, float locationY);
	BulletObject* createBullet();
protected:
private:
	cocos2d::Vector<BulletObject*> BulletPool;
	BulletObject* _bullet;
};

#endif // !_BULLET_H_

