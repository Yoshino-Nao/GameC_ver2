#pragma once
#include "../Base/Base.h"

class Item : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	bool m_is_ground;
	int m_item_id;
	int m_cnt;
	float m_pop;
public:
	Item(const CVector2D& pos,int item_id);
	void Draw();
	void Collision(Base* b);
	void Update();
	int GetItemId();
};
//class Item_LifeUp : public Base {
//private:
//	//画像オブジェクト
//	CImage m_img;
//	bool m_is_ground;
//public:
//	Item_LifeUp(const CVector2D& pos);
//	void Draw();
//	void Collision(Base* b);
//	void Update();
//};