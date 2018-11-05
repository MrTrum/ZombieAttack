#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;

class Dynamite : public GameObject
{
public:
	Dynamite();
	~Dynamite();
	virtual bool init();
	void throwDynamite(float posX, float posY);
private:
	Sprite	*_sprDynamite;
};


#endif // !_DYNAMITE_H_
