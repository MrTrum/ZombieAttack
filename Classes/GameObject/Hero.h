#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include <map>
#include <string>
#include "GameObject.h"
#include "ui/CocosGUI.h"
#include "GameObject/PZombie.h"
#include "GamePlayLayer.h"

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
	void						setHealthBar(float percent);
	void						updateHealthBar(float percent);
	void						healHero();
	void setCallBack(std::function<void()> callback);
protected:
	void						onCollission(GameObject *obj) override;
	void						heroWounded(float delta);
private:
	Size						winSize;
	cocos2d::Sprite				*_sprhero;
	cocos2d::Sprite				*_sprheroarm;
	float						_health;
	cocos2d::Vector<GameObject*>_zombiesAreAttackingHeroes;
	void						update(float delta) override;
	ui::LoadingBar				*_healthbarHero;
	cocos2d::Vector<PZombie*>   _listZombieCollision;
	std::function<void()> _callback;
};



#endif // !_HERO_H_

