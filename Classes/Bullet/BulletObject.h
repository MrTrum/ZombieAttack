#ifndef _BULLETOBJECT_H_
#define _BULLETOBJECT_H_

#include "cocos2d.h"
#include "GameObject.h"

class BulletObject;
typedef std::function<void(BulletObject* bullet)> OnBulletDestroyCallback;
class BulletObject : public GameObject
{
public:
	BulletObject();
	~BulletObject();
	virtual bool init();
	CREATE_FUNC(BulletObject);
	void onCollission(GameObject *obj) override;
	void removeBullet();
	void reset(float x, float y);
	void setOnDestroyCallback(OnBulletDestroyCallback callback);
private:
	void update(float delta);
	void bulletFire(float locationX, float locationY);
private:
	cocos2d::Sprite *_sprBullet;
	OnBulletDestroyCallback _onBulletDestroyCallback;
	bool _willBeDestroy;
};

#endif // !_BULLETOBJECT_H_
