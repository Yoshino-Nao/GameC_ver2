#pragma once
#include "../Base/Base.h"
class GaugeBack : public Base {
public:
	CImage m_img;
public:
	GaugeBack();
	void Draw();
};
class GaugeGreen : public Base {
public:
	CImage m_img;
	int player_hp;
	int player_hpmax;
	int m_hp;
public:
	GaugeGreen();
	void Draw();
};
class GaugeRed : public Base {
public:
	CImage m_img;
	int player_hp;
	int player_hpmax;
	int m_hp;
	//�␳�l
	float m_hp2;
	//�ڕW�l
	int m_hp3;
	//�����x
	float m_hp4;
public:
	GaugeRed();
	void Draw();
};