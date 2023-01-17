#include "Event.h"

Event::Event(int type, const CRect& rect)
	:Base(eType_Event)
{
	m_type = type;
	m_pos = CVector2D(rect.m_left, rect.m_top);
	m_rect = CRect(0, 0, rect.m_right, rect.m_bottom);

}

Event::~Event() {
}

void Event::Draw()
{
	//デバッグ表示
	//DrawRect();
}

int Event::GetEventNum()
{
	return m_type;
}
