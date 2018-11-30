#ifndef _POOL_BULLET_H_
#define _POOL_BULLET_H_

#include "cocos2d.h"
USING_NS_CC;
class BulletObject;
class PoolBullet : public cocos2d::Node
{
public:
	PoolBullet();
	~PoolBullet();
	BulletObject* createBullet();
private:
	void returnBulletToPool(BulletObject* bullet);
private:
	cocos2d::Vector<BulletObject*> _listBullet;
};


#endif // !_POOL_BULLET_H_
