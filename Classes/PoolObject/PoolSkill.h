#ifndef _POOL_SKILL_H_
#define _POOL_SKILL_H_

#include "cocos2d.h"
#include "GameObject/SkillZombie.h"

class PZombie;
class PoolSkill
{
public:
	PoolSkill();
	~PoolSkill();

	SkillZombie							*createSkill(int tagZombie);
	void								returnSkillToPool(SkillZombie *skill);
private:
	cocos2d::Sprite						*_skill;
	cocos2d::Vector<SkillZombie*>		_listSkill;
	int									_setNumberSkill[6];
};
#endif // !_POOL_SKILL_H_
