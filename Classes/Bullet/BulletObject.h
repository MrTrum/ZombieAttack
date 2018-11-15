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
	bool init(float x, float y);
	static BulletObject *create(float x, float y);
	//CREATE_FUNC(BulletObject);
	void onCollission(GameObject *obj) override;
	void removeBullet();
	void reset(float x, float y);
	void setOnDestroyCallback(OnBulletDestroyCallback callback);
	void preventShooting();
	void setDamageBullet(int Dmg);
	int _Dmg;
	int getDamage() override;
private:
	void update(float delta);
	void bulletFire(float locationX, float locationY);
private:
	cocos2d::Sprite *_sprBullet;
	OnBulletDestroyCallback _onBulletDestroyCallback;
	bool _willBeDestroy;
	bool _isShooting;
};

#endif // !_BULLETOBJECT_H_
