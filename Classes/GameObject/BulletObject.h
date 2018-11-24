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
	bool init(Vec2 location);
	static BulletObject *create(Vec2 location);
	void onCollission(GameObject *obj) override;
	void reset(Vec2 location);
	void setOnDestroyCallback(OnBulletDestroyCallback callback);
	void setDamageBullet(int Dmg);
	float getDamage() override;
	Vec2 vector;
protected:
	int _Dmg;
private:
	void update(float delta);
	void bulletFire(Vec2 location);
private:
	PhysicsBody *_bulletPhysicBody;
	cocos2d::Sprite *_sprBullet;
	OnBulletDestroyCallback _onBulletDestroyCallback;
	bool _willBeDestroy;
};

#endif // !_BULLETOBJECT_H_
