#include "Player_Bullet1.h"
#include "../Map/Map.h"
#include "../Game/GameData.h"
#include "../Character/Player.h"
Player_Bullet1::Player_Bullet1(const CVector2D& p, float ang, bool flip, int attack_no, int pow)
	:Base(eType_Player_Bullet)
{
	//�摜����
	m_img = COPY_RESOURCE("bullet", CImage);
	//���W�ݒ�
	m_pos = p;
	//�p�x
	m_ang = ang;
	//���]�t���O
	m_flip = flip;
	m_rect = CRect(-6, -3, 6, 3);
	//m_rect = CRect(-16, -16, 16, 16);
	m_speed = 10;
	//�e���Ŏ���
	cnt = 60;
	//�U���ԍ�
	//m_attack_no = rand();
	m_attack_no = attack_no;
	m_pow = pow;
}

void Player_Bullet1::Update()
{

	m_pos_old = m_pos;
	cnt--;
	m_vec = CVector2D(cosf(m_ang), sinf(m_ang)) * m_speed;
	m_pos += m_vec;
	if (cnt < 0) {
		SetKill();
	}

	
}

void Player_Bullet1::Draw()
{
	m_img.SetSize(12, 1);
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	m_img.SetAng(-m_ang);
	//�`��
	m_img.Draw();
	//DrawRect();
}

void Player_Bullet1::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(m_pos, m_rect,&m_pos);
			if (t != NULL_TIP)
				SetKill();
			
		}
		break;
	//case eType_Enemy:
			//SetKill();

	}
}
