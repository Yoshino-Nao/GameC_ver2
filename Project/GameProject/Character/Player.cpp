#include "../Base/Base.h"
#include "../Game/AnimData.h"
#include "../Game/Field.h"
#include "../Game/Slash.h"
#include "../Game/Effect.h"
#include "../Game/Game.h"
#include "../Game/Effect_Ring.h" 
#include "../Game/Map.h"
#include "../Game/GameData.h"
#include "../Attack/EnemyBullet.h"
#include "../Attack/Player_Bullet1.h"
#include "../Item/Item.h"
#include "../Title/Title.h"
#include "../Item/Item.h"
#include "../UI/Menu.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

void Player::StateIdle()
{
	Ccnt = 120;
	/*
	//�ő呬�x
	const float move_speed_max = 10;
	//�����x
	const float move_speed_add = 0.5f;
	//�W�����v��
	const float jump_pow = 18;
	*/
	//�ړ��t���O
	bool move_flag = false;
	//���ړ�
	if (HOLD(CInput::eLeft)) {
		vec.x -= move_speed_add;
		/*
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;*/
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		vec.x += move_speed_add;
		/*
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;*/
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}
	//�W�����v
	if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
		m_airjump = true;
	}
	
	if (HOLD(CInput::eButton1)) {
		m_state = eState_Shooting;
		m_attack_no++;
	}
	
	if (vec.x < -move_speed_max) {
		vec.x = -move_speed_max;
	}
	if (vec.x > move_speed_max) {
		vec.x = move_speed_max;
	}
	m_pos.x += vec.x;
	/*
	//�U��
	if (HOLD(CInput::eButton1)) {
		Base* b = Base::FindObject(eType_Ball);
		if (!b) {
			Base::Add(new Attack(CVector2D(1280, 560), m_flip, eType_Ball, m_attack_no));
			m_img.ChangeAnimation(eAnimAtkIdle);
		}
		
		else if (!b && !m_flip) {

			Base::Add(new Attack(CVector2D(1280, 560), true, eType_Ball,m_attack_no));
		}
		//�U����Ԃֈڍs
		//m_state = eState_Attack;
		//m_attack_no++;
	}*/
	
	//�W�����v���Ȃ�
	if (!m_is_ground) {
		if (m_vec.y < 0)
			//�㏸�A�j���[�V����
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//���~�A�j���[�V����
			m_img.ChangeAnimation(eAnimJumpDown, false);
		//�Q�i�W�����v
		if (m_airjump && m_img.GetIndex() >= 3 && PUSH(CInput::eButton2)) {
			m_vec.y = (jump_pow * -0.5f);
			m_is_ground = false;
			m_airjump = false;
		}
		//�\��
	}
	//�ړ����Ȃ�
	else {
		if (move_flag) {
			//����A�j���[�V����
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			vec.x = 0;
			//�ҋ@�A�j���[�V����
			m_img.ChangeAnimation(eAnimIdle);
		}
	}	
	
}

void Player::StateAttack()
{
	
}

void Player::StateShooting()
{
	//�ړ��t���O
	bool move_flag = false;
	
	//���ړ�
	if (HOLD(CInput::eLeft)) {
		vec.x -= move_speed_add;
		/*
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;*/
		//���]�t���O
		
		m_flip = true;
		move_flag = true;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		vec.x += move_speed_add;
		/*
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;*/
		//���]�t���O
		
		m_flip = false;
		move_flag = true;
	}
	//�W�����v
	if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
		m_airjump = true;
	}
	//�eflip�␳
	if (m_flip) {
		Bulletpos = -60;
	}
	else {
		Bulletpos = 60;
	}
	if (vec.x < -move_speed_max) {
		vec.x = -move_speed_max;
	}
	if (vec.x > move_speed_max) {
		vec.x = move_speed_max;
	}
	m_pos.x += vec.x;
	
	
	
	Base* b = Base::FindObject(eType_Player_Bullet);
	if (!b) {
		if (Ccnt == 120)
		{	
			Base::Add(new Effect_Ring("Effect_Ring", m_pos, m_flip, m_ang, 32, 144));
		}
		if (Ccnt == 60)
		{
			Base::Add(new Effect_Ring("Effect_Ring2", m_pos, m_flip, m_ang, 32, 144));
		}
		if (FREE(CInput::eButton1)) 
		{
			if (Ccnt <= 120 && Ccnt >= 61) 
			{
				Base::Add(new Player_Bullet1(m_pos + CVector2D(Bulletpos, -75), m_flip, eType_Player_Bullet, m_attack_no));
			}
			m_state = eState_Idle;
		}
	}
	
	
	//�U����Ԃֈڍs
	//m_state = eState_Attack;
	//m_attack_no++;
	//�W�����v���Ȃ�
	if (!m_is_ground) 
	{
		if (m_vec.y < 0) 
		{
			//�㏸�A�j���[�V����
			m_img.ChangeAnimation(eAnimAtkJumpUp, false);
		}
		else 
		{
			//���~�A�j���[�V����
			m_img.ChangeAnimation(eAnimAtkJumpDown, false);
			//�Q�i�W�����v
			if (m_airjump && m_img.GetIndex() >= 3 && PUSH(CInput::eButton2)) {
				m_vec.y = (jump_pow * -0.5f);
				m_is_ground = false;
				m_airjump = false;
			}
		}
	}
	//�ړ����Ȃ�
	else {
		if (move_flag) 
		{
			//����A�j���[�V����
			m_img.ChangeAnimation(eAnimAtkRun);
		}
		else 
		{
			vec.x = 0;
			//�ҋ@�A�j���[�V����
			m_img.ChangeAnimation(eAnimAtkIdle);
		}
	}
	Ccnt--;
	if (Ccnt <= 0) {
		Ccnt = 0;
	}
}

void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	m_is_inv = true;
	invtime = 120;
	if (m_flip) {
		m_pos.x += 5;
	}
	else {
		m_pos.x -= 5;
	}
	if (m_img.CheckAnimationEnd()) 
	{
		m_state = eState_Idle;
	}
}

void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) 
	{
		m_kill = true;
	}
}

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//�摜����
	m_img = COPY_RESOURCE("Player", CImage);
	m_img.SetSize(224, 224);

	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//���S�ʒu�ݒ�
	m_img.SetCenter(112, 192);
	//���]�t���O
	m_flip = flip;
	//�����蔻��
	m_rect = CRect(-28, -124, 28, 0);
	//�ʏ��Ԃ�
	m_state = eState_Idle;
	//�ő呬�x
	move_speed_max = 10;
	//�����x
	move_speed_add = 0.5f;
	//�W�����v��
	jump_pow = 18;
	//���n�t���O
	m_is_ground = true;
	//�Q�i�W�����v�t���O
	m_airjump = false;
	//�W�����vindex�擾
	jumpindex = 0;
	//���G�t���O
	m_is_inv = false;
	//Attack��State
	Pstate = 0;
	//�U���ԍ�
	m_attack_no = rand();
	//�eflip�␳�l
	Bulletpos = 60;
	//�_���[�W�ԍ�
    m_damage_no = -1;
	//���ߎ���
	Ccnt = 120;
	//���G����
	invtime = 0;
	//��~����
	stpdtime = 0;
	//HP
	m_hp = 120;
	//�ő�HP
	m_hpmax = 120;
	//�G�U����
	m_pow = 0;
	//�v���C���[�ړ���
	CVector2D vec(0, 0);
	//�J�����ړ���
	CVector2D sc_vec(0, 0);
	//�����X�N���[���ݒ�
	
	
	/*
	m_img.SetSize(224 / 2, 224 / 2);
	m_img.SetCenter(112 / 2, 192 / 2);
	m_rect = CRect(-28 / 2, -124 / 2, 28 / 2, 0);*/
}

void Player::Update() {
	m_img.SetColor(1, 1, 1, 1);
	//std::cout << "Player" << std::endl;
	m_pos_old = m_pos;
	stpdtime--;
	if (stpdtime <= 0) {
		//�X�N���[���ݒ�
		//m_scroll.x = m_pos.x - 1280 / 6;
		//m_scroll.y = m_pos.y - 500;
		switch (m_state) {
			//�ʏ���
		case eState_Idle:
			StateIdle();
			break;
			//�U�����
		case eState_Attack:
			StateAttack();
			break;
			//���ˏ��
		case eState_Shooting:
			StateShooting();
			break;
			//�_���[�W���
		case eState_Damage:
			StateDamage();
			break;
			//�_�E�����
		case eState_Down:
			StateDown();
			break;
		}
		
		/*
		Base* a = Base::FindObject(eType_Player_Bullet1);
		Player_Bullet1* w = dynamic_cast<Player_Bullet1*>(a);
		if (a) {
			Pstate = w->GetState();
			if (Pstate == 2) {
				//Base::Add(new Effect_Ring("Effect_Ring2", m_pos, m_flip, m_ang));
			}
		}*/
		//�X�N���[���␳
		//�ڕW�l
		CVector2D v3(0, 0);
		//�����Ă����痎������Ԃֈڍs
		if (m_is_ground && m_vec.y > GRAVITY * 4) {
			m_is_ground = false;
			m_airjump = true;
		}

		if (m_vec.y > GRAVITY * 4 || m_vec.y < -1)
		{
			v3.y = 300;
		}
		else
		{
			v3.y = 0;
		}
		if (m_flip) {
			v3.x = -300;
		}
		else
		{
			v3.x = +300;
		}

		CVector2D v2 = v3 - sc_vec;
		//�X�N���[�������x
		sc_vec += v2 * 0.05;
		//��l+�␳�l
		m_scroll.x = m_pos.x - 1280 / 2 + sc_vec.x;
		m_scroll.y = m_pos.y - 600 + sc_vec.y;
		//���G����
		if (m_is_inv) {
			invtime--;
			m_img.SetColor(1, 1, 1, 0.5);
			if (invtime <= 0) {
				m_is_inv = false;
				invtime = 0;
			}
		}

		//�d�͂ɂ�闎��
		m_vec.y += GRAVITY;
		//�A�j���[�V�����X�V
		m_img.UpdateAnimation();
		m_pos += m_vec;
		stpdtime = 0;
		if (PUSH(CInput::eButton5)) {
			Base::Add(new Menu());
		}
	}
}

void Player::Draw() {
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	//DrawRect();
	
}

void Player::Collision(Base* b)
{
	switch (b->m_type) {
		//�S�[������
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			b->SetKill();
		}
		break;
	case eType_Item_Score:
		if (Base::CollisionRect(this, b)) {
			GameData::s_score += 1;
			b->SetKill();
		}
		break;
	case eType_Item_LifeUp:
		if (Base::CollisionRect(this, b)) {
			m_hp += 30;
			if (m_hp >= m_hpmax) {
				m_hp = m_hpmax;
			}
			b->SetKill();
		}
		break;
		//Field�^�փL���X�g�A�^�ϊ��ł�����
		/*
		if (Field* f = dynamic_cast<Field*>(b)) {
			//�n�ʂ�艺�ɂ�������
			if (m_pos.y > f->GetGroundY()) {
				//�n�ʂ̍����ɖ߂�
				m_pos.y = f->GetGroundY();
				//�������x���Z�b�g
				m_vec.y = 0;
				//�ڒn�t���OON
				m_is_ground = true;

			}
		}
		break;
		*/
	case eType_Enemy_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s) && !m_is_inv) {
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;

	case eType_Enemy:
		if (Enemy* e = dynamic_cast<Enemy*>(b)) {
			if (m_damage_no != e->GetAttackNo() && Base::CollisionRect(this, e) && !m_is_inv) {
				m_damage_no = e->GetAttackNo();
				m_pow = e->GetPow();
				m_hp -= m_pow;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;

				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
	case eType_Bullet:
		if (EnemyBullet* r = dynamic_cast<EnemyBullet*>(b)) {
			if (m_damage_no != r->GetAttackNo() && Base::CollisionRect(this, r)) {
				m_damage_no = r->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0){
				m_pos.x = m_pos_old.x;
			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
				m_airjump = false;
				//��l+�␳�l
				//m_scroll.x = m_pos.x - 1280 / 2 + sc_ver.x;
				//m_scroll.y = m_pos.y - 500 + sc_ver.y;
				
			}
		}
		break;
	
	}
}