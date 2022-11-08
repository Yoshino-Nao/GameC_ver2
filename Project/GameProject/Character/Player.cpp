#include "../Base/Base.h"
#include "../Game/AnimData.h"
#include "../Game/Field.h"
#include "../Game/Slash.h"
#include "../Game/Effect.h"
#include "../Game/Game.h"
#include "../Game/Effect_Ring.h" 
#include "../Game/Map.h"
#include "../Game/GameData.h"
#include "../Attack/EnemyBullet.h"
#include "../Attack/Player_Bullet1.h"
#include "../Item/Item.h"
#include "../Title/Title.h"
#include "../Item/Item.h"
#include "../UI/Menu.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

void Player::StateIdle()
{
	Ccnt = 120;
	/*
	//最大速度
	const float move_speed_max = 10;
	//加速度
	const float move_speed_add = 0.5f;
	//ジャンプ力
	const float jump_pow = 18;
	*/
	//移動フラグ
	bool move_flag = false;
	//左移動
	if (HOLD(CInput::eLeft)) {
		vec.x -= move_speed_add;
		/*
		//移動量を設定
		m_pos.x += -move_speed;*/
		//反転フラグ
		m_flip = true;
		move_flag = true;
	}
	//右移動
	if (HOLD(CInput::eRight)) {
		vec.x += move_speed_add;
		/*
		//移動量を設定
		m_pos.x += move_speed;*/
		//反転フラグ
		m_flip = false;
		move_flag = true;
	}
	//ジャンプ
	if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
		m_airjump = true;
	}
	
	if (HOLD(CInput::eButton1)) {
		m_state = eState_Shooting;
		m_attack_no++;
	}
	
	if (vec.x < -move_speed_max) {
		vec.x = -move_speed_max;
	}
	if (vec.x > move_speed_max) {
		vec.x = move_speed_max;
	}
	m_pos.x += vec.x;
	/*
	//攻撃
	if (HOLD(CInput::eButton1)) {
		Base* b = Base::FindObject(eType_Ball);
		if (!b) {
			Base::Add(new Attack(CVector2D(1280, 560), m_flip, eType_Ball, m_attack_no));
			m_img.ChangeAnimation(eAnimAtkIdle);
		}
		
		else if (!b && !m_flip) {

			Base::Add(new Attack(CVector2D(1280, 560), true, eType_Ball,m_attack_no));
		}
		//攻撃状態へ移行
		//m_state = eState_Attack;
		//m_attack_no++;
	}*/
	
	//ジャンプ中なら
	if (!m_is_ground) {
		if (m_vec.y < 0)
			//上昇アニメーション
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//下降アニメーション
			m_img.ChangeAnimation(eAnimJumpDown, false);
		//２段ジャンプ
		if (m_airjump && m_img.GetIndex() >= 3 && PUSH(CInput::eButton2)) {
			m_vec.y = (jump_pow * -0.5f);
			m_is_ground = false;
			m_airjump = false;
		}
		//構え
	}
	//移動中なら
	else {
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			vec.x = 0;
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle);
		}
	}	
	
}

void Player::StateAttack()
{
	
}

void Player::StateShooting()
{
	//移動フラグ
	bool move_flag = false;
	
	//左移動
	if (HOLD(CInput::eLeft)) {
		vec.x -= move_speed_add;
		/*
		//移動量を設定
		m_pos.x += -move_speed;*/
		//反転フラグ
		
		m_flip = true;
		move_flag = true;
	}
	//右移動
	if (HOLD(CInput::eRight)) {
		vec.x += move_speed_add;
		/*
		//移動量を設定
		m_pos.x += move_speed;*/
		//反転フラグ
		
		m_flip = false;
		move_flag = true;
	}
	//ジャンプ
	if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
		m_airjump = true;
	}
	//弾flip補正
	if (m_flip) {
		Bulletpos = -60;
	}
	else {
		Bulletpos = 60;
	}
	if (vec.x < -move_speed_max) {
		vec.x = -move_speed_max;
	}
	if (vec.x > move_speed_max) {
		vec.x = move_speed_max;
	}
	m_pos.x += vec.x;
	
	
	
	Base* b = Base::FindObject(eType_Player_Bullet);
	if (!b) {
		if (Ccnt == 120)
		{	
			Base::Add(new Effect_Ring("Effect_Ring", m_pos, m_flip, m_ang, 32, 144));
		}
		if (Ccnt == 60)
		{
			Base::Add(new Effect_Ring("Effect_Ring2", m_pos, m_flip, m_ang, 32, 144));
		}
		if (FREE(CInput::eButton1)) 
		{
			if (Ccnt <= 120 && Ccnt >= 61) 
			{
				Base::Add(new Player_Bullet1(m_pos + CVector2D(Bulletpos, -75), m_flip, eType_Player_Bullet, m_attack_no));
			}
			m_state = eState_Idle;
		}
	}
	
	
	//攻撃状態へ移行
	//m_state = eState_Attack;
	//m_attack_no++;
	//ジャンプ中なら
	if (!m_is_ground) 
	{
		if (m_vec.y < 0) 
		{
			//上昇アニメーション
			m_img.ChangeAnimation(eAnimAtkJumpUp, false);
		}
		else 
		{
			//下降アニメーション
			m_img.ChangeAnimation(eAnimAtkJumpDown, false);
			//２段ジャンプ
			if (m_airjump && m_img.GetIndex() >= 3 && PUSH(CInput::eButton2)) {
				m_vec.y = (jump_pow * -0.5f);
				m_is_ground = false;
				m_airjump = false;
			}
		}
	}
	//移動中なら
	else {
		if (move_flag) 
		{
			//走るアニメーション
			m_img.ChangeAnimation(eAnimAtkRun);
		}
		else 
		{
			vec.x = 0;
			//待機アニメーション
			m_img.ChangeAnimation(eAnimAtkIdle);
		}
	}
	Ccnt--;
	if (Ccnt <= 0) {
		Ccnt = 0;
	}
}

void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	m_is_inv = true;
	invtime = 120;
	if (m_flip) {
		m_pos.x += 5;
	}
	else {
		m_pos.x -= 5;
	}
	if (m_img.CheckAnimationEnd()) 
	{
		m_state = eState_Idle;
	}
}

void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) 
	{
		m_kill = true;
	}
}

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//画像複製
	m_img = COPY_RESOURCE("Player", CImage);
	m_img.SetSize(224, 224);

	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = p;
	//中心位置設定
	m_img.SetCenter(112, 192);
	//反転フラグ
	m_flip = flip;
	//当たり判定
	m_rect = CRect(-28, -124, 28, 0);
	//通常状態へ
	m_state = eState_Idle;
	//最大速度
	move_speed_max = 10;
	//加速度
	move_speed_add = 0.5f;
	//ジャンプ力
	jump_pow = 18;
	//着地フラグ
	m_is_ground = true;
	//２段ジャンプフラグ
	m_airjump = false;
	//ジャンプindex取得
	jumpindex = 0;
	//無敵フラグ
	m_is_inv = false;
	//AttackのState
	Pstate = 0;
	//攻撃番号
	m_attack_no = rand();
	//弾flip補正値
	Bulletpos = 60;
	//ダメージ番号
    m_damage_no = -1;
	//溜め時間
	Ccnt = 120;
	//無敵時間
	invtime = 0;
	//停止時間
	stpdtime = 0;
	//HP
	m_hp = 120;
	//最大HP
	m_hpmax = 120;
	//敵攻撃力
	m_pow = 0;
	//プレイヤー移動量
	CVector2D vec(0, 0);
	//カメラ移動量
	CVector2D sc_vec(0, 0);
	//初期スクロール設定
	
	
	/*
	m_img.SetSize(224 / 2, 224 / 2);
	m_img.SetCenter(112 / 2, 192 / 2);
	m_rect = CRect(-28 / 2, -124 / 2, 28 / 2, 0);*/
}

void Player::Update() {
	m_img.SetColor(1, 1, 1, 1);
	//std::cout << "Player" << std::endl;
	m_pos_old = m_pos;
	stpdtime--;
	if (stpdtime <= 0) {
		//スクロール設定
		//m_scroll.x = m_pos.x - 1280 / 6;
		//m_scroll.y = m_pos.y - 500;
		switch (m_state) {
			//通常状態
		case eState_Idle:
			StateIdle();
			break;
			//攻撃状態
		case eState_Attack:
			StateAttack();
			break;
			//発射状態
		case eState_Shooting:
			StateShooting();
			break;
			//ダメージ状態
		case eState_Damage:
			StateDamage();
			break;
			//ダウン状態
		case eState_Down:
			StateDown();
			break;
		}
		
		/*
		Base* a = Base::FindObject(eType_Player_Bullet1);
		Player_Bullet1* w = dynamic_cast<Player_Bullet1*>(a);
		if (a) {
			Pstate = w->GetState();
			if (Pstate == 2) {
				//Base::Add(new Effect_Ring("Effect_Ring2", m_pos, m_flip, m_ang));
			}
		}*/
		//スクロール補正
		//目標値
		CVector2D v3(0, 0);
		//落ちていたら落下中状態へ移行
		if (m_is_ground && m_vec.y > GRAVITY * 4) {
			m_is_ground = false;
			m_airjump = true;
		}

		if (m_vec.y > GRAVITY * 4 || m_vec.y < -1)
		{
			v3.y = 300;
		}
		else
		{
			v3.y = 0;
		}
		if (m_flip) {
			v3.x = -300;
		}
		else
		{
			v3.x = +300;
		}

		CVector2D v2 = v3 - sc_vec;
		//スクロール加速度
		sc_vec += v2 * 0.05;
		//基準値+補正値
		m_scroll.x = m_pos.x - 1280 / 2 + sc_vec.x;
		m_scroll.y = m_pos.y - 600 + sc_vec.y;
		//無敵時間
		if (m_is_inv) {
			invtime--;
			m_img.SetColor(1, 1, 1, 0.5);
			if (invtime <= 0) {
				m_is_inv = false;
				invtime = 0;
			}
		}

		//重力による落下
		m_vec.y += GRAVITY;
		//アニメーション更新
		m_img.UpdateAnimation();
		m_pos += m_vec;
		stpdtime = 0;
		if (PUSH(CInput::eButton5)) {
			Base::Add(new Menu());
		}
	}
}

void Player::Draw() {
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//DrawRect();
	
}

void Player::Collision(Base* b)
{
	switch (b->m_type) {
		//ゴール判定
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			b->SetKill();
		}
		break;
	case eType_Item_Score:
		if (Base::CollisionRect(this, b)) {
			GameData::s_score += 1;
			b->SetKill();
		}
		break;
	case eType_Item_LifeUp:
		if (Base::CollisionRect(this, b)) {
			m_hp += 30;
			if (m_hp >= m_hpmax) {
				m_hp = m_hpmax;
			}
			b->SetKill();
		}
		break;
		//Field型へキャスト、型変換できたら
		/*
		if (Field* f = dynamic_cast<Field*>(b)) {
			//地面より下にいったら
			if (m_pos.y > f->GetGroundY()) {
				//地面の高さに戻す
				m_pos.y = f->GetGroundY();
				//落下速度リセット
				m_vec.y = 0;
				//接地フラグON
				m_is_ground = true;

			}
		}
		break;
		*/
	case eType_Enemy_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s) && !m_is_inv) {
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;

	case eType_Enemy:
		if (Enemy* e = dynamic_cast<Enemy*>(b)) {
			if (m_damage_no != e->GetAttackNo() && Base::CollisionRect(this, e) && !m_is_inv) {
				m_damage_no = e->GetAttackNo();
				m_pow = e->GetPow();
				m_hp -= m_pow;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;

				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
	case eType_Bullet:
		if (EnemyBullet* r = dynamic_cast<EnemyBullet*>(b)) {
			if (m_damage_no != r->GetAttackNo() && Base::CollisionRect(this, r)) {
				m_damage_no = r->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0){
				m_pos.x = m_pos_old.x;
			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
				m_airjump = false;
				//基準値+補正値
				//m_scroll.x = m_pos.x - 1280 / 2 + sc_ver.x;
				//m_scroll.y = m_pos.y - 500 + sc_ver.y;
				
			}
		}
		break;
	
	}
}