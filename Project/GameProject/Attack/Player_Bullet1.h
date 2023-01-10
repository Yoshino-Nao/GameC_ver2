#pragma once
#include "../Base/Base.h"

class Player_Bullet1 :public Base{
	CImage m_img;
	//”½“]ƒtƒ‰ƒO
	bool m_flip;
	
	//’eÁ–ÅŠÔ
	int cnt;

	float m_speed;
	//UŒ‚”Ô†
	int m_attack_no;
	//UŒ‚—Í
	int m_pow;
public:
	Player_Bullet1(const CVector2D& p, float ang, bool flip, int attack_no, int pow);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
	int GetAttackPow() {
		return m_pow;
	}
};