#pragma once
#include "../Base/Base.h"

class Slash :public Base {
private:
	//画像オブジェクト
	CImage m_img;
	//反転フラグ
	bool m_flip;
	int m_attack_pow;
	//攻撃番号
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
