#pragma once
#include"../Base/Base.h"

class Player :public Base {
private:
	//���
	enum {
		eState_Idle,
		eState_Attack1,
		eState_Attack2,
		eState_Attack3,
		eState_GunDraw,
		eState_Shooting,
		eState_Damage,
		eState_Down,
		

	};
	CImage m_img;
	//��ԕϐ�
	int m_state;
	//X�ő呬�x
	float move_xspeed_max;
	//X�����x
	float move_xspeed_add;
	//�W�����v��
	float move_yspeed_max;
	//�W�����v��
	float jump_pow;
	//���C
	float friction;
	
	
	//���]�t���O
	bool m_flip;
	//���n�t���O
	bool m_is_ground;
	//���n���[�V�����t���O
	bool m_is_land;
	//�Q�i�W�����v�t���O
	bool m_airjump;
	//�W�����vindex�擾
	int jumpindex;
	//���G�t���O
	bool m_is_inv;
	//�G���A�`�F���W�t���O
	bool m_enable_area_change;
	//�G���A�`�F���W�I�u�W�F�N�g�ɐG��Ă���t���O
	bool m_hit_area_change;
	
	//�U����
	int m_attack_pow;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�
	int m_damage_no;
	//�U�������␳�l
	float m_atkpos = 60;
	//���˃��[�g
	int rate;
	//���G����
	int invtime;
	//��~����
	int stpdtime;
	
	//HP
	int m_hp;
	//�ő�HP
	int m_hpmax;
	//�G�U����
	int m_pow;
	//�擾�A�C�e��
	//int m_ItemList[10];

	CVector2D r;

	CVector2D l;
	//�v���C���[�ړ���
	CVector2D vec;
	//�X�N���[����ԗ�
	CVector2D sc_vec;
	//�e��Ԃł̋���
	void StateIdle();
	void StateAttack1();
	void StateAttack2();
	void StateAttack3();
	void StateGunDraw();
	void StateShooting();
	void StateDamage();
	void StateDown();
	

public:
	
	Player(const CVector2D& p, bool flip);
	void Move();
	void GetItem(int i);
	void LifeUp(int v);
	void Update();
	void Draw();
	void Collision(Base* b);
	
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