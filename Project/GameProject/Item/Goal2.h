#pragma once
#include "../Base/Base.h"

class Goal2 :public Base {
private:
	//画像オブジェクト
	CImage m_img;
public:
	bool Ggoal2;
	Goal2(const CVector2D& pos);
	void Draw();
	void Collision(Base* b);
};
