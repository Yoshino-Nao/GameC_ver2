#pragma once
#include "../Base/Base.h"

class UI :public Base {
public:
	CImage m_img;
	//�v���C���[HP
	int m_playerHP;
	int m_playerHPMax;
	int m_old_playerHP;
	int m_old_playerHPMax;
	int digit;
	int digitMax;
public:
	UI();
	void Draw();
};


