#pragma once
#include"../Base/Base.h"

class Enemy :public Base {
private:
	enum {
		eState_Idle,
		eState_Down,
		eState_Damage,
		eState_Attack,
		eState_Wait,


	};
	//��ԕϐ�
	int m_state;

	CImage m_img;
	//���]�t���O
	bool m_flip;
	//���n����p�t���O
	bool m_is_ground;
	//�_���[�W�ԍ�
	int m_damage_no;
	//�U���ԍ�
	int m_attack_no;
	//��~����
	int stptime;
	//�̗�
	int m_hp;
	//�ő�̗�
	int m_hpmax;
	//�U����
	int m_pow;
	int cnt;
	int bcnt;
	//�^�C�v�p�ϐ�
	int EnemyType;
	//�G�ƃv���C���[�܂ł̋���
	CVector2D v;
	//�e��Ԃł̋���
	void StateIdle();
	void StateDamage();
	void StateDown();
	void StateAttack();
	void StateWait();
	void KnockBack(CVector2D m_epos,int pow);
public:
	Enemy(const CVector2D& p, bool flip ,int type);
	~Enemy();
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
	int GetPow() {
		return m_pow;
	}
	int GetStopTime() {
		return stptime;
	}
};