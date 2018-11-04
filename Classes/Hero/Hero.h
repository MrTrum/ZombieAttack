#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include <map>
#include <string>
#include "GameObject.h"
#include "ui/CocosGUI.h"

//std::map<std::string, AnimationInfo> _mapAnimation =
//{
//	{"shootSG",AnimationInfo("fireSG", 10, 30,1)},
//
//};

struct AnimationInfo {
	std::string _name;
	int _numframe;
	float _fps;
	float _loop;
	AnimationInfo(std::string name, int numframe, float fps, float loop) 
	{
		_name = name;
		_numframe = numframe;
		_fps = fps;
		_loop = loop;
	}
};

class Hero : public GameObject
{
public:
	enum class AnimationType
	{
		SHOOT,
		RELOAD,
		IDLE
	};
	Hero();
	~Hero();
	CREATE_FUNC(Hero);
	virtual bool init();
	void						shootAnimation();
	void						playAnimation(std::string name, int numframe, int fps, int loop);
	void						playAnimation(AnimationInfo info);

	void						setHealthBar(float percent);
	void						updateHealthBar(float percent);
protected:
	void						onCollission(GameObject *obj) override;
	void						heroWounded(float delta);
private:
	static std::map<AnimationType, AnimationInfo>	_mapAnimation;
	cocos2d::Sprite				*_sprhero;
	cocos2d::Sprite				*_sprheroarm;
	ui::LoadingBar				*_healthbarHero;
	float _health;
	cocos2d::Vector<GameObject*>_zombiesAreAttackingHeroes;
	void						theHealthOfZombiesAreAttacking(GameObject *obj);
};



#endif // !_HERO_H_

