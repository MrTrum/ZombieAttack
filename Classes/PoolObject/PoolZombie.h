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
	PZombie*					getZombie3();

	void						createZombie_2(float delta);
	void						createZombie_3(float delta);
	void						initZombie();
	bool						checkTheLastZombie();
	void						changeSchedule(int NOZombie);
private:
	cocos2d::Vector<PZombie*>   _listZombie1;
	cocos2d::Vector<PZombie*>   _listZombie2;
	ui::LoadingBar				*bloodbar;
	int							numberZombie;
	int							_check;
	
	float						randomPositionY();
	float						randomPositionX(float position_y);
	int							ZOrder(float position_y);
	void						setBloodBar(float percent);
	void						updateBloodBar(float percent);
	void						setFrameBloodBar();
	void						updateSchedule(int NOZombie,float time);
	//Tú đã sửa
	GamePlayLayer*				_gamePlayLayerPtr;
};
#endif // !_POOL_ZOMBIE_H
