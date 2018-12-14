#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include <map>
#include <string>
#include "GameObject.h"
#include "ui/CocosGUI.h"
#include "GameObject/PZombie.h"
#include "GamePlayLayer.h"

USING_NS_CC;
class Hero : public GameObject
{
public:
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
	Sprite				*_frameBloodBar;
	Sprite				*_sprBase;
	Sprite				*_sprhero;
	Sprite				*_sprheroarm;
	float						_health;
	cocos2d::Vector<GameObject*>_zombiesAreAttackingHeroes;
	void						update(float delta) override;
	ui::LoadingBar				*_healthbarHero;
	cocos2d::Vector<PZombie*>   _listZombieCollision;
	std::function<void()> _callback;
};



#endif // !_HERO_H_

