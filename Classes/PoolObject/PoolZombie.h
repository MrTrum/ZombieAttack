#ifndef _POOL_ZOMBIE_H
#define _POOL_ZOMBIE_H

class PZombie;
#include "cocos2d.h"
#include "GamePlayLayer.h"

class PoolZombie : public cocos2d::Node
{
public:
	PoolZombie();
	~PoolZombie();	
	//Tú đã sửa
	bool init(GamePlayLayer* ptr);
	static PoolZombie* create(GamePlayLayer* ptr);
	//

	PZombie*					getZombie();

	void						createZombie_2(float delta);
	void						initZombie();
	void						createLine();
private:
	cocos2d::Vector<PZombie*>   _listZombie;
	ui::LoadingBar				*bloodbar;
	int							numberZombie = 0;

	
	float						randomPositionY();
	float						randomPositionX(float position_y);
	int							ZOrder(float position_y);
	void						setBloodBar(float percent);
	void						updateBloodBar(float percent);
	void						setFrameBloodBar();
	void						pauseSchedule();
	void						updateSchedule();
	//Tú đã sửa
	GamePlayLayer*				_gamePlayLayerPtr;
};
#endif // !_POOL_ZOMBIE_H
