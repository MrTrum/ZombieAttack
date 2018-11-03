#ifndef _TESTLINE2_H_
#define _TESTLINE2_H_

class TestLine;
#include "cocos2d.h"
#include "GameObject.h"

class TestLine2 : public Node
{
public:
	TestLine2();
	~TestLine2();
	bool init();

	void createLine(float delta);
	
	CREATE_FUNC(TestLine2);
};
#endif // !_TESTLINE_H_
