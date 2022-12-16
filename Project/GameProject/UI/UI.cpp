#include "UI.h" 
#include "../Game/GameData.h"
#include "../Item/start.h"
#include "../Item/Goal.h"
#include "../Character/Player.h"
UI::UI() :Base(eType_UI_Score) {
	m_img.Load("Image/UI.png");
	m_playerHP = -1;
	digit = 0;
}

void UI::Draw() {
	int score = GameData::s_score;
	for (int i = 0; i < 3; i++, score /= 10) {
		int s = score % 10;
		m_img.SetRect(16 * s, 16, 16 * s + 16, 32);
		m_img.SetSize(16, 16);
		m_img.SetPos(500 - 16 * i, 0);
		m_img.Draw();
	}
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
		
	}
	for (int i = 0; i < digit; i++, m_playerHP /= 10) {
		int s = m_playerHP % 10;
		m_img.SetRect(16 * s, 16, 16 * s + 16, 32);
		m_img.SetSize(16, 16);
		m_img.SetPos(90 - 16 * i, 6);
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