#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

class Bullet: public cocos2d::Node
{
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	virtual bool init();
protected:
private:
	cocos2d::Sprite * _sprBullet;
};

#endif // !_BULLET_H_

