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
	bool init();
	static BulletObject *create();
	void onCollission(GameObject *obj) override;
	void reset();
	void setOnDestroyCallback(OnBulletDestroyCallback callback);
	void setDamageBullet(int Dmg);
	float getDamage() override;
	void bulletFire(Vec2 location);
protected:
	int _Dmg;
private:
	void update(float delta);
private:
	MotionStreak *_motion;
	PhysicsBody *_bulletPhysicBody;
	cocos2d::Sprite *_sprBullet;
	OnBulletDestroyCallback _onBulletDestroyCallback;
	bool _willBeDestroy;
	Size winSize;
};

#endif // !_BULLETOBJECT_H_
