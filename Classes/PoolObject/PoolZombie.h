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
	bool init(GamePlayLayer* ptr, int sceneplay);
	static PoolZombie* create(GamePlayLayer* ptr, int sceneplay);

	PZombie*					getZombie1();
	PZombie*					getZombie2();
	PZombie*					getZombie3();
	PZombie*					getZombie4();

	void						createZombie_1(float delta);
	void						createZombie_2(float delta);
	void						createZombie_3(float delta);
	void						createZombie_4(float delta);
	void						initZombie();
	bool						checkTheLastZombie();
	void						changeSchedule(int NOZombie);
	static int					scene;
private:
	cocos2d::Vector<PZombie*>   _listZombie1;
	cocos2d::Vector<PZombie*>   _listZombie2;
	cocos2d::Vector<PZombie*>   _listZombie3;
	cocos2d::Vector<PZombie*>   _listZombie4;
	cocos2d::Vector<PZombie*>   _listZombie2Total;
	GamePlayLayer*				_gamePlayLayerPtr;
	ui::LoadingBar				*bloodbar;
	int							numberZombie;
	int							_check;
	int							setZombie1;
	int							setZombie2;
	int							setZombie3;
	int							setZombie4;
	
	float						randomPositionY();
	float						randomPositionX(float position_y);
	int							ZOrder(float position_y);
	void						setBloodBar(float percent);
	void						updateBloodBar(float percent);
	void						setFrameBloodBar();
	void						updateSchedule(float time, int NOZombie);
	void						scenePlay(int sceneplay);
	std::string					getNameZombie(int setzombie);
};
#endif // !_POOL_ZOMBIE_H
