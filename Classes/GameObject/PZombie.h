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
	float health;
	float damage;

	static float damageOfZombie;
	enum Stage
	{
		DEAD,
		ALIVE
	};
private:
	Sprite*						_spr;
	int							_tag;
	std::string					_stringName;
	int							_setNumberSkill[6];
	PoolSkill*					_poolSkill;
	Vec2						_target;
	SkillZombie*				_skill;
	std::vector<float>			_listHealthZombie;
	//bool						_isWalk;
	//bool						_isAttack;
	bool						_isDead;
public:
	PZombie();
	~PZombie();
	bool init(PoolZombie *ptr, std::string zombieName, int tag);
	static PZombie* create(PoolZombie *ptr, std::string zombieName, int tag);


	void						setGamePlayLayerPtr(GamePlayLayer* ptr);
	void						setHealthBar(float percent);
	void						resetHealthBar(float percent);
	void						updateHealthBar(float health, PZombie *ptrZombie);
	void   					    Dead();
	void   					    checkDamage();
	void   					    Attack();
	void						Walk();
	void						playWalkAnimation(std::string zombieName);
	void						playAttackAnimation(std::string stringname);
	void						playDeadAnimation(Vec2 deadPos, std::string stringname);
	void						onCollission(GameObject *obj) override;
	std::string					convertFromTagToStringWalk(int tag);
	std::string					convertFromTagToStringAttack(int tag);
	std::string					convertFromTagToStringDead(int tag);
	std::string					convertFromTagToStringSkill(int tag);
	void						droppedItems(Vec2 deadPos);
	void						attackSkill(float delta);
	void						attackAndFire(float delta);
	void						walkAndMove();
	void						Move(float time, Vec2& target);
	float						returnHealth(int i);
	/*virtual void move();*/
};
#endif // !_P_ZOMBIE_H_
