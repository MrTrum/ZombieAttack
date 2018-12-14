#ifndef _GAME_PLAY_LAYER
#define _GAME_PLAY_LAYER

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "Item/HP/HP.h"
#include "UI/NumberMoney/Money.h"
#include "UI/StoreItem/StoreLayer.h"
#include "GameObject/PZombie.h"

class MyStore;
class BackgroundLayer;
class Hero;
class BulletObject;
class PoolBullet;
class PoolExplo;
class Dynamite;
class Coin;

USING_NS_CC;

class GamePlayLayer;
class GamePlayLayer : public cocos2d::Node
{
public:
	GamePlayLayer();
	~GamePlayLayer();
	bool init(int playStage);
	static GamePlayLayer* create(int playStage);
	static cocos2d::Scene* createGamePlayLayer(int stage);
public:
	void			IconCoinCreate();
	void			TouchPauseButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void			TouchResumeButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void			TouchShopButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void			TouchQuitButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void			resumeGame();
	void			moneyChange();
	void			CoinFly(Vec2 deadPos, float delay = 0.0f, std::function<void()> onEndCallback = nullptr);
	void			setTotalMoney(int shopMoney);
	void			rechargeBullet();
	void			rechargeHP();
	void			ScaleCoinAnimation();
	void			rechargeBomb();
	void			potionButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void			createGoldBag(Vec2 deadPos);
	void			createItems(int randomitem, Vec2 deadPos);
	void			testButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	bool			onContactBegin(PhysicsContact &contact);
protected:
	Point			touchToPoint(Touch* touch);
	void			updatePressed(float dt);
	bool			onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void			onTouchMoved(Touch* touch, Event* event);
	void			onTouchEnded(Touch* touches, Event* event);
	void			onTouchCancelled(Touch* touches, Event* event);
	void			Shooting();
	bool			isTouchingSprite(Touch* touch);
	void			throwDynamite(Vec2 droppedPos);
	void			throwOutputText(std::string txt, int duration);
	void			reloading(float dt);
	void			addUI();
	void			update(float dt) override;
	void			onTouchReloadBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
private:
	MyStore			*_myStore;
	StoreLayer		*_Shop;
	BackgroundLayer *_bg;
	Hero			*_hero;
	PZombie			*_coinFunc;
	BulletObject	*_bullet;
	Dynamite		*_dynamite;
	HP				*_HP;
	Coin			*_Coin;
	Money			*_Money;
	M4A1			*_gunM4A1;
	SkillZombie     *_skillZombie;
	PoolBullet		*_poolBullet;
	PoolExplo		*_poolDynamite;
	PoolSkill		*_poolSkill;
	MotionStreak	*_motion;
	Label			*_dynLeft;
	Label			*_outputTxt;
	Label			*_bulletInMag;
	Point			_touchOffset;
	Point			_location;
	Sprite			*_woodPane;
	Sprite			*_blurBG;
	Sprite			*_Barrier;
	Sprite			*_hpbar;
	Sprite			*_iconDynamite;
	Sprite			*_sprDynamite;
	Sprite			*_IconCoin;
	Sprite			*_iconHP;
	Sprite			*_iconHPHide;
	Vec2			_iconPos;
	Label			* _labelResume;
	Label			*_labelShop;
	Label			*_labelQuit;
	Label			*_numberHP;
	ui::Button		*_resumeBtn;
	ui::Button		*_quitBtn;
	ui::Button		*_shopBtn;
	UserDefault		*def;
	int				_Level, _Bullet, _baseBullet,_LevelHP,_totalHP;
	int				scenePlay;
	int				dem;
	int				_getDynTag;
	int				_totalBullet;
	int				_dynStock;
	int				_totalMoney = 0;
	int				_musicGame;
	bool			_isTxtVisible;
	bool			_checkMoney;
	bool			_isShootingBegan;
	bool			_isReloading;
	float			_posX;
	float			_posY;
};

#endif // !_GAME_PLAY_LAYER

