#ifndef _STORE_LAYER_H
#define _STORE_LAYER_H
#include "cocos2d.h"
USING_NS_CC;
class StoreLayer : public cocos2d::Node
{
public:
	StoreLayer();
	~StoreLayer();
	CREATE_FUNC(StoreLayer);
	virtual bool init();
private:

};


#endif