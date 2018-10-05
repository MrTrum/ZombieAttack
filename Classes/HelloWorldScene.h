#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"


using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{

public:
    static Scene* createScene();

    virtual bool init();
    
	void TouchPlayButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void TouchQuitButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
    CREATE_FUNC(HelloWorld);

private:
	Sprite*			_menuSpr;
	ui::Button*		_playBtn;
	ui::Button*		_quitBtn;
	Label*			_labelPlay;
	Label*			_labelQuit;
};

#endif // __HELLOWORLD_SCENE_H__
