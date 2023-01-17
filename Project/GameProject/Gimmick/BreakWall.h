#pragma once
#include"../Base/Base.h"
class BreakWall :public Base {
private:
	int m_type;
	CImage m_img;
public:
	BreakWall(int type,const CVector2D& pos);
	void Update();
	void Draw();
};
