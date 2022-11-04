#include "Enemy.h"
#include"AnimData.h"
#include"Field.h"
#include"Slash.h"
#include"Effect.h"
#include"Map.h"
void Enemy::StateIdle() {
	//移動量
	const float move_speed = 6;
	//移動量フラグ
	bool move_flag = false;
	//ジャンプ力
	//const float junp_pow = 12;
	//プレイヤーを探索
	Base* player = Base::FindObject(eType_Player);
	//動作確認用
	if (player) {
		//左移動
		if (player->m_pos.x < m_pos.x - 64) {
			//移動量を設定
			m_pos.x += -move_speed;
			//反転フラグ
			m_flip = true;
			move_flag = true;
		}
		//右移動
		if (player->m_pos.x > m_pos.x + 64) {
			m_pos.x += move_speed;
			m_flip = false;
			move_flag = true;
		}
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun);
		}
		/*else {
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle);
		}*/
		//カウント0で待機状態へ
		if (--m_cnt <= 0) {
			//待機時間2～4秒
			m_cnt = rand() % 120 + 120;
			m_state = eState_Wait;
		}
		//攻撃
		if (m_pos.x - player->m_pos.x < 100) {
			//攻撃状態へ移行
			m_state = eState_Attack;
			m_attack_no++;

		}
	}
}
void Enemy::StateAttack(){
	//攻撃アニメーションへ移行
	m_img.ChangeAnimation(eAnimAttack01, false);
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へと移行
		m_state = eState_Wait;
	}
}
void Enemy::StateDamage(){
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Enemy::StateDown(){
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, 0), m_flip));
		m_kill = true;
	}
}
void Enemy::StateWait() {
	//待機アニメーション
	m_img.ChangeAnimation(eAnimIdle);
		//カウント0で通常状態へ
		if (--m_cnt <= 0) {
			//待機時間2～4秒
			m_cnt = rand() % 120 + 120;
			m_state = eState_Idle;
		}
}
Enemy::Enemy(const CVector2D& p, bool flip):
	Base(eType_Enemy){
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_img.ChangeAnimation(0);
	m_pos_old = m_pos = p;
	m_img.SetCenter(128, 224);
	m_flip = flip;
	m_is_ground = true;
	m_state = eState_Idle;
	m_attack_no = rand();
	m_damage_no = -1;
	m_hp = 100;
}
void Enemy::Update(){
	m_pos_old = m_pos;
	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
	case eState_Wait:
		StateWait();
		break;
	case eState_Attack:
		StateAttack();
		break;
	case eState_Damage:
		StateDamage();
		break;
	case eState_Down:
		StateDown();
		break;
	}
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	m_img.UpdateAnimation();
	//スクロール設定
	//m_scroll.x = m_pos.x - 1280 / 2;
}
void Enemy::Draw(){
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
void Enemy::Collision(Base* b){
	switch (b->m_type) {
		//攻撃オブジェクトとの判定
	case eType_Player_Attack:
		//Slash型へのキャスト、型変換出来たら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollsionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128),m_flip));
			}
		}
	break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y));
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y));
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
		/*Field型へキャスト、型変換出来たら
		if (Field* f = dynamic_cast<Field*>(b)) {
			//地面より下に行ったら
			if (m_pos.y > f->GetGroundY()) {
				//地面の高さに戻す
				m_pos.y = f->GetGroundY();
				//落下速度リセット
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;*/
	}
}
