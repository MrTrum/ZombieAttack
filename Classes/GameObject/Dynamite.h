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
	void show();
	void hide();
	void setLabelStats();
	bool recharge = false;
protected:
private:
	float _Dmg;
	void update(float dt) override;
private:
	PhysicsBody	*_physics;
	ParticleSystemQuad	*_particle;
	OnExploDestroyCallback _onExploDestroyCallback;
	cocos2d::Sprite* _iconBomb;
	cocos2d::Sprite* _Price;
	cocos2d::Sprite* _bombNum;
	cocos2d::Label* _labelNum;
	cocos2d::Label* _labelUpgrade;
	bool _willBeDestroy;
};


#endif // !_DYNAMITE_H_
