#ifndef _COIN_H
#define _COIN_H
#include "GamePlayLayer.h"
#include "cocos2d.h"
class GamePlayLayer;
class Coin : public cocos2d::Node
{
public:
	Coin();
	~Coin();
	virtual bool init();
	CREATE_FUNC(Coin);
	void PlayAnimation();
	void ScaleCoinAnimation();
	bool FlyAnimation(cocos2d::Vec2 iconPos, std::function<void()> callback);
	void update(float dt) override;
private:
	cocos2d::Sprite* _Coin;
	int _coinVal = 1;
	int static _totalVal;
	GamePlayLayer* _GamePlayLayerPtr;
	std::function<void()> _callback;
};


#endif // !_COIN_H
