#pragma once
#include "../Base/Base.h"

class Menu :public Base {
	enum {
		eLifeUp,
		eExit
	};
	int m_select;
	int m_cnt;
public:
	Menu();
	void Update();
	void Draw();
	bool LifeUp();
};
	