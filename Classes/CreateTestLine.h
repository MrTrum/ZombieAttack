#ifndef _CREATE_TESTLINE_H_
#define _CREATE_TESTLINE_H_

#include "cocos2d.h"
#include "GameObject.h"

class CreateTestLine : public GameObject
{
public:
	CreateTestLine();
	~CreateTestLine();
	bool init();

	CREATE_FUNC(CreateTestLine);
	void dead();
	void attack();

};
#endif // !_CREATE_TESTLINE_H_
