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
	bool init();
	static Dynamite *create();
	void reset();
	void setOnDestroyCallback(OnExploDestroyCallback callback);
	void onCollission(GameObject *obj);
	float getDamage() override;
	void kaBoooom(Vec2 droppedPos);
protected:
private:
	float _Dmg;
	void update(float dt);
private:
	PhysicsBody	*_physics;
	ParticleSystemQuad	*_particle;
	OnExploDestroyCallback _onExploDestroyCallback;
	bool _willBeDestroy;
};


#endif // !_DYNAMITE_H_
