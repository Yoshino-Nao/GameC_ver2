#include "Door.h"
Door::Door(const CVector2D& pos, int key)
	:Base(eType_Door)
{	
	//Key�ϐ�(0�Ȃ�ʉ߉\)
	m_key = key;
	//�O���t�B�b�N�����ւ��p
	m_img = COPY_RESOURCE("Lattice", CImage);
	switch (key)
	{
	case 0:
		m_img.SetColor(1, 1, 1, 1);
	case 1:
		m_img.SetColor(0.8f, 0.8f, 0.8f, 1);
		break;
	case 2:
		m_img.SetColor(1.0f, 0.5f, 0.5f, 1);
		break;
	case 3:
		m_img.SetColor(1.0f, 1.0f, 0.5f, 1);
		break;
	}
	//m_img = COPY_RESOURCE("Lattice", CImage);
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(64 * 2, 64 * 2);
	m_img.SetRect(128, 0, 128 + 64, 64);
	//���S�ʒu�ݒ�
	m_img.SetCenter(64, 64);
	//�����蔻��p��`
	m_rect = CRect(-64, -64, 64, 64);
}

void Door::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}

int Door::GetKey()
{
	return m_key;
}
