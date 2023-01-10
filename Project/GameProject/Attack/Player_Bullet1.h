#pragma once
#include "../Base/Base.h"

class Player_Bullet1 :public Base{
	CImage m_img;
	//���]�t���O
	bool m_flip;
	
	//�e���Ŏ���
	int cnt;

	float m_speed;
	//�U���ԍ�
	int m_attack_no;
	//�U����
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