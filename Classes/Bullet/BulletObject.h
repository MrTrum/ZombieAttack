#ifndef _BULLETOBJECT_H_
#define _BULLETOBJECT_H_

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;
class BulletObject;
typedef std::function<void(BulletObject* bullet)> OnBulletDestroyCallback;
class BulletObject : public GameObject
{
public:
	BulletObject();
	~BulletObject();
	bool init(float x, float y);
	static BulletObject *create(float x, float y);
	void onCollission(GameObject *obj) override;
	void removeBullet();
	void reset(float x, float y);
	void setOnDestroyCallback(OnBulletDestroyCallback callback);
private:
	void gunRecoil(float dt);
	void update(float delta);
	void bulletFire(float locationX, float locationY);
private:
	Sprite *_sprBullet;
	PhysicsBody* _bulletPhysicBody;
	OnBulletDestroyCallback _onBulletDestroyCallback;
	bool _willBeDestroy;
	bool canShoot = true;
	float xFromParent;
	float yFromParent;
};

#endif // !_BULLETOBJECT_H_
