#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;
class Dynamite;
typedef std::function<void(Dynamite* explo)> OnExploDestroyCallback;
class Dynamite : public GameObject
{
public:
	Dynamite();
	~Dynamite();
	bool init(Vec2 droppedPos);
	static Dynamite *create(Vec2 droppedPos);
	void reset(Vec2 droppedPos);
	void setOnDestroyCallback(OnExploDestroyCallback callback);
	void onCollission(GameObject *obj);
	float getDamage() override;
protected:
private:
	float _Dmg;
	void update(float dt);
	void kaBoooom(Vec2 droppedPos);

private:
	PhysicsBody	*_physics;
	ParticleSystemQuad	*_particle;
	OnExploDestroyCallback _onExploDestroyCallback;
	bool _willBeDestroy = false;
};


#endif // !_DYNAMITE_H_
