#pragma once

#include "../Base/Base.h"

/// <summary>
/// エリアチェンジ用判定オブジェクト
/// </summary>
class Event : public Base {
public:
	int m_type;					//移動先のエリア番号

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="nextArea">移動先のエリア番号</param>
	/// <param name="rect">当たり判定矩形</param>
	/// <param name="nextplayerpos">移動後のプレイヤーの位置</param>
	Event(int type,const CRect& rect);

	/// <summary>
	/// デストラクタ
	/// </summary>

	~Event();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	int GetEventNum();
};