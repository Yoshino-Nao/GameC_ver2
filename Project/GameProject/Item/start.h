#pragma once
#include "../Base/Base.h"

class start :public Base {
private:
	//画像オブジェクト
	CImage m_img;
public:
	bool Gstart;
	start(const CVector2D& pos);
	void Draw();
	void Collision(Base* b);
};
