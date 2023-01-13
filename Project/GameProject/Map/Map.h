#pragma once

#include"../Base/Base.h"
#include "fmfmap.h"

//透明チップ番号
#define NULL_TIP 0

/// <summary>
/// マップチップによるマップクラス
/// </summary>
class Map : public Base, CFmfMap {
private:

	CImage m_map_tip[2];		//画像オブジェクト
	CImage m_backGround;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="nextArea">生成するエリア番号</param>
	/// <param name="nextplayerpos">プレイヤーの開始位置</param>
	Map(int nextArea, const CVector2D& nextplayerpos);
	~Map();
	void Draw();

	/// 指定した座標のチップ番号を取得
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="tx">(out)列</param>
	/// <param name="ty">(out)行</param>
	/// <returns></returns>
	int GetTip(const CVector2D& pos, int* tx = nullptr, int* ty = nullptr);

	void SetTip(const CVector2D& pos, int t);

	/// <summary>
	/// 指定した行と列のチップ番号を取得
	/// </summary>
	/// <param name="x">行</param>
	/// <param name="y">列</param>
	/// <returns></returns>
	int GetTip(int x, int y);

	/// <summary>
	/// マップとの判定
	/// </summary>
	/// <param name="pos">位置</param>
	/// <returns>衝突したチップ番号</returns>
	int CollisionMap(const CVector2D& pos);

	/// <summary>
	/// マップとの判定
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="pos">矩形</param>
	/// <param name="rev_pos">衝突後、修正した位置</param>
	/// <returns>衝突したチップ番号</returns>
	int CollisionMap(const CVector2D& pos, const CRect& rect, CVector2D* rev_pos);
};
class MiniMap :public Base, CFmfMap {
private:
	CImage m_img;
	int m_mapnum;
	int x;
	int y;
	int s;
public:
	static int MiniMapData[120][100];
	static int MiniMapData1[18][18];
	MiniMap(int nextArea);
	~MiniMap();
	void Draw();
};
