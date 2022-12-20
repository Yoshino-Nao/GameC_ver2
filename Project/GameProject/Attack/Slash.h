#pragma once
#include "../Base/Base.h"

class Slash :public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
	//���]�t���O
	bool m_flip;
	int m_attack_pow;
	//�U���ԍ�
	int m_attack_no;
public:
	Slash(const CVector2D& pos, int r, bool flip, int type, int attack_no, int attack_pow);
	void Update();
	void Draw();
	int GetAttackPow() {
		return m_attack_pow;
	}
	int GetAttackNo() {
		return m_attack_no;
	}
};
