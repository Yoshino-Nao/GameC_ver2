#include "Goal2.h"
#include "start.h"
#include "../Game/GameData.h"

Goal2::Goal2(const CVector2D& pos) :Base(eType_Goal2)
{
	//画像複製
	m_img = COPY_RESOURCE("Goal2", CImage);
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(64, 128);
	//中心位置設定
	m_img.SetCenter(32, 128);
	//当たり判定用矩形
	m_rect = CRect(-32, -128, 32, 0);
}

void Goal2::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();

}

void Goal2::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			//GameData::s_score += 1;
			Base::Add(new start(CVector2D(3000, 1235)));
			SetKill();

		}
		break;
	}
}