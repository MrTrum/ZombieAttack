#ifndef _MENU_LAYER_H
#define _MENU_LAYER_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
USING_NS_CC;
class MenuLayer: public cocos2d::Node
{
public:
	MenuLayer();
	~MenuLayer();
	virtual bool init();
	void TouchPlayButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
	void TouchQuitButton(Ref* pSender, ui::Widget::TouchEventType eEventType);
	CREATE_FUNC(MenuLayer);

private:
	Sprite*			_menuSpr;
	ui::Button*		_playBtn;
	ui::Button*		_quitBtn;
	Label*			_labelPlay;
	Label*			_labelQuit;
};


#endif // !_MENU_LAYER_H
