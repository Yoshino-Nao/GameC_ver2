#pragma once
#include "../Base/Base.h"

class Player_Bullet1 :public Base{
	CImage m_img;
	//”½“]ƒtƒ‰ƒO
	bool m_flip;

	//’eÁ–ÅŠÔ
	int cnt;
	//—­‚ßŠÔ(120)
	//int Ccnt;
	//UŒ‚”Ô†
	int m_attack_no;
public:
	Player_Bullet1(const CVector2D& p, bool flip, int attack_no);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}

};