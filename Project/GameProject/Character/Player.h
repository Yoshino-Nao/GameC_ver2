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
#pragma region �ϐ�

#pragma region �ړ��֌W
	//X�ő呬�x
	float move_xspeed_max;
	//X�����x
	float move_xspeed_add;
	//�W�����v��
	float move_yspeed_max;
	//�W�����v���͎���
	float jump_pow;
	//���C
	float friction;
	//���ݍ��x
	float m_groundpos;
	//�ߋ����x
	float m_groundpos_old;
	//���x��
	float m_groundpos_diff;
	//���x���v�Z�p
	float m_groundpos_diff2;
	//���]�t���O
	bool m_flip;
	//���n����p�t���O
	bool m_is_ground;
	//�Q�i�W�����v�t���O
	bool m_airjump;
	//���n���[�V�����t���O
	bool m_is_land;

	bool m_land2;
#pragma endregion

#pragma region �U���֌W
	//�U���\��t���O
	bool m_atk_yoyaku;
	//�U����
	int m_attack_pow;
	//�U���ԍ�
	int m_attack_no;
	//�_���[�W�ԍ�
	int m_damage_no;
	//�U�������␳�l
	float m_atkpos;
	//��̈ʒu
	float m_handpos;
	//���˃��[�g
	int rate;
#pragma endregion

#pragma region �v���C���[�̏��
	//��ԕϐ�
	int m_state;
	//���G�t���O
	bool m_is_inv;
	//���G����
	int invtime;
	//��~����
	int stpdtime;
	//�G���A�`�F���W�t���O
	bool m_enable_area_change;
	//�G���A�`�F���W�I�u�W�F�N�g�ɐG��Ă���t���O
	bool m_hit_area_change;
	//HP
	int m_hp;
	//�ő�HP
	int m_hpmax;
	//�Q�i�W�����v�A�C�e���擾
	bool m_getairjump;
	//���A�C�e���擾
	bool m_getSword;
	//�e�擾
	bool m_getGun;
#pragma endregion

	//�E�X�e�B�b�N
	CVector2D r;
	//���X�e�B�b�N
	CVector2D l;
	//�X�N���[����ԗp
	CVector2D sc_vec;
	bool m_menukill;
#pragma endregion

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
	~Player();
	void Move();
	void GetItem(int i);
	void UseItem(int n);
	void LifeUp(int v);
	void KnockBack(CVector2D m_epos,int pow);
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