#pragma once
#include "../Base/Base.h"
#include "../Map/fmfmap.h"
#include "../Map/Map.h"
class Door :public Base{
private:
	CImage m_img;
public:
	Door(const CVector2D& pos);
	void Draw();
};
