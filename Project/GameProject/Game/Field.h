#pragma once
#include "../Base/Base.h"

class Field :public Base {
private:
	//画像オブジェクト(前景)
	CImage m_foreground;
	//画像オブジェクト(遠景)
	CImage m_town;
	//画像オブジェクト(最遠景)
	CImage m_sky;
	//地面の高さ
	float m_ground_y;
public:
	//
	Field();
	//
	void Draw();

	//
	float GetGroundY() {
		return m_ground_y;
	}
};
