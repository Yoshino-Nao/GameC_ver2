#include "Player_Bullet1.h"
#include "../Map/Map.h"
#include "../Game/GameData.h"
#include "../Character/Player.h"
Player_Bullet1::Player_Bullet1(const CVector2D& p, bool flip, int attack_no)
	:Base(eType_Player_Bullet)
{
	//画像複製
	m_img = COPY_RESOURCE("bullet", CImage);
	//m_img.SetSize(128, 32);
	//再生アニメーション設定
	//m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = p;
	//中心位置設定
	//m_img.SetCenter(64, 16);
	//反転フラグ
	m_flip = flip;

	//m_rect = CRect(-16, -16, 16, 16);
	
	//弾消滅時間
	cnt = 60;
	//溜め時間
	//Ccnt = 0;
	//攻撃番号
	m_attack_no = rand();
	m_attack_no = attack_no;
	//Player反転フラグ取得

	

}

void Player_Bullet1::Update()
{
	m_pos_old = m_pos;
	//m_img.UpdateAnimation();
	m_img.SetSize(12, 1);
	//m_img.SetCenter(80, 16);
	cnt--;
	m_rect = CRect(-6, -1, 6, 1);
	if (!m_flip) {
		CVector2D vec = CVector2D(10, 0);
		m_pos += vec;
	}
	else {
		CVector2D vec = CVector2D(10, 0);
		m_pos -= vec;
	}
	if (cnt <= 0) {
		SetKill();
	}
}

void Player_Bullet1::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	DrawRect();
}

void Player_Bullet1::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(m_pos, m_rect,&m_pos);
			if (t != NULL_TIP)
				SetKill();
			
		}
		break;
		//case eType_Enemy:
			//SetKill();

	}
}
