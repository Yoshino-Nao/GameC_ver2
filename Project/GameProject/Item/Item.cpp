#include "Item.h"
#include "../Game/Effect.h"
#include "../Game/GameData.h"
#include "../Map/Map.h"
#include "../Gimmick/Door.h"
Item::Item(const CVector2D& pos, int item_id)
	:Base(eType_Item)
{
	//‰æ‘œ·‚µ‘Ö‚¦—\’è
	m_item_id = item_id;
	m_cnt = 0;
	m_pos = pos;
	m_pos_old = m_pos;
	//m_rect = CRect(-24, -24, 24, 24);
	//’†SˆÊ’uÝ’è
	m_vec.y = -10;
	m_is_ground = true;
	switch (item_id)
	{
	case eType_Item_Score:
		m_img = COPY_RESOURCE("coin", CImage);
		m_img.SetCenter(24, 48);
		m_rect = CRect(-24, -24, 24, 24);
		m_img.SetSize(48, 96);
		m_img.ChangeAnimation(0);
		break;
	case eType_Item_LifeUp:
		m_img = COPY_RESOURCE("coin", CImage);
		m_img.SetCenter(24, 48);
		m_rect = CRect(-24, -24, 24, 24);
		m_img.SetSize(48, 96);
		m_img.ChangeAnimation(0);
		m_img.SetColor(0, 1, 0, 1);
		break;
	case eType_Item_AirJump:
		m_img = COPY_RESOURCE("coin", CImage);
		m_img.SetCenter(24, 48);
		m_rect = CRect(-24, -24, 24, 24);
		m_img.SetSize(48, 96);
		m_img.ChangeAnimation(0);
		m_img.SetColor(0, 0, 0, 0);
		break;
	case eType_Item_Sword:
		m_img = COPY_RESOURCE("Sword", CImage);
		m_img.SetCenter(14 * 3, 2 * 3);
		m_rect = CRect(-14 * 3, -4 * 3, 14 * 3, 4 * 3);
		m_img.SetSize(33 * 3, 6);
		//m_img.SetColor(0, 0, 0, 0);
		break;
	case eType_Item_Kay1:
		m_img = COPY_RESOURCE("coin", CImage);
		m_img.SetCenter(24, 48);
		m_rect = CRect(-24, -24, 24, 24);
		m_img.SetSize(48, 96);
		m_img.ChangeAnimation(0);
		m_img.SetColor(1, 0, 0, 1);
		break;
	case eType_Item_Kay2:
		m_img = COPY_RESOURCE("coin", CImage);
		m_img.SetCenter(24, 48);
		m_rect = CRect(-24, -24, 24, 24);
		m_img.SetSize(48, 96);
		m_img.ChangeAnimation(0);
		m_img.SetColor(1, 0, 0, 1);
		break;
	case eType_Item_Kay3:
		m_img = COPY_RESOURCE("coin", CImage);
		m_img.SetCenter(24, 48);
		m_rect = CRect(-24, -24, 24, 24);
		m_img.SetSize(48, 96);
		m_img.ChangeAnimation(0);
		m_img.SetColor(1, 0, 0, 1);
		break;
	}

}

void Item::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}

void Item::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			CVector2D pos;
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect, &pos);
			if (t != NULL_TIP) {
				m_pos.x = pos.x;
				m_vec.x *= -1;
			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect, &pos);
			if (t != NULL_TIP) {
				m_pos.y = pos.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	case eType_Door:
		if (Base::CollisionObject(CVector2D(m_pos.x, m_pos_old.y), m_rect, b->m_pos, b->m_rect)) {
			if (Door* d = dynamic_cast<Door*>(b)) {
				m_pos.x = m_pos_old.x;
			}
		}
		if (Base::CollisionObject(CVector2D(m_pos_old.x, m_pos.y), m_rect, b->m_pos, b->m_rect)) {

			m_pos.y = m_pos_old.y;
			m_vec.y = 0;
			m_is_ground = true;
		}
		break;
	}
}

void Item::Update()
{
	m_cnt--;
	m_pos_old = m_pos;
	m_img.UpdateAnimation();
	if (m_is_ground && m_vec.y > GRAVITY * 4) {
		m_is_ground = false;
	}
	if (m_item_id == eType_Item_AirJump && m_cnt <= 0) {
		Base::Add(new Effect("Effect_Ring_yoko", CVector2D(m_pos.x, m_pos.y), true, 90, 30));
		m_cnt = 60;
	}
	m_vec.y += GRAVITY;
	m_pos.y += m_vec.y;
}

int Item::GetItemId()
{
	return m_item_id;
}

//Item_LifeUp::Item_LifeUp(const CVector2D& pos)
//	:Base(eType_Item_LifeUp)
//{
//	m_img = COPY_RESOURCE("coin", CImage);
//	m_pos = pos;
//	m_img.SetSize(48, 96);
//	m_img.SetCenter(28, 72);
//	m_img.SetColor(0, 1, 0, 1);
//	m_rect = CRect(-24, -48, 24, 0);
//	m_img.ChangeAnimation(0);
//	m_vec.y = -10;
//	m_is_ground = true;
//}
//
//void Item_LifeUp::Draw()
//{
//	m_img.SetPos(GetScreenPos(m_pos));
//	m_img.Draw();
//	DrawRect();
//}
//
//void Item_LifeUp::Collision(Base* b)
//{
//	switch (b->m_type) {
//	case eType_Field:
//		if (Map* m = dynamic_cast<Map*>(b)) {
//			CVector2D pos;
//			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect, &pos);
//			if (t != 0) {
//				m_pos.x = pos.x;
//				m_vec.x *= -1;
//			}
//			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect, &pos);
//			if (t != 0) {
//				m_pos.y = pos.y;
//				m_vec.y = 0;
//				m_is_ground = true;
//			}
//		}
//		break;
//	}
//}
//
//void Item_LifeUp::Update()
//{
//	m_pos_old = m_pos;
//	m_img.UpdateAnimation();
//	if (m_is_ground && m_vec.y > GRAVITY * 4) {
//		m_is_ground = false;
//	}
//	m_vec.y += GRAVITY;
//	m_pos += m_vec;
//}