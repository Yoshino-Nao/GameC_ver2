#pragma once
#include "../Base/Base.h"

class Effect_Ring :public Base {
private:
	//画像オブジェクト
	CImage m_img;
	//反転フラグ
	bool m_flip;
	int Pstate;
public:
	Effect_Ring(const char* name, const CVector2D& pos, bool flip, float m_ang, float w, float h);
	void Update();
	void Draw();
};
