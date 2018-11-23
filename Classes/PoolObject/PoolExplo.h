#ifndef _POOLEXPLO_H_
#define _POOLEXPLO_H_

#include "cocos2d.h"

USING_NS_CC;

class Dynamite;
class PoolExplo : public Node
{
public:
	PoolExplo();
	~PoolExplo();
	Dynamite *createExplo();
private:
	cocos2d::Vector<Dynamite*> _listExplo;
private:
	void returnExploToPool(Dynamite* explo);
};



#endif // !_POOLEXPLO_H_
