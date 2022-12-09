#include "Slash.h"

Slash::Slash(const CVector2D& pos, int r, bool flip, int type, int attack_no)
	:Base(type) {
	//�摜����
	m_img = COPY_RESOURCE("Effect_Slash", CImage);
	//���]�t���O�ݒ�
	m_flip = flip;
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(r * 2, r * 2);
	//���S�ʒu�ݒ�
	m_img.SetCenter(r, r);
	//�����蔻��p��`
	m_rect = CRect(-r, -r, r, r);
	//�Đ��A�j���[�V�����ݒ�(�񃋁[�v)
	m_img.ChangeAnimation(0, false);
	//�U���ԍ�
	m_attack_no = attack_no;
}

void Slash::Update()
{//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	m_img.SetColor(0, 0, 0, 0);
	//�A�j���[�V�����I���`�F�b�N
	if (m_img.CheckAnimationEnd()) {
		//�G�t�F�N�g���폜
		SetKill();
	}
	
}

void Slash::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
	
	DrawRect();
}
