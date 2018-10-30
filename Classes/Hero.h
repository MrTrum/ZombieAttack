#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include <map>
#include <string>

//std::map<std::string, AnimationInfo> _mapAnimation =
//{
//	{"shootSG",AnimationInfo("fireSG", 10, 30,1)},
//
//};

struct AnimationInfo {
	std::string _name;
	int _numframe;
	float _fps;
	float _loop;
	AnimationInfo(std::string name, int numframe, float fps, float loop) {
		_name = name;
		_numframe = numframe;
		_fps = fps;
		_loop = loop;
	}
};

class Hero : public cocos2d::Node
{
public:
	Hero();
	~Hero();
	CREATE_FUNC(Hero);
	virtual bool init();
	void shootAnimation();
	void playAnimation(std::string name, int numframe, int fps, int loop);
	void playAnimation(AnimationInfo info);
	void playAnimation(std::string animationType);
protected:
private:
	cocos2d::Sprite	 *_sprhero;
	cocos2d::Sprite	 *_sprheroarm;
};



#endif // !_HERO_H_

