#ifndef _POOL_BULLET_H_
#define _POOL_BULLET_H_

#include "cocos2d.h"

class BulletObject;
class PoolBullet : public cocos2d::Node
{
public:
	PoolBullet();
	~PoolBullet();
	BulletObject* createBullet(float x, float y);
private:
	void returnBulletToPool(BulletObject* bullet);
private:
	cocos2d::Vector<BulletObject*> _listBullet;
	float xFromGameLayer;
	float yFromGameLayer;
};


#endif // !_POOL_BULLET_H_
