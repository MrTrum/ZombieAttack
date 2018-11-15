#include "GameObject.h"
#include "PoolObject/PoolZombie.h"


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



int GameObject::getDamage()
{
	return _Dmg;
}


