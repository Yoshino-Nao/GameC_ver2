#include "Effect_Ring.h"
#include"../Character/Player.h"

#include"../Attack/Player_Bullet1.h"
Effect_Ring::Effect_Ring(const char* name, const CVector2D& pos, bool flip, float ang, float w, float h) :
	Base(eType_AtkEffect)
{
	//�摜����
	m_img = COPY_RESOURCE(name, CImage);
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	//m_img.SetSize(16*2, 144);
	m_img.SetSize(w, h);
	//m_img.SetSize(3600, 1440);
	//���S�ʒu�ݒ�
	m_img.SetCenter(16, 40*2);
	//�Đ��A�j���[�V�����ݒ�(�񃋁[�v)
	m_img.ChangeAnimation(0, false);
	//���]�t���O
	m_flip = flip;
	m_ang = ang;
	Pstate = 0;
}

void Effect_Ring::Update()
{

	Base* b = Base::FindObject(eType_Player);
	Player* f = dynamic_cast<Player*>(b);

	//Base* b1 = Base::FindObject(eType_Player_Bullet1);
	//Player_Bullet1* w = dynamic_cast<Player_Bullet1*>(b1);
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();

	m_flip = f->GetFlipFlag();
	if (m_flip) {
		m_pos = f->GetPos() + CVector2D(+60, -70);
	}
	else {
		m_pos = f->GetPos() + CVector2D(-60, -70);
	}
	//�A�j���[�V�����I���`�F�b�N
	if (m_img.CheckAnimationEnd() || !HOLD(CInput::eButton1)) {
		//�G�t�F�N�g���폜	
		SetKill();
	}

	/*
	if (b && Pstate == 0) {
		m_flip = f->GetFlipFlag();
		if (m_flip) {
			m_pos = f->GetPos() + CVector2D(+60, -70);
		}
		else {
			m_pos = f->GetPos() + CVector2D(-60, -70);
		}
	}*/
}
	
	

void Effect_Ring::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
