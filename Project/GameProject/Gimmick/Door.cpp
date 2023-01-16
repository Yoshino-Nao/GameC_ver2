#include "Door.h"
Door::Door(const CVector2D& pos, int key)
	:Base(eType_Door)
{	
	//Key�ϐ�(0�Ȃ�ʉ߉\)
	m_key = key;
	//�O���t�B�b�N�����ւ��p
	switch (key)
	{
	case 0:
		
	case 1:

		break;
	}
	m_img = COPY_RESOURCE("MapTip_64", CImage);
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
