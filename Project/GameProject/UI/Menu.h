#pragma once
#include "../Base/Base.h"

class Menu :public Base {
	enum {
		eCnt,
		eExit
	};
	int m_select;
	int m_cnt;
public:
	Menu();
	void UpDate();
	void Draw();
};
	