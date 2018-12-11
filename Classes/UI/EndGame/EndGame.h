#ifndef _END_GAME_H
#define _END_GAME_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

class GamePlayLayer;
class EndGame : public cocos2d::ui::Layout
{

public:
	EndGame();
	~EndGame();
	static EndGame* create(std::string endStr, int curStage);
	bool init(std::string endStr, int  curStage);
	void TouchNextButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void TouchReplayButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void TouchMapButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void setGamePlayLayerPtr(GamePlayLayer* ptr);
	void runNumber();
	void plusNumber(float dt);
	void getMax(int number);
private:
	cocos2d::Sprite* _bgEndgame;
	cocos2d::Sprite* _labelScore;
	cocos2d::ui::Button* _btnMap;
	cocos2d::ui::Button* _btnNext;
	cocos2d::ui::Button* _btnReplay;
	GamePlayLayer* _ptrGamePlayLayer;
	cocos2d::Label* _outputTxt;
	cocos2d::Label* _labelScore2;
	int min, max;
	int _curStage;
};

#endif // !_END_GAME_H
