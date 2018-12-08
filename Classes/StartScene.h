#ifndef _START_SCENE_H_
#define _START_SCENE_H_

#include "cocos2d.h"
#include "InfiniteParallaxNode.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

USING_NS_CC;

class StartScene : public Node
{
public:
	StartScene();
	~StartScene();
	bool init();
	CREATE_FUNC(StartScene);
	static Scene* createStartScene();
	float randomValueBetween(float low, float high);
	void onTouchStartBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void onTouchMapsBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void onTouchQuitBtn(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void update(float dt);
private:
	Size winSize;
	InfiniteParallaxNode	*_parallaxBG;
	Label					*_startBtnTxt;
	Label					*_mapsBtnTxt;
	Label					*_quitBtnTxt;
	ui::Button				*_startBtn;
	ui::Button				*_mapsBtn;
	ui::Button				*_quitBtn;
};

#endif // !_START_SCENE_H_
