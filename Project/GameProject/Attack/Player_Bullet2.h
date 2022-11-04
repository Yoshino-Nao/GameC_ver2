#pragma once
#include "../Base/Base.h"

class Player_Bullet2 :public Base {
	CImage m_img;
	//���]�t���O
	bool m_flip;

	//�e���Ŏ���
	int cnt;
	//���ߎ���(120)
	//int Ccnt;
	//�U���ԍ�
	int m_attack_no;
public:
	Player_Bullet2(const CVector2D& p, bool flip, int type, int attack_no);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};