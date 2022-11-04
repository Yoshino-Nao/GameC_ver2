#include "Enemy.h"
#include"AnimData.h"
#include"Field.h"
#include"Slash.h"
#include"Effect.h"
#include"Map.h"
void Enemy::StateIdle() {
	//�ړ���
	const float move_speed = 6;
	//�ړ��ʃt���O
	bool move_flag = false;
	//�W�����v��
	//const float junp_pow = 12;
	//�v���C���[��T��
	Base* player = Base::FindObject(eType_Player);
	//����m�F�p
	if (player) {
		//���ړ�
		if (player->m_pos.x < m_pos.x - 64) {
			//�ړ��ʂ�ݒ�
			m_pos.x += -move_speed;
			//���]�t���O
			m_flip = true;
			move_flag = true;
		}
		//�E�ړ�
		if (player->m_pos.x > m_pos.x + 64) {
			m_pos.x += move_speed;
			m_flip = false;
			move_flag = true;
		}
		if (move_flag) {
			//����A�j���[�V����
			m_img.ChangeAnimation(eAnimRun);
		}
		/*else {
			//�ҋ@�A�j���[�V����
			m_img.ChangeAnimation(eAnimIdle);
		}*/
		//�J�E���g0�őҋ@��Ԃ�
		if (--m_cnt <= 0) {
			//�ҋ@����2�`4�b
			m_cnt = rand() % 120 + 120;
			m_state = eState_Wait;
		}
		//�U��
		if (m_pos.x - player->m_pos.x < 100) {
			//�U����Ԃֈڍs
			m_state = eState_Attack;
			m_attack_no++;

		}
	}
}
void Enemy::StateAttack(){
	//�U���A�j���[�V�����ֈڍs
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃւƈڍs
		m_state = eState_Wait;
	}
}
void Enemy::StateDamage(){
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Enemy::StateDown(){
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, 0), m_flip));
		m_kill = true;
	}
}
void Enemy::StateWait() {
	//�ҋ@�A�j���[�V����
	m_img.ChangeAnimation(eAnimIdle);
		//�J�E���g0�Œʏ��Ԃ�
		if (--m_cnt <= 0) {
			//�ҋ@����2�`4�b
			m_cnt = rand() % 120 + 120;
			m_state = eState_Idle;
		}
}
Enemy::Enemy(const CVector2D& p, bool flip):
	Base(eType_Enemy){
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_img.ChangeAnimation(0);
	m_pos_old = m_pos = p;
	m_img.SetCenter(128, 224);
	m_flip = flip;
	m_is_ground = true;
	m_state = eState_Idle;
	m_attack_no = rand();
	m_damage_no = -1;
	m_hp = 100;
}
void Enemy::Update(){
	m_pos_old = m_pos;
	switch (m_state) {
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
	case eState_Wait:
		StateWait();
		break;
	case eState_Attack:
		StateAttack();
		break;
	case eState_Damage:
		StateDamage();
		break;
	case eState_Down:
		StateDown();
		break;
	}
	//�d�͂ɂ�闎��
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	m_img.UpdateAnimation();
	//�X�N���[���ݒ�
	//m_scroll.x = m_pos.x - 1280 / 2;
}
void Enemy::Draw(){
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
void Enemy::Collision(Base* b){
	switch (b->m_type) {
		//�U���I�u�W�F�N�g�Ƃ̔���
	case eType_Player_Attack:
		//Slash�^�ւ̃L���X�g�A�^�ϊ��o������
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollsionRect(this, s)) {
				//�����U���̘A���_���[�W�h�~
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128),m_flip));
			}
		}
	break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y));
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y));
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
		/*Field�^�փL���X�g�A�^�ϊ��o������
		if (Field* f = dynamic_cast<Field*>(b)) {
			//�n�ʂ�艺�ɍs������
			if (m_pos.y > f->GetGroundY()) {
				//�n�ʂ̍����ɖ߂�
				m_pos.y = f->GetGroundY();
				//�������x���Z�b�g
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;*/
	}
}
