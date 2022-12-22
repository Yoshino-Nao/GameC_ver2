#include "Base.h"
std::list<Base*>Base::m_list;
//スクロール値の定義
CVector2D Base::m_scroll(0, 0);
Base::Base(int type) : m_type(type), m_kill(false), m_pos(0, 0), m_vec(0, 0), m_rad(0), m_ang(0) {

}

Base::~Base() {

}

void Base::Update() {

}

void Base::Draw() {

}

void Base::UpdateAll()
{
	for (auto& b : m_list) {
		b->Update();
	}
}

void Base::DrawAll() {
	for (auto& b : m_list) {
		b->Draw();
	}
}

void Base::Add(Base*b) {
	//Type順によるソート
	auto itr = m_list.begin();
	while (itr != m_list.end()) {
		if ((*itr)->m_type > b->m_type) {
			m_list.insert(itr, b);
			return;
		}
		itr++;
	}
	m_list.push_back(b);
}
void Base::KillAll()
{
	std::list<Base*>ret;
	for (auto& b : m_list) {
		b->SetKill();
	}
}
void Base::KillByType(int type)
{
	//指定の種類を全て削除
	std::list<Base*> ret;
	for (auto& b : m_list) {
		if (b->m_type == type)
			b->SetKill();
	}
}
void Base::Collision(Base* b) {

}
void Base::CollisionAll() {
	auto it1 = m_list.begin();
	auto last = m_list.end();
	while (it1 != last) {
		auto it2 = it1;
		it2++;
		while (it2 != last) {
			(*it1)->Collision(*it2);
			(*it2)->Collision(*it1);
			it2++;
		}
		it1++;
	}
}
bool Base::CollisionCircle(Base* b1, Base* b2) {
	CVector2D v = b1->m_pos - b2->m_pos;
	float l = v.Length();
	if (l < b1->m_rad + b2->m_rad) {
		return true;
	}
	return false;

}
void Base::CheckKillAll()
{
	auto it = m_list.begin();
	auto last = m_list.end();
	while (it != last) {
		if ((*it)->m_kill) {
			delete (*it);
			it = m_list.erase(it);
		}
		else {
			//次へ
			it++;
		}
	}
}
Base* Base::FindObject(int type)
{
	//先頭の要素
	auto it = m_list.begin();
	//末尾の要素
	auto last = m_list.end();
	//itが末尾でなければ
	while (it != last) {
		if ((*it)->m_type == type) {
			//見つけたオブジェクトの返却
			return (*it);
		}
		it++;
	}
	return nullptr;
}
std::list<Base*> Base::FindObjects(int type) {
	std::list<Base*>ret;
	for (auto& b : m_list) {
		if (b->m_type == type)
			ret.push_back(b);
	}
	return ret;
}

CVector2D Base::GetScreenPos(const CVector2D& pos)
{
	//座標-スクロール値=画面上での位置
	return pos - m_scroll;

	return CVector2D();
}

void Base::DrawRect()
{
	//デバッグ用　矩形の表示
	CRect rect = CRect(
		m_pos.x + m_rect.m_left,
		m_pos.y + m_rect.m_top,
		m_pos.x + m_rect.m_right,
		m_pos.y + m_rect.m_bottom);
	Utility::DrawQuad(
		CVector2D(rect.m_left, rect.m_top) - m_scroll,
		CVector2D(rect.m_width, rect.m_height),
		CVector4D(1, 0, 0, 0.5f));
}
void Base::DrawLine(CVector2D p1, CVector2D p2, float r, float g, float b)
{
	Utility::DrawLine(p1 - m_scroll, p2, CVector4D(r, g, b, 0.8f));
}
//DrawLine(const CVector3D &s, const CVector3D &e, const CVector4D &color);
bool Base::CollisionRect(Base* b1, Base* b2) {
	//b1の矩形
	CRect rect1 = CRect(
		b1->m_pos.x + b1->m_rect.m_left,
		b1->m_pos.y + b1->m_rect.m_top,
		b1->m_pos.x + b1->m_rect.m_right,
		b1->m_pos.y + b1->m_rect.m_bottom);
	//b2の矩形
	CRect rect2 = CRect(
		b2->m_pos.x + b2->m_rect.m_left,
		b2->m_pos.y + b2->m_rect.m_top,
		b2->m_pos.x + b2->m_rect.m_right,
		b2->m_pos.y + b2->m_rect.m_bottom);
	//矩形同士の判定
	if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
		rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
		return true;

	return false;
}

bool Base::CollisionObject(CVector2D p1, CRect r1, CVector2D p2, CRect r2)
{
	CRect rect1 = CRect(
		p1.x + r1.m_left,
		p1.y + r1.m_top,
		p1.x + r1.m_right,
		p1.y + r1.m_bottom);
	//b2の矩形
	CRect rect2 = CRect(
		p2.x + r2.m_left,
		p2.y + r2.m_top,
		p2.x + r2.m_right,
		p2.y + r2.m_bottom);
	//矩形同士の判定
	if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
		rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
		return true;
	
	return false;
}



