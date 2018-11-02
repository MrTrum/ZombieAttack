#ifndef _GAME_PLAY_LAYER
#define _GAME_PLAY_LAYER

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "UI/NumberMoney/Money.h"
#include "UI/StoreItem/StoreLayer.h"
#include "Zombie/PZombie.h"


class BackgroundLayer;
class Hero;
class Base;
class Bullet;
class Coin;

using namespace cocos2d;
class GamePlayLayer : public cocos2d::Node
{
public:
	GamePlayLayer();
	~GamePlayLayer();
	CREATE_FUNC(GamePlayLayer);
	virtual bool init();
	static cocos2d::Scene* createGamePlayLayer();

	/*Tú*/
public:
	void IconCoinCreate();
	void TouchPauseButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void TouchResumeButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void TouchShopButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void resumeGame();
	void update(float dt);
	void removeCoin();
	void CoinFly(Vec2 deadPos);

/*Thanh*/
protected:
	bool onContactBegin(PhysicsContact &contact);
/*Khoa*/
protected:
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touches, Event* event);
	void onTouchCancelled(Touch* touches, Event* event);
	void Shooting(Touch *touch);
	enum State
	{
		STATE_STANDING,
		STATE_SHOOTING,
		STATE_RELOADING,
	};

private:
	BackgroundLayer *_bg;
	Hero			*_hero;
	Base			*_base;
	Bullet			*_bullet;
	float			_posX;
	float			_posY;
	Sprite			*_Barrier;
	Sprite			*_hpbar;
	ui::Widget		*_dynamiteBtn;
/*Tú*/
private:
	Vec2 _iconPos;
	StoreLayer* _Shop;
	Coin* _Coin;
	Money* _Money;
	PZombie* _coinFunc;
	int _totalMoney = 0;
	bool _checkMoney = false;
	cocos2d::Label* _labelResume;
	cocos2d::Label*_labelShop;
	cocos2d::Label*_labelQuit;
	cocos2d::ui::Button* _resumeBtn;
	cocos2d::ui::Button* _quitBtn;
	cocos2d::ui::Button* _shopBtn;
};

#endif // !_GAME_PLAY_LAYER

