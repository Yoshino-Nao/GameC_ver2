#pragma once
#include"../Base/Base.h"

class Player :public Base {
private:
	//���
	enum {
		eState_Idle,
		eState_Attack,
		eState_Shooting,
		eState_Damage,
		eState_Down,
		

	};
	//��ԕϐ�
	int m_state;
	//�ő呬�x
	float move_speed_max;
	//�����x
	float move_speed_add;
	//�W�����v��
	float jump_pow;
	CImage m_img;
	//���]�t���O
	bool m_flip;
	//���n�t���O
	bool m_is_ground;
	//�Q�i�W�����v�t���O
	bool m_airjump;
	//�W�����vindex�擾
	int jumpindex;
	//���G�t���O
	bool m_is_inv;
	//Attack��State
	int Pstate;
	//�U���ԍ�
	int m_attack_no;
	//�eflip�␳�l
	int Bulletpos;

	//���ߎ���(120)
	int Ccnt;
	//���G����
	int invtime;
	
	//�_���[�W�ԍ�
	int m_damage_no;
	//HP
	int m_hp;
	//�ő�HP
	int m_hpmax;
	//�G�U����
	int m_pow;
	//�v���C���[�ړ���
	CVector2D vec;
	//�X�N���[����ԗ�
	CVector2D sc_vec;
	//�e��Ԃł̋���
	void StateIdle();
	void StateAttack();
	void StateShooting();
	void StateDamage();
	void StateDown();
	

public:
	//��~����
	int stpdtime;
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetFlipFlag() {
		return !m_flip;
	}
	int GetHp() {
		return m_hp;
	}
	int GetHpMax() {
		return m_hpmax;
	}
	CVector2D GetPos() {
		return m_pos;
	}
};