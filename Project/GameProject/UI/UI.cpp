#include "UI.h" 
#include "../Game/GameData.h"
#include "../Item/start.h"
#include "../Item/Goal.h"
#include "../Character/Player.h"
UI::UI() :Base(eType_UI_Score) {
	m_img.Load("Image/UI.png");
	m_playerHP = -1;
	m_playerHPMax = 0;
	m_old_playerHPMax = 0;
	digit = 0;
	digit = 0;
}

void UI::Draw() {
	int key = GameData::s_key;
	for (int i = 0; i < 1; i++, key /= 10) {
		int s = key % 10;
		m_img.SetRect(16 * s, 16, 16 * s + 16, 32);
		m_img.SetSize(24, 24);
		m_img.SetPos(600 - 16 * i, 8);
		m_img.Draw();
	}
	FONT_T()->Draw(575, 30, 1, 1, 1, "X");
	/*
	Base* b = Base::FindObject(eType_start);
	if (!b) {
		GameData::s_time--;
	}
	int t = GameData::s_time / 60;
	for (int i = 0; i < 4; i++, t /= 10) {
		int s = t % 10;
		m_img.SetRect(16 * s, 16, 16 * s + 16, 32);
		m_img.SetSize(24, 24);
		m_img.SetPos(100 - 24 * i, 0);
		m_img.Draw();
	}*/
	m_old_playerHP = m_playerHP;

	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (p) {
		m_playerHP = h->GetHp();
		m_playerHPMax = h->GetHpMax();
		if (m_playerHP <= 0) {
			digit = 1;
		}
		else if (m_old_playerHP != m_playerHP) {
			int hp = m_playerHP;
			digit = 0;
			while (hp != 0) {
				hp /= 10;
				digit++;
			}
		}
		if (m_playerHPMax <= 0) {
			digitMax = 1;
		}
		else if (m_old_playerHPMax != m_playerHPMax) {
			int hpmax = m_playerHPMax;
			digitMax = 0;
			while (hpmax != 0) {
				hpmax /= 10;
				digitMax++;
			}
		}
	}
	
	for (int i = 0; i < digitMax; i++, m_playerHPMax /= 10) {
		int s = m_playerHPMax % 10;
		m_img.SetRect(16 * s, 18, 16 * s + 16, 32);
		m_img.SetSize(16, 18);
		m_img.SetPos(90 + (16 * (digitMax + 1)) - (16 * i), 5);
		m_img.Draw();
	}
	m_img.SetRect(16 * 10, 18, 16 * 10 + 16, 32);
	m_img.SetSize(16, 18);
	m_img.SetPos(160 - 16 * 3, 5);
	m_img.Draw();
	for (int i = 0; i < digit; i++, m_playerHP /= 10) {
		int s = m_playerHP % 10;
		m_img.SetRect(16 * s, 18, 16 * s + 16, 32);
		m_img.SetSize(16, 18);
		m_img.SetPos(90 - 16 * i, 5);
		m_img.Draw();
	}
	/*
	//“G‚ª‚¢‚È‚¯‚ê‚Î
	Base* g = Base::FindObject(eType_Goal);
	if (g == nullptr) {
		//ƒQ[ƒ€ƒNƒŠƒA‚Ì•\Ž¦
		m_img.SetRect(0, 64, 0 + 160, 64 + 32);
		m_img.SetSize(160, 32);
		m_img.SetPos(100, 200);
		m_img.Draw();
	}
	*/
}

UIimg::UIimg() :Base(eType_UI_Front)
{
	m_img = COPY_RESOURCE("Key", CImage);
	m_img.SetSize(16 * 2, 16 * 2);
	m_img.SetPos(550 - 16, 4);
	//m_img.SetColor(1, 1, 1, 1);
}

void UIimg::Draw()
{
	m_img.Draw();
}
