#pragma once
#include"../Base/Base.h"

class Player :public Base {
private:
	//状態
	enum {
		eState_Idle,
		eState_Attack1,
		eState_Attack2,
		eState_Attack3,
		eState_Draw,
		eState_Shooting,
		eState_Damage,
		eState_Down,
		

	};
	//状態変数
	int m_state;
	//X最大速度
	float move_xspeed_max;
	//X加速度
	float move_xspeed_add;
	//Y最高速度
	float move_yspeed_max;
	//Y加速度
	float move_yspeed_add;
	//摩擦
	float friction;
	//ジャンプ力
	float jump_pow;
	CImage m_img;
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	//着地モーションフラグ
	bool m_is_land;
	//２段ジャンプフラグ
	bool m_airjump;
	//ジャンプindex取得
	int jumpindex;
	//無敵フラグ
	bool m_is_inv;
	//AttackのState
	int Pstate;
	//攻撃番号
	int m_attack_no;
	//攻撃発生補正値
	float m_atkpos = 60;
	//溜め時間(120)
	int Ccnt;
	//無敵時間
	int invtime;
	
	//ダメージ番号
	int m_damage_no;
	//HP
	int m_hp;
	//最大HP
	int m_hpmax;
	//敵攻撃力
	int m_pow;
	//プレイヤー移動量
	CVector2D vec;
	//スクロール補間量
	CVector2D sc_vec;
	//各状態での挙動
	void StateIdle();
	void StateAttack1();
	void StateAttack2();
	void StateAttack3();
	void StateDraw();
	void StateShooting();
	void StateDamage();
	void StateDown();
	

public:
	//停止時間
	int stpdtime;
	Player(const CVector2D& p, bool flip);
	void Move();
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