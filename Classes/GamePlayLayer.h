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
class BulletObject;
class PoolBullet;
class Dynamite;
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
	void moneyChange();
	void CoinFly(Vec2 deadPos);
	void setTotalMoney(int shopMoney);

/*Thanh*/
	bool onContactBegin(PhysicsContact &contact);
	void createGoldBag(Vec2 deadPos);
	void createItems(int randomitem, Vec2 deadPos);
	void testButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
/*Khoa*/
protected:
	void updatePressed(float dt);
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touches, Event* event);
	void onTouchCancelled(Touch* touches, Event* event);
	void Shooting();
private:
	BackgroundLayer *_bg;
	Hero			*_hero;
	Base			*_base;
	BulletObject	*_bullet;
	PoolBullet		*_poolBullet;
	bool			_isPressed = false;
	float			_posX;
	float			_posY;
	Point			_location;
	Sprite			*_Barrier;
	Sprite			*_hpbar;
	Sprite			*_iconDynamite;
	ui::Widget		*_dynamiteBtn;
/*Tú*/
private:
	Vec2 _iconPos;
	StoreLayer* _Shop;
	Coin* _Coin;
	Money* _Money;
	M4A1* _gunM4A1;
	PZombie* _coinFunc;
	int _totalMoney = 0;
	bool _checkMoney = false;
	cocos2d::Label* _labelResume;
	cocos2d::Label*_labelShop;
	cocos2d::Label*_labelQuit;
	cocos2d::ui::Button* _resumeBtn;
	cocos2d::ui::Button* _quitBtn;
	cocos2d::ui::Button* _shopBtn;
	UserDefault* def;
	int _Level, _Bullet;
	int scenePlay;
};

#endif // !_GAME_PLAY_LAYER

