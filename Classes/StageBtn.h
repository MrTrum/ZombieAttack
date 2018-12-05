#ifndef _STAGE_BUTTON_H_
#define _STAGE_BUTTON_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

USING_NS_CC;

class StageBtn: public Node 
{
public:
	StageBtn();
	~StageBtn();
	bool init(int tag, Vec2 position);
	static StageBtn* create(int tag, Vec2 position);
	void onTouchStageBtn(Ref* pSender, ui::Widget::TouchEventType eEventType);
private:
	ui::Button		*_stageBtn;
	int				_currentStage;
};


#endif // !_STAGE_BUTTON_H_

