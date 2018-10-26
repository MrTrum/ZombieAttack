#ifndef _P_ZOMBIE_H_
#define _P_ZOMBIE_H_

#include "cocos2d.h"
#include "GameObject.h"
#include "ui/CocosGUI.h"

class PZombie : public GameObject
{
public:
	ui::LoadingBar *loadingbar;

public:
	PZombie();
	~PZombie();
	bool init();
	CREATE_FUNC(PZombie);

	void						getLoadingHealth(float percent);
protected:

	void   					    dead();
	void						reset();
	void						playWalkAnimation(std::string &sprite);
	void						playDeadAnimation();
	void						updateLoadingHealth(float percent);
private:
	cocos2d::Sprite* _spr;
};
#endif // !_P_ZOMBIE_H_
