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
		eState_GunDraw,
		eState_Shooting,
		eState_Damage,
		eState_Down,
		

	};
	CImage m_img;
#pragma region 変数

#pragma region 移動関係
	//X最大速度
	float move_xspeed_max;
	//X加速度
	float move_xspeed_add;
	//ジャンプ力
	float move_yspeed_max;
	//ジャンプ入力時間
	float jump_pow;
	//摩擦
	float friction;
	//現在高度
	float m_groundpos;
	//過去高度
	float m_groundpos_old;
	//高度差
	float m_groundpos_diff;
	//高度差計算用
	float m_groundpos_diff2;
	//反転フラグ
	bool m_flip;
	//着地判定用フラグ
	bool m_is_ground;
	//２段ジャンプフラグ
	bool m_airjump;
	//着地モーションフラグ
	bool m_is_land;

	bool m_land2;
#pragma endregion

#pragma region 攻撃関係
	//攻撃予約フラグ
	bool m_atk_yoyaku;
	//攻撃力
	int m_attack_pow;
	//攻撃番号
	int m_attack_no;
	//ダメージ番号
	int m_damage_no;
	//攻撃発生補正値
	float m_atkpos;
	//手の位置
	float m_handpos;
	//発射レート
	int rate;
#pragma endregion

#pragma region プレイヤーの状態
	//状態変数
	int m_state;
	//無敵フラグ
	bool m_is_inv;
	//無敵時間
	int invtime;
	//停止時間
	int stpdtime;
	//エリアチェンジフラグ
	bool m_enable_area_change;
	//エリアチェンジオブジェクトに触れているフラグ
	bool m_hit_area_change;
	//HP
	int m_hp;
	//最大HP
	int m_hpmax;
	//２段ジャンプアイテム取得
	bool m_getairjump;
	//剣アイテム取得
	bool m_getSword;
	//銃取得
	bool m_getGun;
#pragma endregion

	//右スティック
	CVector2D r;
	//左スティック
	CVector2D l;
	//スクロール補間用
	CVector2D sc_vec;
	bool m_menukill;
#pragma endregion

	//各状態での挙動
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