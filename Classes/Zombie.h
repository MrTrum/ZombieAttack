#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "cocos2d.h"


using namespace cocos2d;

class Zombie : public cocos2d::Node
{
public:
	Sprite						*zomBie2;
	Vector<Sprite*>				*_Zombie2;


public:
	static cocos2d::Node		*createNode();
	virtual bool				init();
	CREATE_FUNC(Zombie);

	void						createZombie_2(float delta);
	void						createZombie_3(float delta);
	void						createZombie_4(float delta);
	void						createZombie_5(float delta);
	void						physicsForLine();
	bool						onContactBegan(PhysicsContact &contact);
	void						createPools(float delta);
	void						zombie_2Dead(Sprite* sprite);
	void						zombieBackPool(Sprite* sprite);

private:
	int							health = 200;
};

#endif // __ZOMBIE_H__
