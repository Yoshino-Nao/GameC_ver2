#pragma once
#include"../Base/Base.h"

class Attack : public Base {
	
	
private:
//状態
enum {
	eState_Idle,
	eState_Attack,
	eState_Attack2,
	eState_Attack3,

};

//状態変数
int m_state;

CImage m_img;
//反転フラグ
bool m_flip;

//弾消滅時間
int cnt;
//溜め時間(120)
int Ccnt;
//攻撃番号
int m_attack_no;
//ダメージ番号
int m_damage_no;
//各状態での挙動
void StateIdle();
void StateAttack();
void StateAttack2();
void StateAttack3();

public:
	Attack(const CVector2D& p, bool flip,int type,int attack_no);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
	int GetState() {
		return m_state;
	}
};
