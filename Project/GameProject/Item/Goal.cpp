#include "Goal.h"

Goal::Goal(const CVector2D& pos)
	:Base(eType_Goal)
{
	//�摜����
	m_img = COPY_RESOURCE("Goal", CImage);
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(64*2, 64*2);
	//���S�ʒu�ݒ�
	m_img.SetCenter(32,128);
	//�����蔻��p��`
	m_rect = CRect(-64, -128, 64, 0);
}

void Goal::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();

}

void Goal::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			b->SetKill();
		}
		break;
	}
}
