#ifndef _P_ZOMBIE_H_
#define _P_ZOMBIE_H_

#include "cocos2d.h"
#include "GameObject.h"
#include "ui/CocosGUI.h"
#include "GameObject/SkillZombie.h"



class GamePlayLayer;
class PoolZombie;
class PoolSkill;

using namespace cocos2d;
class PZombie : public GameObject
{
public:
	ui::LoadingBar*				healthbarZombie;
	GamePlayLayer*				ptrGamePlayLayer;
	PoolZombie*					ptrPoolZombie;
	int health;
	float damage;

	static float damageOfZombie;
private:
	Sprite*						_spr;
	Sprite*						_skill;
	int							_tag;
	std::string					_stringName;
	const int					_percentHealth2;
	const int					_percentHealth3;
	const int					_percentHealth4;
	const int					_percentHealth5;
	const int					_percentHealth6;
	const int					_percentHealth7;
	int							_setNumberSkill[6];
	PoolSkill*					_poolSkill;
	Vec2						_target;
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
	std::string					convertFromTagToStringSkill(int tag);
	void						droppedItems(Vec2 deadPos);
	void						attackSkill();
	void						resumeAction();
	void						move(int time, Vec2& target);
	/*virtual void move();*/
};
#endif // !_P_ZOMBIE_H_
