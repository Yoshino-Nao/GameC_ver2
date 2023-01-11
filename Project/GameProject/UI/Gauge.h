#pragma once
#include "../Base/Base.h"
#pragma region プレイヤー体力ゲージ
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
	int m_hp;
	int m_hpmax;
	int m_gauge;
public:
	GaugeGreen();
	void Draw();
};
class GaugeRed : public Base {
public:
	CImage m_img;
	int m_hp;
	int m_hpmax;
	int m_gauge;
	//補正値
	float m_gauge2;
	//目標値
	int m_gauge3;
	//加速度
	float m_gauge4;
public:
	GaugeRed();
	void Draw();
};
#pragma endregion

#pragma region 敵体力ゲージ
class EGaugeBack : public Base {
public:
	CImage m_img;
	CVector2D m_size;
public:
	EGaugeBack(CVector2D size);
	void Draw();
};
class EGaugeGreen : public Base {
public:
	CImage m_img;
	int m_hp;
	int m_hpmax;
	int m_gauge;
public:
	EGaugeGreen(const CVector2D& pos, float size, int hpmax, int hp);
	void Draw();
};
class EGaugeRed : public Base {
public:
	CImage m_img;
	int m_hp;
	int m_hpmax;
	int m_gauge;
	//補正値
	float m_gauge2;
	//目標値
	int m_gauge3;
	//加速度
	float m_gauge4;
public:
	EGaugeRed(const CVector2D& pos, float size, int hpmax, int hp);
	void Draw();
};
#pragma endregion
