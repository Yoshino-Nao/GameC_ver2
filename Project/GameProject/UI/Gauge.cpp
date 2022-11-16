#include "Gauge.h"
#include "../Character/Player.h"

GaugeBack::GaugeBack() :Base(eType_UI_Back)
{
	m_img.Load("Image/-5.png");
	m_img.SetColor(0.3, 0.3, 0.3, 1);
}
void GaugeBack::Draw()
{
	m_img.SetPos(0, 0);
	m_img.SetRect(0, 0, 380, 30);
	m_img.SetSize(380, 30);
	m_img.Draw();
}

GaugeGreen::GaugeGreen() :Base(eType_UI_Front)
{
	m_img.Load("Image/-5.png");
	m_img.SetColor(0, 1, 0, 1);
	player_hp = 0;
	player_hpmax = 0;
	m_hp = 0;
}
void GaugeGreen::Draw()
{
	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (p) {
		player_hp = h->GetHp();
		player_hpmax = h->GetHpMax();
	}
	//GreenGauge.fillAmount = (1.0f / (float)maxhp) * (float)hp;
	m_hp = (380.0f / (float)player_hpmax) * (float)player_hp;
	//画像の最大サイズは380
	//m_hpの値が残hpに対応
	
	m_img.SetPos(0, 0);
	m_img.SetRect(0, 0, m_hp, 30);
	m_img.SetSize(m_hp, 30);
	m_img.Draw();
}

GaugeRed::GaugeRed() :Base(eType_UI_Mid)
{
	m_img.Load("Image/-5.png");
	m_img.SetColor(1, 0, 0, 1);
	m_hp = 0;
	m_hp2 = 0.0f;
	m_hp3 = 0;
	m_hp4 = 0.0f;
	player_hp = 0;
	player_hpmax = 0;
}
void GaugeRed::Draw()
{
	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (p) {
		player_hp = h->GetHp();
		player_hpmax = h->GetHpMax();
	}
	//GreenGauge.fillAmount = (1.0f / (float)maxhp) * (float)hp;
	m_hp3 = (380.0f / (float)player_hpmax) * (float)player_hp;
	m_hp2 = m_hp3 - m_hp4;
	m_hp4 += m_hp2 * 0.05;
	m_hp = m_hp4;
	m_img.SetPos(0, 0);
	m_img.SetRect(0, 0, m_hp, 30);
	m_img.SetSize(m_hp, 30);
	m_img.Draw();
}