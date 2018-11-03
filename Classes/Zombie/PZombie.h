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
	Sprite* _spr;
	float health;
	float damage;

	static float damageOfZombie;
public:
	PZombie();
	~PZombie();
	bool init();
	CREATE_FUNC(PZombie);


	void						setGamePlayLayerPtr(GamePlayLayer* ptr);
	void						setHealthBar(float percent);
	float						getHealthBar();
	void						updateHealthBar(float percent);
	void   					    dead();
	void   					    attack();
	void						reset();
	void						playWalkAnimation();
	void						playAttackAnimation();
	void						playDeadAnimation(Vec2 deadPos);
	void						onCollission(GameObject *obj) override;
};
#endif // !_P_ZOMBIE_H_
