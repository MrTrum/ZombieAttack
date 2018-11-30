#ifndef _SKILL_ZOMBIE_H_
#define _SKILL_ZOMBIE_H_

#include "cocos2d.h"
#include "GameObject.h"



using namespace cocos2d;
class SkillZombie;
class PZombie;
typedef std::function<void(SkillZombie *skill)> skillZombie;

class SkillZombie : public GameObject
{
public:
	SkillZombie();
	~SkillZombie();
	bool init(int tagZombie);
	static SkillZombie* create(int tagZombie);

	void						playSkillAnimation(std::string skillname);
	void						onCollission(GameObject *obj) override;
	void						fireSkill(Vec2 localZombie, Vec2 localHero);
	void						assignSkillToPoll(skillZombie skillzombie);
	virtual void				setPosition(float x, float y) override;

	//virtual void setPosition(float x, float y);
private:
	Sprite						*_skill;
	int							_setNumberSkill[6];
	skillZombie					_skillzombie;
	ParticleSystemQuad			*_particle;
};
#endif // !_SKILL_ZOMBIE_H_
