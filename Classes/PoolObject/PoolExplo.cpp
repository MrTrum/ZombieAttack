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
	if (_listExplo.size() <= 0) 
	{
		instance = Dynamite::create(droppedPos);
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolExplo::returnExploToPool, this));
	}
	else
	{
		instance = _listExplo.back();
		instance->reset(droppedPos);
		instance->retain();
		_listExplo.popBack(); 
	}
	return instance;
}

void PoolExplo::returnExploToPool(Dynamite *explo)
{
	_listExplo.pushBack(explo);
}