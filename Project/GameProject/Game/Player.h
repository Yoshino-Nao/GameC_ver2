#pragma once
#include"../Base/Base.h"

class Player :public Base {
private:
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
	};
	int m_state;
	//Šeó‘Ô‚Å‚Ì‹““®
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();
	CImage m_img;
	bool m_flip;
	bool m_is_ground;
	int m_attack_no;
	int m_damage_no;
	int m_hp;
public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};