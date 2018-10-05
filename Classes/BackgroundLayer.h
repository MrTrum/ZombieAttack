#ifndef _BACKGROUND_LAYER_H_
#define _BACKGROUND_LAYER_H_
#include "cocos2d.h"

class BackgroundLayer:public cocos2d::Node
{
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	virtual bool init();
private:
	cocos2d::Sprite *_sprBG;
};

#endif // !_BACKGROUND_LAYER_H_

