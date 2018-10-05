#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "cocos2d.h"


using namespace cocos2d;

class Zombie : public cocos2d::Node
{
public:
	Sprite						*zomBie2;


public:
    static cocos2d::Node		*createNode();
    virtual bool				init();
    CREATE_FUNC(Zombie);

	void						createZombie_2(float unknow);
	void						createZombie_3(float unknow);
	void						createZombie_4(float unknow);
	void						createZombie_5(float unknow);
	void						physicsForLine();
	bool						onContactBegan(PhysicsContact &contact);

};

#endif // __ZOMBIE_H__
