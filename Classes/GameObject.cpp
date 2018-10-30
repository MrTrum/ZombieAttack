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


void GameObject::onCollissionDead(GameObject *obj)
{
	if (obj->getTag() == ZOMBIE_TAG)
	{
		obj->dead();
	}
}
void GameObject::onCollissionAttack(GameObject *obj)
{
	if (obj->getTag() == ZOMBIE_TAG)
	{
		obj->attack();
	}
	if (obj->getTag() == BULLET_TAG)
	{
		obj->dead();
	}
}




