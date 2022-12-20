#pragma once
#include "../Base/Base.h"

class Menu :public Base {
	enum {
		eItem,
		eExit
	};
	int m_select;
	int m_Item_select;
	int m_cnt;
	bool m_in_item;
public:
	Menu();
	void Update();
	void Draw();
	bool LifeUp() {
		if (PUSH(CInput::eButton4)) {
			return true;
		}
		else {
			return false;
		}
	}
};
	