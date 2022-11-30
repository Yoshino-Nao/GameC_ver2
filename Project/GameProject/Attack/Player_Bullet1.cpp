#include "Player_Bullet1.h"
#include "../Map/Map.h"
#include "../Game/GameData.h"
#include "../Character/Player.h"
Player_Bullet1::Player_Bullet1(const CVector2D& p, bool flip, int type, int attack_no) 
	:Base(eType_Player_Bullet)
{
	//�摜����
	m_img = COPY_RESOURCE("Effect_Flame", CImage);
	//m_img.SetSize(128, 32);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//���S�ʒu�ݒ�
	//m_img.SetCenter(64, 16);
	//���]�t���O
	m_flip = flip;

	//m_rect = CRect(-16, -16, 16, 16);
	
	//�e���Ŏ���
	cnt = 60;
	//���ߎ���
	//Ccnt = 0;
	//�U���ԍ�
	m_attack_no = rand();
	m_attack_no = attack_no;
	//Player���]�t���O�擾

	Base* b = Base::FindObject(eType_Player);
	Player* f = dynamic_cast<Player*>(b);
	if (b) 
	{
		m_flip = f->GetFlipFlag();
	}

}

void Player_Bullet1::Update()
{
	m_pos_old = m_pos;
	m_img.UpdateAnimation();
	m_img.SetSize(128, 32);
	m_img.SetCenter(80, 16);
	cnt--;
	m_rect = CRect(-32, -24, 32, 24);
	if (m_flip) {
		CVector2D vec = CVector2D(10, 0);
		m_pos += vec;
	}
	else {
		CVector2D vec = CVector2D(10, 0);
		m_pos -= vec;
	}
	if (cnt <= 0) {
		SetKill();
	}
}

void Player_Bullet1::Draw()
{
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	DrawRect();
}

void Player_Bullet1::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(m_pos, m_rect,&m_pos);
			if (t != NULL_TIP)
				m_vec = CVector2D(sin(m_ang) * -1, cos(m_ang));
			
		}
		break;
		//case eType_Enemy:
			//SetKill();

	}
}
