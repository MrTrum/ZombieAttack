#ifndef _GAME_PLAY_LAYER
#define _GAME_PLAY_LAYER

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "Coin.h"


class BackgroundLayer;
class Hero;
class Base;
class Bullet;

using namespace cocos2d;
class GamePlayLayer : public cocos2d::Node
{
public:
	GamePlayLayer();
	~GamePlayLayer();
	CREATE_FUNC(GamePlayLayer);
	virtual bool init();
	static cocos2d::Scene* createGamePlayLayer();

protected:
<<<<<<< HEAD
	bool onContactBegin(PhysicsContact &contact);
=======
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touches, Event* event);
	void Shooting(Touch *touch);

private:
	Size			winSize;
	BackgroundLayer *_bg;
	Hero			*_hero;
	Base			*_base;
	Bullet			*_bullet;
	float			_posX;
	float			_posY;
	Sprite*			_Barrier;
	Coin*			_Coin;
	Sprite*			_hpbar;
>>>>>>> 66a4e0b2ce8c4a497db11a83ce597bca9992a3bd

};

#endif // !_GAME_PLAY_LAYER

