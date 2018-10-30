#ifndef _P_ZOMBIE_H_
#define _P_ZOMBIE_H_

#include "cocos2d.h"
#include "GameObject.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
class PZombie : public GameObject
{
public:
	ui::LoadingBar *healthbarZombie;
public:
	PZombie();
	~PZombie();
	bool init();
	CREATE_FUNC(PZombie);


	
	void						setHealthBar(float percent);
	void						getHealthBar(float percent);
	void						updateHealthBar(float percent);
	void   					    dead();
	void   					    attack();
	void						reset();
	void						playWalkAnimation();
	void						playDeadAnimation();
	void						playAttackAnimation();
	Sprite* _spr;


};
#endif // !_P_ZOMBIE_H_
