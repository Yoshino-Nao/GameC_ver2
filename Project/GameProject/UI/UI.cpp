#include "UI.h" 
#include "../Game/GameData.h"
#include "../Item/start.h"
#include "../Item/Goal.h"
#include "../Character/Player.h"
UI::UI() :Base(eType_UI) {
	m_img.Load("Image/UI.png");
	p_hp = 0;
	
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
	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (p) {
		p_hp = h->GetHp();
	}
	for (int i = 0; i < 3; i++, p_hp /= 10) {
		int s = p_hp % 10;
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