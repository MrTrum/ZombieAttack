#ifndef _INFINITE_PARALLAX_NODE_H_
#define _INFINITE_PARALLAX_NODE_H_

#include "cocos2d.h"
USING_NS_CC;

class InfiniteParallaxNode : public ParallaxNode
{
public:
	InfiniteParallaxNode();
	~InfiniteParallaxNode();
	static InfiniteParallaxNode* create();
	void updatePosition();
private:

};

#endif // !_INFINITE_PARALLAX_NODE_H_
