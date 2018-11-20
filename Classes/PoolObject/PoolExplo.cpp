#include "PoolExplo.h"
#include "Dynamite.h"
PoolExplo::PoolExplo()
{
	
}

PoolExplo::~PoolExplo()
{
}

Dynamite *PoolExplo::createExplo(Vec2 droppedPos)
{
	Dynamite *instance = nullptr;
	if (_listExplo.size() <= 0) // if pool not have bullet, create new
	{
		instance = Dynamite::create(droppedPos);
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolExplo::returnExploToPool, this));
	}
	else
	{
		instance = _listExplo.back();
		instance->reset(droppedPos);
		instance->retain();
		_listExplo.popBack(); // erase last element
	}
	return instance;
}

void PoolExplo::returnExploToPool(Dynamite *explo)
{
	_listExplo.pushBack(explo);
}