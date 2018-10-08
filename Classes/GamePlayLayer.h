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
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event* e);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode kc, cocos2d::Event* e);
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touches, Event* event);

private:
	BackgroundLayer *_bg;
	Hero			*_hero;
	Base			*_base;
	Bullet			*_bullet;
	float			_posX;
	float			_posY;
	Sprite* _Barrier;
	Coin* _Coin;
	Sprite* _hpbar;

};

#endif // !_GAME_PLAY_LAYER

