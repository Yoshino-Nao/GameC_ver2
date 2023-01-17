#include "BreakWall.h"
#include"../Character/Player.h"
BreakWall::BreakWall(int type, const CVector2D& pos) :Base(eType_BreakWall)
{
	m_img = COPY_RESOURCE("MapTip_64", CImage);
	m_type = type;
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(64, 64);
	m_img.SetRect(64, 0, 64 + 64, 64);
	//中心位置設定
	m_img.SetCenter(0, 32);
	//当たり判定用矩形
	m_rect = CRect(0, -32, 64, 32);
}

void BreakWall::Update()
{
	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (p) {
		
		switch (m_type)
		{
		case 0:
			
			break;
		}
	}
}

void BreakWall::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));

	m_img.Draw();
	//DrawRect();
}
