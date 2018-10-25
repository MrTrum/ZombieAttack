#ifndef _POOL_ZOMBIE_H
#define _POOL_ZOMBIE_H

class PZombie;
#include "cocos2d.h"
#include "GamePlayLayer.h"

class PoolZombie : public cocos2d::Node
{
public:
	PoolZombie();
	~PoolZombie();	
	bool init();
	CREATE_FUNC(PoolZombie);


	void						createZombie_2(float delta);
	void						initZombie();
	PZombie*					getZombie();
	void						createLine(float delta);
private:
	cocos2d::Vector<PZombie*> _listZombie;

};
#endif // !_POOL_ZOMBIE_H
