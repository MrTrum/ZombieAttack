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
	CREATE_FUNC(MenuLayer);
	virtual bool init();
private:

};


#endif // !_MENU_LAYER_H
