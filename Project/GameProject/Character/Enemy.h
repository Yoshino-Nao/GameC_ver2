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
	//状態変数
	int m_state;

	CImage m_img;
	//反転フラグ
	bool m_flip;
	//着地判定用フラグ
	bool m_is_ground;
	//ダメージ番号
	int m_damage_no;
	//攻撃番号
	int m_attack_no;
	//停止時間
	int stptime;
	//体力
	int m_hp;
	//最大体力
	int m_hpmax;
	//攻撃力
	int m_pow;
	int cnt;
	int bcnt;
	//タイプ用変数
	int EnemyType;
	//敵とプレイヤーまでの距離
	CVector2D v;
	//各状態での挙動
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