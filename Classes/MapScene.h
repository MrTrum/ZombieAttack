#ifndef _MAP_SCENE_H_
#define _MAP_SCENE_H_

#include "cocos2d.h"
#include "UI/CocosGUI.h"
#include "ui/UIButton.h"
#include <climits>
#include <cstdlib>
#include <iostream>
#include "InfiniteParallaxNode.h"
USING_NS_CC;

class StageBtn;
class MapScene : public Node
{
public:
	MapScene();
	~MapScene();
	bool init();
	CREATE_FUNC(MapScene);
	static Scene* createMap();
	void update(float delta) override;
	bool onTouchBegan(Touch*, Event*);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touches, Event* event);
	void onTouchCancelled(Touch* touches, Event* event);
private:
	InfiniteParallaxNode	*_parallaxBG;
	StageBtn				*_stageBtn;
	Vec2					_startPos;
	Vec2					_endPos;
	Vec2					_location;
	Size					winSize;
	bool					_isTouchingBG;
};

#endif // !_MAP_SCENE_H_
