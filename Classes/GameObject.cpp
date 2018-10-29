#include "GameObject.h"
#include "PoolZombie.h"


USING_NS_CC;


GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

bool GameObject::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}


void GameObject::onCollission(GameObject *obj)
{
	if (obj->getTag() == ZOMBIE_TAG)
	{
		obj->dead();
	}
	else if (obj->getTag() == LINE_TAG)
	{
		obj->removeChildByTag(LINE_TAG);
	}
	if (obj->getTag() == BULLET_TAG)
	{
		obj->dead();
	}
}




