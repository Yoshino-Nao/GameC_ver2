#pragma once
#include "../Base/Base.h"

class Door :public Base {
private:
	CImage m_img;
public:
	Door(const CVector2D& pos);
	void Draw();
	void Collision(Base* b);
	void Update();
};
