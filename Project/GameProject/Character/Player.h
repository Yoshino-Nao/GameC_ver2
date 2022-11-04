#pragma once
#include"../Base/Base.h"

class Player :public Base {
private:
	//状態
	enum {
		eState_Idle,
		eState_Attack,
		eState_Shooting,
		eState_Damage,
		eState_Down,
		

	};
	//状態変数
	int m_state;
	//最大速度
	float move_speed_max;
	//加速度
	float move_speed_add;
	//ジャンプ力
	float jump_pow;
	CImage m_img;
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
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
	//弾flip補正値
	int Bulletpos;

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
	void StateAttack();
	void StateShooting();
	void StateDamage();
	void StateDown();
	

public:
	//停止時間
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