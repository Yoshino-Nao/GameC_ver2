#pragma once

#include"../Base/Base.h"

class Title :public Base {
	float m_s;
	//画像オブジェクト
	CImage m_img;
	//文字表示オブジェクト
	CFont m_title_text;
public:
	Title();
	~Title();
	void Update();
	void Draw();
};
class License :public Base {
	//画像オブジェクト
	CImage m_img;
	//文字表示オブジェクト
	CFont m_title_text;
public:
	License();
	void Update();
	void Draw();
};
