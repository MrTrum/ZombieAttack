#ifndef _BASE_H_
#define _BASE_H_

#include "cocos2d.h"

class Base: public cocos2d::Node
{
public:
	Base();
	~Base();
	virtual bool init();
	CREATE_FUNC(Base);
private:
	cocos2d::Sprite *_sprBase;
	cocos2d::Sprite *_sprBar1;
	cocos2d::Sprite *_sprBar2;
	cocos2d::Sprite *_sprBar3;
};


#endif // !_BASE_H_

