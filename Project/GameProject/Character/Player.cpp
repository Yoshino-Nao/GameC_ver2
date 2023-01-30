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
#include "../UI/UI.h"
#include "../UI/Menu.h"
#include "../UI/Gauge.h"
#include "../Gimmick/Door.h"
#include "../Gimmick/BreakWall.h"
#include "../Gimmick/Event.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

void Player::StateIdle()
{
	Move();
	if (PUSH(CInput::eButton1) && m_getSword) {
		m_atk_yoyaku = false;
		m_attack_no++;
		m_state = eState_Attack1;
	}
	if (PUSH(CInput::eButton6) && m_getGun) {
		m_state = eState_GunDraw;
		m_attack_no++;
	}
}
#pragma region Attack
void Player::StateAttack1()
{
	m_img.ChangeAnimation(12, false, 0, true);
	if (m_img.GetIndex() == 3) {
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos, m_pos.y - 50), 64,
			m_flip, eType_Player_Attack, m_attack_no, m_attack_pow));
	}
	if (m_img.GetIndex() >= 3 && HOLD(CInput::eButton1)) {
		m_atk_yoyaku = true;
	}
	if (m_img.CheckAnimationEnd() && m_atk_yoyaku) {
		m_attack_no++;
		m_atk_yoyaku = false;
		m_state = eState_Attack2;
	}
	else if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Player::StateAttack2()
{
	m_img.ChangeAnimation(13, false, 0, true);
	if (m_img.GetIndex() == 4) {
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos, m_pos.y - 50), 64, 
			m_flip, eType_Player_Attack, m_attack_no, m_attack_pow));
		Base::Add(new Slash(CVector2D(m_pos.x, m_pos.y - 100), 32, 
			m_flip, eType_Player_Attack, m_attack_no, m_attack_pow));
	}
	if (m_img.GetIndex() >= 4 && HOLD(CInput::eButton1)) {
		m_atk_yoyaku = true;
	}
	if (m_img.CheckAnimationEnd() && m_atk_yoyaku) {
		m_atk_yoyaku = false;
		m_attack_no++;
		m_state = eState_Attack3;
	}
	else if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}

void Player::StateAttack3()
{
	m_img.ChangeAnimation(14, false, 0, true);
	if (m_img.GetIndex() == 4) {
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos + (m_atkpos / 2), m_pos.y - 30), 48, 
			m_flip, eType_Player_Attack, m_attack_no, m_attack_pow));
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos + (m_atkpos / 2), m_pos.y - 127), 48, 
			m_flip, eType_Player_Attack, m_attack_no, m_attack_pow));
	}
	if (m_img.GetIndex() == 5) {
		Base::Add(new Slash(CVector2D(m_pos.x + m_atkpos + m_atkpos + m_atkpos, m_pos.y - 20), 40,
			m_flip, eType_Player_Attack, m_attack_no, m_attack_pow));
		
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
	CVector2D HandPos(m_pos.x + (r.x * m_handpos), m_pos.y - 70 + (r.y * m_handpos));
	r = r * 1000;
	//
	DrawLine(HandPos, HandPos + r , 1, 0, 0);

	//FONT_T()->Draw(100, 100, 1, 1, 1, "%.4f%.4f", r.x, r.y);
	
	if (m_img.CheckAnimationEnd() && 
		//PUSH(CInput::eRight) || PUSH(CInput::eLeft) || 
		l.x >= 0.8f || l.x <= -0.8f) {
		m_state = eState_Idle;
	}
	else if (m_img.CheckAnimationEnd() && HOLD(CInput::eButton6)) {
		m_state = eState_Shooting;
		rate = 0;
		//Base::Add(new Player_Bullet1(CVector2D(m_pos.x, m_pos.y - 50), m_flip, m_attack_no));
	}
}
void Player::StateShooting()
{	
	CVector2D mouse_pos = CInput::GetMousePoint();
	CVector2D HandPos(m_pos.x + (r.x * m_handpos), m_pos.y - 70 + (r.y * m_handpos));
	r = r * 1000;
	DrawLine(HandPos, HandPos + r, 1, 0, 0);
	CVector2D Front;
	m_flip ? Front = CVector2D::left : Front = CVector2D::right;
	
	float dot = CVector2D::Dot(Front.GetNormalize(), r.GetNormalize());
	//FONT_T()->Draw(100, 100, 1, 1, 1, "%.4f%.4f", r.x, r.y);
	//FONT_T()->Draw(100, 100, 1, 1, 1, "%.4f%.4f", r.x, r.y);
	//����
	if (dot > cosf(DtoR(20.0f))) {
		//DrawLine(HandPos, HandPos + r, 1, 0, 0);
		m_img.ChangeAnimation(17, true);
	}//�΂ߏ�
	else if (dot > cosf(DtoR(70.0f)) && r.y < 0) {
		//DrawLine(HandPos, HandPos + r, 0, 1, 0);
		m_img.ChangeAnimation(18, true);
	}//�΂߉�
	else if (dot > cosf(DtoR(70.0f)) && r.y > 0) {
		//DrawLine(HandPos, HandPos + r, 0, 0, 1);
		m_img.ChangeAnimation(16, true);
	}//�^��
	else if (dot > cosf(DtoR(115.0f)) && r.y < 0) {
		//DrawLine(HandPos, HandPos + r, 1, 1, 1);
		m_img.ChangeAnimation(19, true);
		if (rate <= 0) {
			Base::Add(new Player_Bullet1(CVector2D(HandPos.x, HandPos.y)
				, atan2f(r.y, r.x), m_flip, m_attack_no, m_attack_pow * 0.5f));
			
			rate = 20;
			m_attack_no++;
		}
	}
	else {
		m_img.ChangeAnimation(15, false);
	}
	if (rate <= 0 && dot > cosf(DtoR(70.0f))) {
		Base::Add(new Player_Bullet1(HandPos
			, atan2f(r.y, r.x), m_flip, m_attack_no, m_attack_pow * 0.5f));
		rate = 20;
		m_attack_no++;
	}
	rate--;

	
	if (FREE(CInput::eButton6)) {
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
	/*if (m_flip) {
		m_pos.x += 5;
	}
	else {
		m_pos.x -= 5;
	}*/
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

Player::~Player()
{

	////SetKill();
	//Base::KillAll();
	////�^�C�g���V�[����
	//Base::Add(new Title());

}

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//�摜����
	m_img = COPY_RESOURCE("Player", CImage);
	//�摜�T�C�Y
	m_img.SetSize(448, 448);
	//���S�ʒu�ݒ�
	m_img.SetCenter(224, 412);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//�����蔻��
	m_rect = CRect(-20, -104, 20, 0);
#pragma region �ϐ�

#pragma region �ړ��֌W
	//X�ő呬�x
	move_xspeed_max = 10;
	//�����x
	move_xspeed_add = 1.0f;
	//�W�����v��
	move_yspeed_max = 20;
	//�W�����v���͎���
	jump_pow = 0;
	//���C
	friction = 0.9f;
	//���ݍ��x �ߋ����x
	m_groundpos_old = m_groundpos = m_pos.y;
	//���x�� ���x���v�Z�p
	m_groundpos_diff = m_groundpos_diff2 = 0;
	//���]�t���O
	m_flip = flip;
	//���n����p�t���O
	m_is_ground = true;
	//���n���[�V�����t���O
	m_is_land = false;
	m_land2 = false;
	//�Q�i�W�����v�t���O
	m_airjump = false;
#pragma endregion

#pragma region �U���֌W
	//�U���\��t���O
	m_atk_yoyaku = false;
	//�U����
	m_attack_pow = 50;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
    m_damage_no = -1;
	//�U�������␳�l
	m_atkpos = 60.0f;
	//��̈ʒu
	m_handpos = 30;
	//���˃��[�g
	rate = 20;
#pragma endregion

#pragma region �v���C���[�̏��
	//��ԕϐ�
	m_state = eState_Idle;
	//���G�t���O
	m_is_inv = false;
	//���G����
	invtime = 0;
	//��~����
	stpdtime = 0;
	//�G���A�`�F���W�t���O
	m_enable_area_change = true;
	//�G���A�`�F���W�I�u�W�F�N�g�ɐG��Ă���t���O
	m_hit_area_change = false;
	//�ő�HP   HP
	m_hpmax = 120;
	m_hp = 120;
	//�Q�i�W�����v�擾
	//���擾
	//�e�擾
	m_getairjump = false;
	m_getSword = false;
	m_getGun = false;
	//�f�o�b�O�p
	//m_getairjump = m_getSword = m_getGun = true;
#pragma endregion
	//�X�e�B�b�N
	r = CVector2D(0, 0);
	l = CVector2D(0, 0);
	////�X�N���[����ԗp
	sc_vec = CVector2D(0, 0);
	//
	m_menukill = false;
#pragma endregion

}

void Player::Move()
{
	//�ړ��t���O
	bool move_flag = false;
	bool walk_flag = false;
	
	//������
	if (l.x <= -0.8f) {
		move_xspeed_max = 10;
		m_vec.x -= move_xspeed_add * abs(l.x);
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}
	else if (l.x > -0.8f && l.x < -0.2f) {
		move_xspeed_max = 3.0f * abs(l.x) + 3;
		//m_is_ground ? move_xspeed_max = 5 : move_xspeed_max = 5;
		m_vec.x -= move_xspeed_add * abs(l.x) * 0.7f;
		//���]�t���O
		m_flip = true;
		walk_flag = true;
	}
	//�E����
	if (l.x >= 0.8f) {
		move_xspeed_max = 10;
		m_vec.x += move_xspeed_add * abs(l.x);
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}
	else if (l.x < 0.8f && l.x > 0.2f) {
		move_xspeed_max = 3.0f * abs(l.x) + 3;
		//m_is_ground ? move_xspeed_max = 5 : move_xspeed_max = 5;
		
		m_vec.x += move_xspeed_add * abs(l.x) * 0.7f;

		//���]�t���O
		m_flip = false;
		walk_flag = true;
	}
	m_vec.x = min(max(m_vec.x, -move_xspeed_max), move_xspeed_max);
	//�W�����v
	if (m_is_ground && HOLD(CInput::eButton2)) {
		jump_pow++;
	}
	//���x���𑪒�
	m_groundpos_diff = m_groundpos - m_groundpos_old;

	//FONT_T()->Draw(100, 100, 1, 1, 1, "vec.y:%f", m_vec.y);
	//FONT_T()->Draw(100, 200, 1, 1, 1, "l.x%f", l.x);
	//FONT_T()->Draw(100, 300, 1, 1, 1, "%f", m_groundpos_diff2);
	//FONT_T()->Draw(100, 300, 1, 1, 1, "m_scroll.y%f", m_scroll.y);
	//�W�����v���Ȃ�
	if (!m_is_ground) {
		if (m_vec.y < 0) {
			//�㏸�A�j���[�V����
			m_img.ChangeAnimation(5, false);
			if (m_vec.y <= -10) {
				//�W�����v�̋��������������ɂ�����
				m_vec.y += 0.4f;		
			}
			//�A�j���[�V�����̂P���ڂ̎��ɍ��x����
			if (m_img.GetIndex() == 0) {
				m_groundpos_old = m_groundpos;
			}
		}
		else
		{
			//���~�A�j���[�V����
			m_img.ChangeAnimation(6, false);
			
			//���x�̍���300�ȉ��Ȃ璅�n���[�V�����t���O�𗧂����Ȃ�
			if (m_groundpos_diff > 300) {
				m_is_land = true;
				m_groundpos_diff2 = min(m_groundpos_diff, 1200);
			}
			//�A�j���[�V�����̂P���ڂ̎��ɍ��x����
			if (m_img.GetIndex() == 0) {
				m_groundpos_diff2 = 0;
				m_groundpos_old = m_groundpos;
			}
			//���ݍ��x�𑪒�
			m_groundpos = m_pos.y;
		}
		//�Q�i�W�����v
		if (m_airjump && m_img.GetIndex() >= 1 && PUSH(CInput::eButton2) && m_getairjump) {
			m_img.ChangeAnimation(5, false);

			m_vec.y = (move_yspeed_max * -0.7f);
			m_is_ground = false;
			m_airjump = false;
			Base::Add(new Effect("Effect_Ring_yoko", CVector2D(m_pos.x, m_pos.y), m_flip, 90, 30));
		}
		//�Q�i�W�����v���A���x�����Z�b�g
		if (!m_airjump && m_img.GetIndex() >= 4) {
			if (HOLD(CInput::eLeft)) {
				m_vec.x = -move_xspeed_max * 0.5f;
			}
			else if (HOLD(CInput::eRight)) {
				m_vec.x = move_xspeed_max * 0.5f;
			}
		}
	}
	else {
		m_airjump = true;
		//��W�����v
		if (HOLD(CInput::eButton2) && jump_pow >= 6) {
			m_vec.y = -move_yspeed_max;
			m_is_ground = false;
			jump_pow = 0;	
		}//���W�����v
		if (FREE(CInput::eButton2) && jump_pow < 6 && jump_pow > 0) {
			float ySpeed = 0;
			if (jump_pow <= 5) {
				ySpeed = 10 + jump_pow;
			}
			//m_vec.y = -move_yspeed_max * 0.5f;
			m_vec.y = -ySpeed;
			m_is_ground = false;
			jump_pow = 0;
		}
		if (!m_is_land) {
			//����A�j���[�V����
			if (move_flag) {
				m_img.ChangeAnimation(2);
			}//�����A�j���[�V����
			else if (walk_flag) {
				m_img.ChangeAnimation(1);
			}//�ҋ@�A�j���[�V����
			else {
				m_img.ChangeAnimation(0);
			}
		}
		else
		{	//���n���[�V����
			m_img.ChangeAnimation(7, false);
			if (m_img.CheckAnimationEnd()) {
				//���n���[�V�������I���܂ł̃J�E���g
				//m_vec.x = m_vec.x * 0.8f;
				m_vec.x = 0;
				m_groundpos_diff2 -= 40;
				if (m_groundpos_diff2 <= 0) {
					m_is_land = false;
				}
			}
		}
	}
#pragma region �X�N���[���␳
	//�ڕW�l
	CVector2D v3(0, 0);
	//�����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4) {
		m_is_ground = false;
		//m_airjump = true;
	}
	
	if (m_vec.y > GRAVITY * 4 || m_vec.y < -1)
	{
		//�������A���ɃX�N���[��;
		v3.y = min(m_vec.y * 10 + 100, 500);
	}
	else if (r.y > 0.8) {
		v3.y = 300;
	}
	else if (r.y < -0.8) {
		v3.y = -300;
	}
	else
	{
		v3.y = 0;
	}
	//FONT_T()->Draw(100, 100, 1, 1, 1, "m_vec.y:%f", m_vec.y);
	//�J�����␳
	//�~�j�}�b�v�ƃA�N�V�����̂��₷���̌��ˍ������l���Ĉ�UOFF
	m_flip ? v3.x = -200 : v3.x = +200;
	m_flip ? m_atkpos = -60.0f : m_atkpos = 60.0f;
	CVector2D v2 = v3 - sc_vec;
	//�X�N���[�������x
	sc_vec += v2 * 0.05;
#pragma endregion
}

void Player::GetItem(int i)
{

}
void Player::UseItem(int n)
{
	switch (n)
	{
	case 0:
		LifeUp(30);
		break;
	}
}
void Player::LifeUp(int v)
{
	m_hp += v;
	if (m_hp >= m_hpmax) {
		m_hp = m_hpmax;
	}
}

void Player::KnockBack(CVector2D m_epos,int pow)
{
	float ratio = (float)pow / (float)m_hpmax;
	CVector2D e_pos = (m_pos - m_epos) * ratio;
	m_vec = e_pos;
}

void Player::Update() {
	m_img.SetColor(1, 1, 1, 1);
	//�X�e�B�b�N���b�h�]�[��
	if (abs(r.x) <= 0.2f) {
		r.x = 0.0f;
	}
	if (abs(r.y) <= 0.2f) {
		r.y = 0.0f;
	}
	if (abs(l.x) <= 0.2f) {
		l.x = 0.0f;
	}
	if (abs(l.y) <= 0.2f) {
		l.y = 0.0f;
	}
	
	Base* b = Base::FindObject(eType_Menu);
#pragma region ���j���[���J����Ă��Ȃ���
	if (!b) {
		r = CInput::GetRStick(0);
		l = CInput::GetLStick(0);
		//�����L�[��L,R�𑀍�
		if (HOLD(CInput::eLeft) && HOLD(CInput::eButton6)) {
			r.x = -1;
		}else if (HOLD(CInput::eLeft)) {
			l.x = -1;
		}
		if (HOLD(CInput::eRight) && HOLD(CInput::eButton6)) {
			r.x = 1;
		}else if (HOLD(CInput::eRight)) {
			l.x = 1;
		}
		/*if (HOLD(CInput::eLeft)) {
			l.x = -1;
		}
		else if (HOLD(CInput::eRight)) {
			l.x = 1;
		}
		else if (HOLD(CInput::eLeft) && HOLD(CInput::eRight)) {
			l.x = 0;
		}*/



		if (HOLD(CInput::eUp) && HOLD(CInput::eButton6)) {
			r.y = -1;
		}else if (HOLD(CInput::eUp)) {
			l.y = -1;
		}
		if (HOLD(CInput::eDown) && HOLD(CInput::eButton6)) {
			r.y = 1;
		}else if (HOLD(CInput::eDown)) {
			l.y = 1;
		}
		//std::cout << "Player" << std::endl;
		m_pos_old = m_pos;
		Base* a = Base::FindObject(eType_Enemy);
		Enemy* e = dynamic_cast<Enemy*>(a);
		if (a) {
			stpdtime = e->GetStopTime();
		}
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
			//CVector2D v3(0, 0);
			////�����Ă����痎������Ԃֈڍs
			//if (m_is_ground && m_vec.y > GRAVITY * 4) {
			//	m_is_ground = false;
			//	//m_airjump = true;
			//}

			//if (m_vec.y > GRAVITY * 4 || m_vec.y < -1 || HOLD(CInput::eDown))
			//{
			//	//v3.y = 300;
			//	v3.y = m_vec.y * 10 + 100;
			//}
			//else if (HOLD(CInput::eUp)) {
			//	v3.y = -300;
			//}
			//else
			//{
			//	v3.y = 0;
			//}
			////FONT_T()->Draw(100, 100, 1, 1, 1, "m_vec.y:%f", m_vec.y);
			////�J�����␳
			////�~�j�}�b�v�ƃA�N�V�����̂��₷���̌��ˍ������l���Ĉ�UOFF
			////m_flip ? v3.x = -300 : v3.x = +300;
			//m_flip ? m_atkpos = -60.0f : m_atkpos = 60.0f;
			//CVector2D v2 = v3 - sc_vec;
			////�X�N���[�������x
			//sc_vec += v2 * 0.05;
			////��l+�␳�l
			m_scroll.x = m_pos.x - CCamera::GetCurrent()->GetWhidth()/2 + sc_vec.x;
			m_scroll.y = m_pos.y - CCamera::GetCurrent()->GetHeight() / 1.4f + sc_vec.y;
			//���G����
			if (m_is_inv) {
				invtime--;
				m_img.SetColor(1, 1, 1, 0.5);
				if (invtime <= 0) {
					m_is_inv = false;
					invtime = 0;
				}
			}
			
			m_vec.x *= friction;
			

			//�d�͂ɂ�闎��
			m_vec.y += GRAVITY;
			//�A�j���[�V�����X�V
			m_img.UpdateAnimation();
			/*m_pos.x += vec.x;
			m_pos.y += m_vec.y;*/
			m_pos += m_vec;
			stpdtime = 0;


			if (!m_enable_area_change && !m_hit_area_change) {
				m_enable_area_change = true;
				m_groundpos = m_pos.y;
			}
			m_hit_area_change = false;
		}

	}
#pragma endregion
	Menu* m = dynamic_cast<Menu*>(b);
	if (PUSH(CInput::eButton10)) {
		if (m) {
			m->SetKill();
		}
		else {
			Base::Add(new Menu());
		}
	}
	else if (PUSH(CInput::eButton10) && m) {
		m_menukill = true;
	}
	if (m_menukill && FREE(CInput::eButton10) && m) {
		m->SetKill();
		m_menukill = false;
	}
	if (b) {
		if (m->UseItemflag()) {
			//int item_num = m->UseItemNum();
			if (GameData::s_itemlist[m->UseItemNum()] > 0) {
				UseItem(m->UseItemNum());
				GameData::s_itemlist[m->UseItemNum()] -= 1;
			}
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
#pragma region �A�C�e���R���W����
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			b->SetKill();
		}
		break;
	case eType_Item:
		if (Base::CollisionRect(this, b)) {
			if (Item* i = dynamic_cast<Item*>(b)) {
				int id = i->GetItemId();
				switch (id)
				{
				case eType_Item_Score:
					//GameData::s_score += 1;
					b->SetKill();
					break;
				case eType_Item_LifeUp:
					//LifeUp(30);
					GameData::s_itemlist[0] += 1;
					//m_ItemList[0] += 1;
					b->SetKill();
					break;
				case eType_Item_AirJump:
					m_getairjump = true;
					b->SetKill();
					break;
				case eType_Item_Sword:
					m_getSword = true;
					b->SetKill();
					break;
				case eType_Item_Gun:
					m_getGun = true;
					b->SetKill();
					break;
				case eType_Item_Kay1:
					GameData::s_key += 1;
					b->SetKill();
					break;
				case eType_Item_Kay2:
					GameData::s_key2 += 1;
					b->SetKill();
					break;
				case eType_Item_Kay3:
					GameData::s_key3 += 1;
					b->SetKill();
					break;
				}
			}
		}
		break;
#pragma endregion
	/*case eType_Item_Score:
		if (Base::CollisionRect(this, b)) {
			GameData::s_score += 1;
			b->SetKill();
		}
		break;
	case eType_Item_LifeUp:
		if (Base::CollisionRect(this, b)) {
			LifeUp(30);
			b->SetKill();
		}*/
#pragma region �U���R���W����
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
				int get_pow = e->GetPow();
				m_hp -= get_pow;
				KnockBack(e->m_pos, get_pow);

				
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
#pragma endregion
#pragma region �}�b�v�I�u�W�F�N�g�R���W����
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			CVector2D pos;
			
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect, &pos);
			if (t == 1) {
				m_pos.x = pos.x;
			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect, &pos);
			if (t == 1) {
				//FONT_T()->Draw(100, 200, 1, 1, 1, "pos.y:%f", pos.y);
				//�����Ԃ������̔���
				if (m_pos.y >= pos.y) {
					m_is_ground = true;
				}
				/*else {
					pos.y = m_pos.y;
				}*/
				m_pos.y = pos.y;
				m_vec.y = 0;/*
				FONT_T()->Draw(100, 100, 1, 1, 1, "m_pos.y:%f", m_pos.y);
				FONT_T()->Draw(100, 200, 1, 1, 1, "pos.y:%f", pos.y);*/
				//m_is_land = false;
				//m_airjump = false;
				
				//��l+�␳�l
				//m_scroll.x = m_pos.x - 1280 / 2 + sc_ver.x;
				//m_scroll.y = m_pos.y - 500 + sc_ver.y;

			}//���蔲�����̔���
			else if (t == 3) {//�W�����v�����A�����͒��͂��蔲����
				if (m_pos.y >= pos.y && m_vec.y >= 0 && l.y != 1) {
					/*FONT_T()->Draw(100, 100, 1, 1, 1, "m_pos.y:%f", m_pos.y);
					FONT_T()->Draw(100, 200, 1, 1, 1, "pos.y:%f", pos.y);*/
					m_vec.y = 0;
					m_is_ground = true;
					m_pos.y = pos.y;
				}
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
					KillByType(eType_Event);
					KillByType(eType_BreakWall);
					KillByType(eType_Door);
					KillByType(eType_MiniMapBack);
					KillByType(eType_MiniMapFront); 
					KillByType(eType_Enemy);
					KillByType(eType_Item);
					m_groundpos_diff = m_groundpos_diff2 = 0;
					//���̃}�b�v�𐶐�
					Base::Add(new Map(a->m_nextArea, a->m_nextplayerpos));
					//�G���A�`�F���W�ꎞ�s����
					m_enable_area_change = false;
				}
			}
		}

		break;
	case eType_Event:
		if (Base::CollisionRect(this, b)) {
			Base* b = Base::FindObject(eType_Event);
			Event* e = dynamic_cast<Event*>(b);
			int eventnum = e->GetEventNum();
			switch (eventnum)
			{
			case 0:
				auto p = Base::FindObjects(eType_BreakWall);
				for (auto& b : p) {
					BreakWall* h = dynamic_cast<BreakWall*>(b);
					Base::Add(new Effect("Effect_Smoke", h->m_pos, m_flip, 128, 128));
					h->SetKill();
				}
				e->SetKill();
				break;
			}
		}
		break;
	case eType_BreakWall:
		if (Base::CollisionObject(CVector2D(m_pos.x, m_pos_old.y), m_rect, b->m_pos, b->m_rect)) {
			m_pos.x = m_pos_old.x;
		}
		if (Base::CollisionObject(CVector2D(m_pos_old.x, m_pos.y), m_rect, b->m_pos, b->m_rect)) {
			m_pos.y = m_pos_old.y;
			m_vec.y = 0;
			m_is_ground = true;
			//m_is_land = false;
			//m_airjump = false;
		}
		break;
	case eType_Door:
		if (Base::CollisionObject(CVector2D(m_pos.x, m_pos_old.y), m_rect, b->m_pos, b->m_rect)) {
			if (Door* door = dynamic_cast<Door*>(b)) {
				int k = door->GetKey();
				m_pos.x = m_pos_old.x;
				switch (k)
				{
				case 0:
					door->SetKill();
					break;
				case 1:
					if (GameData::s_key > 0) {
						GameData::s_key -= 1;
						door->SetKill();
					}
					break;
				case 2:
					if (GameData::s_key2 > 0) {
						GameData::s_key2 -= 1;
						door->SetKill();
					}
					break;
				case 3:
					if (GameData::s_key3 > 0) {
						GameData::s_key3 -= 1;
						door->SetKill();
					}
					break;
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
#pragma endregion
	}
}