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
};


#endif // !_BASE_H_

