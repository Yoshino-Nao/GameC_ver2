#pragma once
#include "../Base/Base.h"

class UI :public Base {
public:
	CImage m_img;
	//�v���C���[HP
	int p_hp;
public:
	UI();
	void Draw();
};


