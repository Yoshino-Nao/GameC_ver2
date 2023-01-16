#pragma once
#include"../Base/Base.h"
class BreakWall :public Base {
private:
	CImage m_img;
public:
	BreakWall(const CVector2D& pos);
	void Draw();
};
