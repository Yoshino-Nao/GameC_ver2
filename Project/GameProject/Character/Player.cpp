#include "../Base/Base.h"
#include "../Game/AnimData.h"
#include "../Attack/Slash.h"
#include "../Game/Effect.h"
#include "../Game/Game.h"
#include "../Game/Effect_Ring.h" 
#include "../Map/Map.h"
#include "../Map/AreaChange.h"
#include "../Game/GameData.h"
#include "../Attack/EnemyBullet.h"
#include "../Attack/Player_Bullet1.h"
#include "../Item/Item.h"
#include "../Title/Title.h"
#include "../Item/Item.h"
#include "../UI/Menu.h"
#include "../Gimmick/Door.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

void Player::StateIdle()
{
	
	
	Move();

	if (PUSH(CInput::eButton3)) {
		m_state = eState_GunDraw;
		m_attack_no++;
	}
	if (PUSH(CInput::eButton1)) {
		m_state = eState_Attack1;
		m_attack_no++;
	}
}
#pragma region Attack
void Player::StateAttack1()
{
	m_img.ChangeAnimation(12, false, 0, true);
	if (m_img.GetIndex() == 3) {
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos, m_pos.y - 50), 64, m_flip, eType_Player_Attack, m_attack_no));
		
	}
	if (m_img.CheckAnimationEnd() && HOLD(CInput::eButton1)) {
		m_state = eState_Attack2;
	}
	else if (m_img.CheckAnimationEnd() && HOLD(CInput::eRight) || HOLD(CInput::eLeft)) {
		m_state = eState_Idle;
	}
}

void Player::StateAttack2()
{
	m_img.ChangeAnimation(13, false, 0, true);
	if (m_img.GetIndex() == 4) {
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos, m_pos.y - 50), 64, m_flip, eType_Player_Attack, m_attack_no));
		Base::Add(new Slash(CVector2D(m_pos.x, m_pos.y - 100), 32, m_flip, eType_Player_Attack, m_attack_no));
	}
	if (m_img.CheckAnimationEnd() && HOLD(CInput::eButton1)) {
		m_state = eState_Attack3;
	}
	else if (m_img.CheckAnimationEnd() && HOLD(CInput::eRight) || HOLD(CInput::eLeft)) {
		m_state = eState_Idle;
	}
}

void Player::StateAttack3()
{
	m_img.ChangeAnimation(14, false, 0, true);
	if (m_img.GetIndex() == 4) {
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos + (m_atkpos / 2), m_pos.y - 30), 48, m_flip, eType_Player_Attack, m_attack_no));
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos + (m_atkpos / 2), m_pos.y - 127), 48, m_flip, eType_Player_Attack, m_attack_no));
	}
	if (m_img.GetIndex() == 5) {
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos + m_atkpos , m_pos.y - 20), 32, m_flip, eType_Player_Attack, m_attack_no));
	}
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
#pragma endregion
#pragma region GunAttack
void Player::StateGunDraw()
{
	
	m_img.ChangeAnimation(15, false);
	CVector2D mouse_pos = CInput::GetMousePoint();
	CVector2D r = CInput::GetRStick(0);
	DrawLine(CVector2D(m_pos.x, m_pos.y - 50), mouse_pos);
	if (m_img.CheckAnimationEnd() && PUSH(CInput::eRight) || PUSH(CInput::eLeft)) {
		m_state = eState_Idle;
	}
	else if (m_img.CheckAnimationEnd() && HOLD(CInput::eButton3)) {
		m_state = eState_Shooting;
		rate = 0;
		//Base::Add(new Player_Bullet1(CVector2D(m_pos.x, m_pos.y - 50), m_flip, m_attack_no));
	}
}
void Player::StateShooting()
{	
	CVector2D mouse_pos = CInput::GetMousePoint();
	CVector2D r = CInput::GetRStick(0);
	CVector2D diff = mouse_pos - GetScreenPos(CVector2D(m_pos.x, m_pos.y - 50));
	DrawLine(CVector2D(m_pos.x, m_pos.y - 50), mouse_pos);
	if (rate <= 0) {
		Base::Add(new Player_Bullet1(CVector2D(m_pos.x + m_atkpos, m_pos.y - 76), atan2f(diff.y, diff.x), m_flip, m_attack_no));
		m_img.ChangeAnimation(17, true);
		rate = 20;
	}
	rate--;

	
	if (FREE(CInput::eButton3)) {
		m_state = eState_GunDraw;
	}
}
#pragma endregion
#pragma region Damage
void Player::StateDamage()
{
	m_img.ChangeAnimation(8, false);
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
	m_img.ChangeAnimation(11, false);
	if (m_img.CheckAnimationEnd()) 
	{
		m_kill = true;
	}
}
#pragma endregion

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//�摜����
	m_img = COPY_RESOURCE("Player", CImage);
	m_img.SetSize(448, 448);
	//���S�ʒu�ݒ�
	m_img.SetCenter(224, 412);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	
	//�����蔻��
	m_rect = CRect(-20, -104, 20, 0);
	//��ԕϐ�
	m_state = eState_Idle;
	//X�ő呬�x
	move_xspeed_max = 10;
	//�����x
	move_xspeed_add = 1.0f;
	//�W�����v��
	move_yspeed_max = 18;
	//�W�����v��
	jump_pow = 9;
	//�����x
	//move_yspeed_add = 0.5f;
	//���C
	friction = 0.9f;

	//���]�t���O
	m_flip = flip;
	//���n�t���O
	m_is_ground = true;
	//���n���[�V�����t���O
	m_is_land = false;
	//�Q�i�W�����v�t���O
	m_airjump = false;
	//�W�����vindex�擾
	jumpindex = 0;
	//���G�t���O
	m_is_inv = false;
	//�G���A�`�F���W�t���O
	m_enable_area_change = true;
	//�G���A�`�F���W�I�u�W�F�N�g�ɐG��Ă���t���O
	m_hit_area_change = false;

	//Attack��State
	//Pstate = 0;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
    m_damage_no = -1;
	//�U�������␳�l
	m_atkpos = 60.0f;
	
	//���˃��[�g
	rate = 20;
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
	////�X�N���[����ԗ�
	CVector2D sc_vec(0, 0);
	
	
	/*
	m_img.SetSize(224 / 2, 224 / 2);
	m_img.SetCenter(112 / 2, 192 / 2);
	m_rect = CRect(-28 / 2, -124 / 2, 28 / 2, 0);*/
}

void Player::Move()
{
	//�ړ��t���O
	bool move_flag = false;
	//���ړ�
	if (HOLD(CInput::eLeft)) {
		vec.x -= move_xspeed_add;
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		vec.x += move_xspeed_add;
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}
	//�W�����v
	if (m_is_ground && PUSH(CInput::eButton2)) {
		vec.y = jump_pow;
		m_vec.y = -move_yspeed_max;
		m_is_ground = false;
		m_airjump = true;
	}
	vec.x = min(max(vec.x, -move_xspeed_max), move_xspeed_max);
	/*
	if (vec.x < -move_xspeed_max) {
		vec.x = -move_xspeed_max;
	}
	if (vec.x > move_xspeed_max) {
		vec.x = move_xspeed_max;
	}*/
	
	//m_pos.y += vec.y;
	//�W�����v���Ȃ�
	if (!m_is_ground) {
		if (m_vec.y < 0) {
			//�㏸�A�j���[�V����
			m_img.ChangeAnimation(5, false);
		}
		else
		{
			//���~�A�j���[�V����
			m_img.ChangeAnimation(6, false);
			m_is_land = true;
		}
		//�Q�i�W�����v
		if (m_airjump && m_img.GetIndex() >= 1 && PUSH(CInput::eButton2)) {
			m_vec.y = (move_yspeed_max * -0.7f);
			m_is_ground = false;
			m_airjump = false;
		}
	}
	//�ړ����Ȃ�
	else {
		if (move_flag) {
			if (m_is_land) {
				m_img.ChangeAnimation(7, false);
				m_is_land = false;
				if (m_img.CheckAnimationEnd()) {
					m_img.ChangeAnimation(2);
				}
			}
			else {
				//����A�j���[�V����
				m_img.ChangeAnimation(2);
			}
		}
		else {
			if (m_is_land) {
				m_img.ChangeAnimation(7, false);
				m_airjump = true;
				m_is_land = false; 
				if (m_img.CheckAnimationEnd()) {
					m_img.ChangeAnimation(0);
				}

			}
			else {
				
				//�ҋ@�A�j���[�V����
				m_img.ChangeAnimation(0);
			}
		}
	}
}
void Player::LifeUp(int v)
{
	m_hp += v;
	if (m_hp >= m_hpmax) {
		m_hp = m_hpmax;
	}
}

void Player::Update() {
	m_img.SetColor(1, 1, 1, 1);
	Base* b = Base::FindObject(eType_Menu);
	if (!b) {
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
			case eState_Attack1:
				StateAttack1();
				break;
			case eState_Attack2:
				StateAttack2();
				break;
			case eState_Attack3:
				StateAttack3();
				break;
			case eState_GunDraw:
				StateGunDraw();
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
			//�X�N���[���␳
			//�ڕW�l
			CVector2D v3(0, 0);
			//�����Ă����痎������Ԃֈڍs
			if (m_is_ground && m_vec.y > GRAVITY * 4) {
				m_is_ground = false;
				m_airjump = true;
			}

			if (m_vec.y > GRAVITY * 4 || m_vec.y < -1 || HOLD(CInput::eDown))
			{
				v3.y = 300;
			}
			else if (HOLD(CInput::eUp)) {
				v3.y = -300;
			}
			else
			{
				v3.y = 0;
			}

			m_flip ? v3.x = -300 : v3.x = +300;
			m_flip ? m_atkpos = -60.0f : m_atkpos = 60.0f;
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
			if (m_is_ground) {
				vec.x *= friction;
			}

			//�d�͂ɂ�闎��
			m_vec.y += GRAVITY;
			//�A�j���[�V�����X�V
			m_img.UpdateAnimation();
			m_pos.x += vec.x;
			m_pos.y += m_vec.y;
			stpdtime = 0;


			if (!m_enable_area_change && !m_hit_area_change)
				m_enable_area_change = true;
			m_hit_area_change = false;
		}
	}
	Menu* m = dynamic_cast<Menu*>(b);
	if (PUSH(CInput::eButton5)) {
		if (m) {
			m->SetKill();
		}
		else {
			Base::Add(new Menu());
		}
	}
	if (bool b=m->LifeUp()) {
		LifeUp(10);
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
			LifeUp(30);
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
				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
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
				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			CVector2D pos;
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect, &pos);
			if (t != NULL_TIP){
				m_pos.x = pos.x;
			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect,&pos);
			if (t != NULL_TIP) {
				m_pos.y = pos.y;
				m_vec.y = 0;
				m_is_ground = true;
				//m_is_land = false;
				//m_airjump = false;
				
				//��l+�␳�l
				//m_scroll.x = m_pos.x - 1280 / 2 + sc_ver.x;
				//m_scroll.y = m_pos.y - 500 + sc_ver.y;
				
			}
		}
		break;
	case eType_AreaChange:
		if (Base::CollisionRect(this, b)) {
			//�G���A�`�F���W�ɐG��Ă���
			m_hit_area_change = true;
			//�G���A�`�F���W�\�Ȃ�
			if (m_enable_area_change) {
				if (AreaChange* a = dynamic_cast<AreaChange*>(b)) {
					//�}�b�v�ƃG���A�`�F���W�I�u�W�F�N�g���폜
					KillByType(eType_Field);
					KillByType(eType_AreaChange);
					KillByType(eType_MiniMapBack);
					KillByType(eType_MiniMapFront); 
					KillByType(eType_Enemy);
					//���̃}�b�v�𐶐�
					Base::Add(new Map(a->m_nextArea, a->m_nextplayerpos));
					//�G���A�`�F���W�ꎞ�s����
					m_enable_area_change = false;
				}
			}
		}

		break;
	case eType_Door:
		if (Base::CollisionObject(CVector2D(m_pos.x, m_pos_old.y), m_rect, b->m_pos, b->m_rect)) {
			if (Door* door = dynamic_cast<Door*>(b)) {
				int k = door->GetKey();
				if (k == 0) {
					door->SetKill();
				}
				else {
					m_pos.x = m_pos_old.x;
				}
			}
		}
		if (Base::CollisionObject(CVector2D(m_pos_old.x, m_pos.y), m_rect, b->m_pos, b->m_rect)) {
			
			m_pos.y = m_pos_old.y;
			m_vec.y = 0;
			m_is_ground = true;
			//m_is_land = false;
			//m_airjump = false;
		}
		break;
	}
}

