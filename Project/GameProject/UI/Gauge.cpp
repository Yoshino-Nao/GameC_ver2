#include "Gauge.h"
#include "../Character/Player.h"
#include "../Character/Enemy.h"
#pragma region プレイヤー体力ゲージ
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

	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (!p) {
		SetKill();
	}
}

GaugeGreen::GaugeGreen() :Base(eType_UI_Front)
{
	m_img.Load("Image/-5.png");
	m_hp = 0;
	m_hpmax = 0;
	m_gauge = 0;
}
void GaugeGreen::Draw()
{
	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (p) {
		m_hp = h->GetHp();
		m_hpmax = h->GetHpMax();
	}
	else {
		SetKill();
	}
	//GreenGauge.fillAmount = (1.0f / (float)maxhp) * (float)hp;
	//画像の最大サイズは380
	//m_hpの値が残hpに対応
	m_gauge = (380.0f / (float)m_hpmax) * (float)m_hp;
	


	float ratio = (1.0f / (float)m_hpmax) * (float)m_hp;
	
	m_img.SetColor(1.4f - ratio, ratio + 0.2f, 0, 1);
	m_img.SetPos(0, 0);
	m_img.SetRect(0, 0, m_gauge, 30);
	m_img.SetSize(m_gauge, 30);
	m_img.Draw();
}

GaugeRed::GaugeRed() :Base(eType_UI_Mid)
{
	m_img.Load("Image/-5.png");
	m_img.SetColor(1, 0, 0, 1);
	m_gauge = 0;
	m_gauge2 = 0.0f;
	m_gauge3 = 0;
	m_gauge4 = 0.0f;
	m_hp = 0;
	m_hpmax = 0;
}
void GaugeRed::Draw()
{
	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (p) {
		m_hp = h->GetHp();
		m_hpmax = h->GetHpMax();
	}
	else {
		SetKill();
	}
	//GreenGauge.fillAmount = (1.0f / (float)maxhp) * (float)hp;
	m_gauge3 = (380.0f / (float)m_hpmax) * (float)m_hp;
	m_gauge2 = m_gauge3 - m_gauge4;
	m_gauge4 += m_gauge2 * 0.05;
	m_hp = m_gauge4;
	m_img.SetPos(0, 0);
	m_img.SetRect(0, 0, m_hp, 30);
	m_img.SetSize(m_hp, 30);
	m_img.Draw();
}
#pragma endregion

