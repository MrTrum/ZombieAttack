#ifndef _CREATE_TESTLINE_H_
#define _CREATE_TESTLINE_H_

#include "cocos2d.h"
#include "GameObject.h"

class CreateTestLine : public GameObject
{
public:
	CreateTestLine();
	~CreateTestLine();
	bool init(int tag);

	static CreateTestLine*		create(int tag);
	void						onCollission(GameObject *obj);
};
#endif // !_CREATE_TESTLINE_H_
