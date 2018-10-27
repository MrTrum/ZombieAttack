#ifndef _TESTLINE_H_
#define _TESTLINE_H_

#include "cocos2d.h"
#include "GameObject.h"

class TestLine : public GameObject
{
public:
	TestLine();
	~TestLine();
	bool init();
	
	CREATE_FUNC(TestLine);

	void dead();
	void createLine(float delta);

};
#endif // !_TESTLINE_H_
