#include "EnemyBullet.h"
#include "../Game/Map.h"
#include "../Game/Effect_Ring.h"
#include "../Character/Player.h"
EnemyBullet::EnemyBullet(
	int type, const CVector2D& pos, int attack_no,
	float r, float g, float b, float t) 
	:Base(eType_Bullet) {
	m_img = COPY_RESOURCE("ball", CImage);
	m_pos = pos;
	m_img.SetSize(32, 32);
	m_img.SetColor(r, g, b, t);
	m_img.SetCenter(16, 16);
	m_rect = CRect(-8, -8, 8, 8);
	m_attack_no = rand();
	//m_ang = ang;
	m_speed = 4;
	cnt = 0;
	m_attack_no = attack_no;
}
void EnemyBullet::Update(){
	cnt++;
	Base* b = Base::FindObject(eType_Player);
	Player* f = dynamic_cast<Player*>(b);
	if (b) {
		CVector2D Player_pos = f->GetPos();
		CVector2D diff = Player_pos - m_pos;
		m_ang = atan2(diff.x, diff.y);
		m_vec = CVector2D(sin(m_ang), cos(m_ang)) * m_speed;
		m_pos += m_vec;
		if (cnt >= 180) {
			SetKill();
		}
	}
}
void EnemyBullet::Draw(){
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetAng(m_ang);
	m_img.Draw();
	//DrawRect();
}
void EnemyBullet::Collision(Base* b){
	switch (b->m_type) {
		
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			//const CVector2D& pos, const CRect& rect
			int t = m->CollisionMap(m_pos,m_rect);
			if (t != 0)
				SetKill();
		}
		break;
		
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			SetKill();
		}
		break;
		/*
	case eType_Enemy:
		if (m_type == eType_Player_Bullet && Base::CollisionCircle(this, b)) {
			SetKill();
			b->SetKill();
		}
		break;*/
	}
}
