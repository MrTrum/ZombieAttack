#ifndef _P_ZOMBIE_H_
#define _P_ZOMBIE_H_

#include "cocos2d.h"
#include "GameObject.h"
#include "ui/CocosGUI.h"
//Tú đã sửa
class GamePlayLayer;
using namespace cocos2d;

class PZombie : public GameObject
{
public:
	ui::LoadingBar *healthbarZombie;
	//Tú đã sửa
	GamePlayLayer* _coinFunc;
public:
	PZombie();
	~PZombie();
	bool init();
	CREATE_FUNC(PZombie);


	void						setGamePlayLayerPtr(GamePlayLayer* ptr);
	void						setHealthBar(float percent);
	void						getHealthBar(float percent);
	void						updateHealthBar(float percent);
	void   					    dead();
	void   					    attack();
	void						reset();
	void						playWalkAnimation();
	//Tú đã sửa
	void						playDeadAnimation(Vec2 deadPos);
	void						playAttackAnimation();
	Sprite* _spr;
	

};
#endif // !_P_ZOMBIE_H_
