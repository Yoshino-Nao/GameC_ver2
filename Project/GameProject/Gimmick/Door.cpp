#include "Door.h"
#include "../Character/Player.h"
#include "../Map/Map.h"
#include "../Map/fmfmap.h"
Door::Door(const CVector2D& pos)
	:Base(eType_Door)
{
	
	m_img = COPY_RESOURCE("Door", CImage);
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(64 * 2, 64 * 2);
	//���S�ʒu�ݒ�
	m_img.SetCenter(64, 64);
	//�����蔻��p��`
	m_rect = CRect(-64, -64, 64, 64);
	//m_rect = CRect(-3, -3, 3, 3);
}

void Door::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}
