#pragma once
#include "../Base/Base.h"

class Menu :public Base {
	enum {
		eItem,
		eTitle
	};
	int m_select;
	int m_Item_select;
	int m_cnt;
	bool m_in_item;
	bool m_use_item;
public:
	Menu();
	void Update();
	void Draw();
	bool UseItemflag() {
		return m_use_item;
	}
	int UseItemNum() {
		return m_Item_select;
	}

};
	