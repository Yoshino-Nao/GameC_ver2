#pragma once
#include "../Base/Base.h"

class UI :public Base {
public:
	CImage m_img;
	//�v���C���[HP
	int m_playerHP;
	int m_old_playerHP;
	int digit;
public:
	UI();
	void Draw();
};


