#include "Door.h"
Door::Door(const CVector2D& pos, int key)
	:Base(eType_Door)
{	
	//Key変数(0なら通過可能)
	m_key = key;
	//グラフィック差し替え用
	switch (key)
	{
	case 0:
		
	case 1:

		break;
	}
	m_img = COPY_RESOURCE("MapTip_64", CImage);
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(64 * 2, 64 * 2);
	m_img.SetRect(128, 0, 128 + 64, 64);
	//中心位置設定
	m_img.SetCenter(64, 64);
	//当たり判定用矩形
	m_rect = CRect(-64, -64, 64, 64);
}

void Door::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}

int Door::GetKey()
{
	return m_key;
}
