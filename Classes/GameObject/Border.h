#ifndef _BORDER_H_
#define _BORDER_H_

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;
class Border : public GameObject
{
public:
	Border();
	~Border();
	bool init();
	CREATE_FUNC(Border);
	void	onCollission(GameObject *obj);
private:

};



#endif // !_BORDER_H_

