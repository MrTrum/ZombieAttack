#ifndef _POOL_BULLET_H_
#define _POOL_BULLET_H_

#include "cocos2d.h"

class BulletObject;
class PoolBullet : public cocos2d::Node
{
public:
	PoolBullet();
	~PoolBullet();
	bool init(float x, float y);
	static PoolBullet *create(float x, float y);
	void initBullet(float x, float y);
	BulletObject* createBullet(float x, float y);
	void addBullet();
private:
	cocos2d::Vector<BulletObject*> _listBullet;
private:
	void returnBulletToPool(BulletObject* bullet);
	float xFromGameLayer;
	float yFromGameLayer;
};


#endif // !_POOL_BULLET_H_
