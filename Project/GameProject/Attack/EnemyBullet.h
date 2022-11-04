#pragma once
#include"../Base/Base.h"

class EnemyBullet :public Base {
	CImage m_img;
	float m_speed;
	int cnt;
	int m_attack_no;
public:
	EnemyBullet(
		int type, const CVector2D& pos, int attack_no, float r, float g, float b, float t);
	void Update();
	void Draw();
	void Collision(Base*b);
	int GetAttackNo() {
		return m_attack_no;
	}
};
