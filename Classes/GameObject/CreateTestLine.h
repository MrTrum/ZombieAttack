#ifndef _CREATE_TESTLINE_H_
#define _CREATE_TESTLINE_H_

#include "cocos2d.h"
#include "GameObject/GameObject.h"

class CreateTestLine : public GameObject
{
public:
	CreateTestLine();
	~CreateTestLine();
	bool init(int tag, Vec2 location);

	static CreateTestLine*		create(int tag, Vec2 location);
	void						onCollission(GameObject *obj);

private:
	Vec2						_location;
};
#endif // !_CREATE_TESTLINE_H_
