#ifndef _BULLETOBJECT_H_
#define _BULLETOBJECT_H_

#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;
class BulletObject;
class GamePlayLayer;
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
	Vec2 vector;
	void bulletFire(Vec2 location);
protected:
	int _Dmg;
private:
	void poolAndRemoveBullet();
private:
	PhysicsBody *_bulletPhysicBody;
	cocos2d::Sprite *_sprBullet;
	OnBulletDestroyCallback _onBulletDestroyCallback;
	bool _willBeDestroy;
	MotionStreak *_motion;
};

#endif // !_BULLETOBJECT_H_
