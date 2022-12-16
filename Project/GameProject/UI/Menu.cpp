#include "Menu.h"

Menu::Menu()
	:Base(eType_Menu){
	m_select = eLifeUp;
	m_cnt = 0;
}

void Menu::Update()
{
	//選択
	if (PUSH(CInput::eUp)) {
		m_select--;
		if (m_select < 0) m_select = 0;
	}
	if (PUSH(CInput::eDown)) {
		m_select++;
		if (m_select > 1) m_select = 1;
	}
	if (PUSH(CInput::eButton4)) {
		switch (m_select){
		case eLifeUp:
			LifeUp();
			//m_cnt++;
			break;
		case eExit:
			SetKill();
			break;
		}
	}
}

void Menu::Draw()
{
	CVector2D pos[2] = {
		CVector2D(100,200),
		CVector2D(100,300),
	};
	const char* text[2] = {
		"LifeUp",
		"Exit"
	};
	for (int i = 0; i < 2; i++) {
		FONT_T()->Draw(pos[i].x, pos[i].y, 1, 1, 1, text[i]);
	}
	//カーソル
	FONT_T()->Draw(pos[m_select].x - 64, pos[m_select].y, 1, 1, 1, ">");
	//テストデータの表示
	//FONT_T()->Draw(0, 128, 1, 0, 0, "m_cnt[%d]", m_cnt);

}

bool Menu::LifeUp()
{
	if (PUSH(CInput::eButton4)) {
		return true;
	}
	else {
		return false;
	}
}
