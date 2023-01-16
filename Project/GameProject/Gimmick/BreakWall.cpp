#include "BreakWall.h"

BreakWall::BreakWall(const CVector2D& pos):Base(eType_BreakWall)
{
	m_img = COPY_RESOURCE("MapTip_64", CImage);
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(64, 64);
	m_img.SetRect(64, 0, 64 + 64, 64);
	//���S�ʒu�ݒ�
	m_img.SetCenter(0, 32);
	//�����蔻��p��`
	m_rect = CRect(0, -32, 64, 32);
}

void BreakWall::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}
