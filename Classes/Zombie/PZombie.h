#ifndef _P_ZOMBIE_H_
#define _P_ZOMBIE_H_

#include "cocos2d.h"
#include "GameObject.h"
#include "ui/CocosGUI.h"



class GamePlayLayer;
class PoolZombie;

using namespace cocos2d;
class PZombie : public GameObject
{
public:
	ui::LoadingBar				*healthbarZombie;
	//Tú đã sửa
	GamePlayLayer				*ptrGamePlayLayer;
	PoolZombie					*ptrPoolZombie;
	Sprite* _spr;
	int health;
	int damage;

	static float damageOfZombie;
private:
	int							_tag;
	std::string					_stringName;
	const int					_percentHealth2;
	const int					_percentHealth3;
	const int					_percentHealth4;
	const int					_percentHealth5;

public:
	PZombie();
	~PZombie();
	bool init(PoolZombie *ptr, std::string zombieName, int tag);
	static PZombie* create(PoolZombie *ptr, std::string zombieName, int tag);


	void						setGamePlayLayerPtr(GamePlayLayer* ptr);
	void						setHealthBar(float percent);
	void						resetHealthBar(float percent);
	void						updateHealthBar(int health, PZombie *ptrZombie);
	void   					    dead();
	void   					    checkDamage();
	void   					    attack();
	void						reset();
	void						playWalkAnimation(std::string zombieName);
	void						playAttackAnimation(std::string stringname);
	void						playDeadAnimation(Vec2 deadPos, std::string stringname);
	void						onCollission(GameObject *obj) override;
	std::string					convertFromTagToStringWalk(int tag);
	std::string					convertFromTagToStringAttack(int tag);
	std::string					convertFromTagToStringDead(int tag);
	void						droppedItems(Vec2 deadPos);
};
#endif // !_P_ZOMBIE_H_
