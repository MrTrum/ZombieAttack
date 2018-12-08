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
	bool init(GamePlayLayer* ptr, int sceneplay);
	static PoolZombie* create(GamePlayLayer* ptr, int sceneplay);

	PZombie						*getZombie1();
	PZombie						*getZombie2();
	PZombie						*getZombie3();
	PZombie						*getZombie4();

	void						createZombie_1(float delta);
	void						createZombie_2(float delta);
	void						createZombie_3(float delta);
	void						createZombie_4(float delta);
	void						initZombie();
	bool						checkTheLastZombie();
	void						changeSchedule();
	float						setHealth(PZombie *zombie);
	typedef std::function<void()> Action;
	void						assignAction(Action action);
	void						updateAction();
	GamePlayLayer*				getGamePlayLayer();

private:
	cocos2d::Vector<PZombie*>   _listZombie1;
	cocos2d::Vector<PZombie*>   _listZombie2;
	cocos2d::Vector<PZombie*>   _listZombie3;
	cocos2d::Vector<PZombie*>   _listZombie4;
	cocos2d::Vector<PZombie*>   _listZombie2Total;
	GamePlayLayer*				_gamePlayLayerPtr;
	ui::LoadingBar				*bloodbar;
	int							_numberZombie;
	int							_check;
	int							_setTagZombie[4];
	int							_random14;
	Action						_action;
	int							_scenePlay;
	bool						_hasBoss;

	void						getTagZombie(int tagZombie1, int tagZombie2, int tagZombie3, int tagZombie4);
	float						randomPositionY();
	float						randomPositionX(float position_y);
	int							ZOrder(float position_y);
	void						setBloodBar(float percent);
	void						updateBloodBar(float percent);
	void						setFrameBloodBar();
	void						updateSchedule(int numberZombie);
	void						scenePlay(int sceneplay);
	std::string					getNameZombie(int tagZombie);
	void						setScaleHealthBar(PZombie* zombie);
	float						getPosX(int tagZombie, float positionY);
	int							getTimeMove(int tagZombie);
	
};
#endif // !_POOL_ZOMBIE_H
