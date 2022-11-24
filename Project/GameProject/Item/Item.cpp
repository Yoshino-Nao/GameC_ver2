#include "Item.h"
#include "../Game/GameData.h"
#include "../Map/Map.h"
Item_Score::Item_Score(const CVector2D& pos)
	:Base(eType_Item_Score)
{
	m_img = COPY_RESOURCE("coin", CImage);
	m_pos = pos;
	m_img.SetSize(48, 96);
	m_img.SetCenter(28, 72);
	m_rect = CRect(-24, -48, 24, 0);	
	m_img.ChangeAnimation(0);
	m_vec.y = -10;
	m_is_ground = true;
}

void Item_Score::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}

void Item_Score::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0) {
				m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	}
}

void Item_Score::Update()
{
	m_pos_old = m_pos;
	m_img.UpdateAnimation();
	if (m_is_ground && m_vec.y > GRAVITY * 4) {
		m_is_ground = false;
	}
	m_vec.y += GRAVITY;
	m_pos += m_vec;
}

Item_LifeUp::Item_LifeUp(const CVector2D& pos)
	:Base(eType_Item_LifeUp)
{
	m_img = COPY_RESOURCE("coin", CImage);
	m_pos = pos;
	m_img.SetSize(48, 96);
	m_img.SetCenter(28, 72);
	m_img.SetColor(0, 1, 0, 1);
	m_rect = CRect(-24, -48, 24, 0);
	m_img.ChangeAnimation(0);
	m_vec.y = -10;
	m_is_ground = true;
}

void Item_LifeUp::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}

void Item_LifeUp::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0) {
				m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	}
}

void Item_LifeUp::Update()
{
	m_pos_old = m_pos;
	m_img.UpdateAnimation();
	if (m_is_ground && m_vec.y > GRAVITY * 4) {
		m_is_ground = false;
	}
	m_vec.y += GRAVITY;
	m_pos += m_vec;
}