#include "InfiniteParallaxNode.h"


InfiniteParallaxNode::InfiniteParallaxNode()
{
}

InfiniteParallaxNode::~InfiniteParallaxNode()
{
}

class PointObject : public Ref // Dựng 1 lớp PointObject 
{
public:
	inline void setRation(Vec2 ratio) { _ratio = ratio; }
	inline void setOffset(Vec2 offset) { _offset = offset; }
	inline void setChild(Node *var) { _child = var; }
	inline Point getOffset() const { return _offset; }
	inline Node* getChild() const { return _child; }

private:
	Vec2 _ratio; // Tỉ lệ
	Vec2 _offset; // Độ lệch
	Node* _child; // Node con
};

InfiniteParallaxNode* InfiniteParallaxNode::create()
{
	InfiniteParallaxNode* node = new InfiniteParallaxNode();
	if (node) {
		node->autorelease();
	}
	else {
		delete node;
		node = 0;
	}
	return node;
}

void InfiniteParallaxNode::updatePosition()
{
	int safeOffset = -10;

	Size winSize = Director::getInstance()->getWinSize();
	for (int i = 0; i < _children.size(); i++)
	{
		auto node = _children.at(i); // Node i
		if (convertToWorldSpace(node->getPosition()).x + node->getContentSize().width < safeOffset)
			for (int j = 0; j < _parallaxArray->num; j++)
			{
				auto po = (PointObject*)_parallaxArray->arr[j];
				if (po->getChild() == node)
					po->setOffset(po->getOffset() +
						Point(winSize.width + node->getContentSize().width, 0));
			}
	}
}