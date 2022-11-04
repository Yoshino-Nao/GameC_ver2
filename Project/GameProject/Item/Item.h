#pragma once
#include "../Base/Base.h"

class Item_Score : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	bool m_is_ground;
public:
	Item_Score(const CVector2D& pos);
	void Draw();
	void Collision(Base* b);
	void Update();
};
class Item_LifeUp : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	bool m_is_ground;
public:
	Item_LifeUp(const CVector2D& pos);
	void Draw();
	void Collision(Base* b);
	void Update();
};