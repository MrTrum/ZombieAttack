#include "PoolExplo.h"
#include "GameObject/Dynamite.h"
PoolExplo::PoolExplo()
{
	
}

PoolExplo::~PoolExplo()
{
}

Dynamite *PoolExplo::createExplo()
{
	Dynamite *instance = nullptr;
	if (_listExplo.size() <= 0) 
	{
		instance = Dynamite::create();
		instance->setOnDestroyCallback(CC_CALLBACK_1(PoolExplo::returnExploToPool, this));
	}
	else
	{
		instance = _listExplo.back();
		instance->reset();
		instance->retain();
		_listExplo.popBack(); 
	}
	return instance;
}

void PoolExplo::returnExploToPool(Dynamite *explo)
{
	_listExplo.pushBack(explo);
}