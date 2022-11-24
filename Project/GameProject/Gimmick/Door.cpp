#include "Door.h"
#include "../Character/Player.h"
#include "../Map/Map.h"
Door::Door(const CVector2D& pos)
	:Base(eType_Door)
{
	m_img = COPY_RESOURCE("Door", CImage);
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(MAP_TIP_SIZE * 2, MAP_TIP_SIZE * 2);
	//中心位置設定
	m_img.SetCenter(MAP_TIP_SIZE, MAP_TIP_SIZE);
	//当たり判定用矩形
	m_rect = CRect(-MAP_TIP_SIZE, -MAP_TIP_SIZE, MAP_TIP_SIZE , MAP_TIP_SIZE);
	//m_rect = CRect(-3, -3, 3, 3);
}

void Door::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}

void Door::Collision(Base* b)
{
	switch (b->m_type){
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			Map* m = dynamic_cast<Map*>(b);
			int t = m->CollisionMap(m_pos);
			if (t == 2) {
				m->SetTip(m_pos, 0);
				m->SetTip(m_pos + CVector2D(0, -MAP_TIP_SIZE), 0);
				SetKill();
			}
		}
		break;
	}
}

void Door::Update()
{
}
