#include "Menu.h"
#include "../Character/Player.h"
#include"../Game/Game.h"
#include "../Game/GameData.h"
#include"../Title/Title.h"
#include "../Map/Map.h"
Menu::Menu()
	:Base(eType_Menu){
	m_select = eItem;
	m_Item_select = 0;
	m_cnt = 0;
	m_in_item = false;
	m_use_item = false;
}

void Menu::Update()
{
	//選択
	if (!m_in_item) {
		if (PUSH(CInput::eUp)) {
			m_select--;
			if (m_select < 0) m_select = 0;
		}
		if (PUSH(CInput::eDown)) {
			m_select++;
			if (m_select > 1) m_select = 1;
		}
	}
	if (m_select == eItem && m_in_item) {
		if (PUSH(CInput::eRight)) {
			m_Item_select++;
			if (m_Item_select > 1) m_Item_select = 1;
		}
		if (PUSH(CInput::eLeft)) {
			m_Item_select--;
			if (m_Item_select < 0) m_Item_select = 0;
		}
	}
	if (PUSH(CInput::eButton3)) {
		switch (m_select){
		case eItem:
			(!m_in_item ? m_in_item = true : m_in_item = false);
			break;
		case eTitle:
			Base::KillAll();
			//ゲームシーンへ
			Base::Add(new Title());
			Base::Add(new License());
			
			break;
		}
	}
	if (PUSH(CInput::eButton3) && m_in_item) {
		m_use_item = true;
		switch (m_Item_select) {
		case 0:
			
			break;
		case 1:
			
			break;
		}
	}
	else {
		m_use_item = false;
	}
}

void Menu::Draw()
{
	CVector2D pos[2] = {
		CVector2D(100,200),
		CVector2D(100,600),
	};
	CVector2D Itempos[2]{
		CVector2D(300,200),
		CVector2D(500,200),
	};
	const char* text[2] = {
		"Item",
		"Title"
	};
	for (int i = 0; i < 2; i++) {
		FONT_T()->Draw(pos[i].x, pos[i].y, 1, 1, 1, text[i]);

	}
	for (int i = 0; i < 2; i++) {
		//m_img
		//FONT_T()->Draw(Itempos[i].x, Itempos[i].y, 1, 1, 1, text[i]);
		FONT_T()->Draw(Itempos[i].x, Itempos[i].y+64, 1, 1, 1, "%d", GameData::s_itemlist[i]);
	}
	//カーソル
	FONT_T()->Draw(pos[m_select].x - 64, pos[m_select].y, 1, 1, 1, ">");
	FONT_T()->Draw(Itempos[m_Item_select].x - 64, Itempos[m_Item_select].y, 1, 1, 1, ">");
	//テストデータの表示
	//FONT_T()->Draw(0, 128, 1, 0, 0, "m_cnt[%d]", m_cnt);
}