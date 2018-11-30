#include "Parameter.h"
#include "PoolObject/PoolSkill.h"
#include "GameObject/SkillZombie.h"


USING_NS_CC;

PoolSkill::PoolSkill()
{
	
}

PoolSkill::~PoolSkill()
{
}

SkillZombie* PoolSkill::createSkill(int tagZombie)
{
	SkillZombie *skill = nullptr;
	if (_listSkill.empty())
	{
		skill = SkillZombie::create(tagZombie);
		skill->assignSkillToPoll(CC_CALLBACK_1(PoolSkill::returnSkillToPool, this));
	}
	else
	{
		skill = _listSkill.back();
		skill->retain();
		_listSkill.popBack(); // erase last element
	}
	skill->setVisible(false);
	return skill;
}

void PoolSkill::returnSkillToPool(SkillZombie *skill)
{
	_listSkill.pushBack(skill);
}


