#include "Border.h"
#include "Parameter.h"
Border::Border()
{
}

Border::~Border()
{
}

bool Border::init()
{
	if (!GameObject::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	auto physics = PhysicsBody::createEdgeBox(winSize);
	setPhysicsBody(physics);
	physics->setDynamic(false);
	physics->setContactTestBitmask(true);
	physics->setGroup(1);
	physics->setPositionOffset(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	/*this->setTag(TAG_BORDER);*/

	return true;
}


void Border::onCollission(GameObject *obj)
{

}