
#include"Map.h"
#include"AreaChange.h"
#include "../Gimmick/Door.h"
#include"../Gimmick/BreakWall.h"
#include"../Gimmick/Event.h"
#include "../Character/Enemy.h"
#include "../Character/Player.h"
#include "../Item/Item.h"
#include"../Item/Goal.h"
#include"../Title/Title.h"


Map::Map(int nextArea,const CVector2D& nextplayerpos) : Base(eType_Field) {
	
	//レイヤー0
	m_map_tip[0] = COPY_RESOURCE("MapTip_64", CImage);
	//レイヤー1
	m_map_tip[1] = COPY_RESOURCE("MapTip_64", CImage);
	
	switch (nextArea) {
	case 1:
		//fmfからマップデータを読み込む
		Open("Map/test64.fmf");
		Base::Add(new MiniMap(nextArea));
		//Base::Add(new MiniMapPlayer(nextArea)); 64 * 45, 64 * 10
		

		/*Base::Add(new Item(CVector2D(m_fmfHeader.byChipWidth * 50,
			m_fmfHeader.byChipHeight * 10),eType_Item_Kay1));
		Base::Add(new Item(CVector2D(m_fmfHeader.byChipWidth * 53,
			m_fmfHeader.byChipHeight * 10), eType_Item_Kay2));
		Base::Add(new Item(CVector2D(m_fmfHeader.byChipWidth * 56,
			m_fmfHeader.byChipHeight * 10), eType_Item_Kay3));*/
		Base::Add(new Door(CVector2D(
			m_fmfHeader.byChipWidth * 26,
			m_fmfHeader.byChipHeight * 45),
			1));
		Base::Add(new Door(CVector2D(
			m_fmfHeader.byChipWidth * 60,
			m_fmfHeader.byChipHeight * 45),
			1));

		/*Base::Add(new Door(CVector2D(
			m_fmfHeader.byChipWidth * 7,
			m_fmfHeader.byChipHeight * 45),
			2));*/
		Base::Add(new Door(CVector2D(
			m_fmfHeader.byChipWidth * 108,
			m_fmfHeader.byChipHeight * 53),
			2));
		Base::Add(new Door(CVector2D(
			m_fmfHeader.byChipWidth * 98,
			m_fmfHeader.byChipHeight * 21),
			2));
		Base::Add(new Door(CVector2D(
			m_fmfHeader.byChipWidth * 108,
			m_fmfHeader.byChipHeight * 11), 
			3));
		for (int i = 0; i <= 31; i++) {
			Base::Add(new BreakWall(0, CVector2D(
				m_fmfHeader.byChipWidth * (27 + i),
				m_fmfHeader.byChipHeight * 39)));
		}
		
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 40,
			m_fmfHeader.byChipHeight * 37), true, eType_E_Slime1));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 42,
			m_fmfHeader.byChipHeight * 37), true, eType_E_Slime1));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 44,
			m_fmfHeader.byChipHeight * 37), true, eType_E_Slime1));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 31,
			m_fmfHeader.byChipHeight * 98), true, eType_E_Slime2));

		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 23,
			m_fmfHeader.byChipHeight * 64), true, eType_E_Slo));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 10,
			m_fmfHeader.byChipHeight * 50), false, eType_E_Slo));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 18,
			m_fmfHeader.byChipHeight * 50), false, eType_E_Slo));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 28,
			m_fmfHeader.byChipHeight * 49), false, eType_E_Slo));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 28,
			m_fmfHeader.byChipHeight * 52), false, eType_E_Slo));

		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 5 + 32,
			m_fmfHeader.byChipHeight * 19), eType_Item_Kay1));
		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 28 + 32,
			m_fmfHeader.byChipHeight * 38), eType_Item_Kay1));
		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 49 + 32,
			m_fmfHeader.byChipHeight * 53), eType_Item_Kay2));
		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 111 + 32,
			m_fmfHeader.byChipHeight * 53), eType_Item_Kay2));
		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 97 + 32,
			m_fmfHeader.byChipHeight * 23), eType_Item_Kay3));
		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 104 + 32,
			m_fmfHeader.byChipHeight * 44), eType_Item_AirJump));
		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 55 + 32,
			m_fmfHeader.byChipHeight * 45), eType_Item_Sword));
		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 5 + 32,
			m_fmfHeader.byChipHeight * 68), eType_Item_Gun));
		Base::Add(new Event(0,
			CRect(m_fmfHeader.byChipWidth * 55,
				m_fmfHeader.byChipHeight * 45,
				m_fmfHeader.byChipWidth * 2,
				m_fmfHeader.byChipHeight * 2)));
		//テストマップ２
		Base::Add(new AreaChange(2,					//次のマップの番号
			CRect(m_fmfHeader.byChipWidth * 117,		//エリアチェンジの判定
				m_fmfHeader.byChipHeight * 10,		//左上
				m_fmfHeader.byChipWidth * 2,		//横サイズ
				m_fmfHeader.byChipHeight * 2),		//縦サイズ
			CVector2D(m_fmfHeader.byChipWidth * 1,	//次のマップの最初のプレイヤーの場所
				m_fmfHeader.byChipHeight * 16)));
		/*//廊下　左へ
		Base::Add(new AreaChange(4,
			CRect(m_fmfHeader.byChipWidth * 1,
				m_fmfHeader.byChipHeight * 14,
				m_fmfHeader.byChipWidth * 1,
				m_fmfHeader.byChipHeight * 13),
			CVector2D(m_fmfHeader.byChipWidth * 31,
				m_fmfHeader.byChipHeight * 20)));*/
		break;
	case 2:
		//Open("Map/test64(2).fmf");
		Base::Add(new MiniMap(nextArea));

		/*Base::Add(new Goal(CVector2D(m_fmfHeader.byChipWidth * 8,
			m_fmfHeader.byChipHeight * 16)));*/

		if (Base::FindObject(eType_Player)) {
			Base::KillAll();
			//ゲームシーンへ
			Base::Add(new Title());
			Base::Add(new License());
		}
		//Base::Add(new MiniMapPlayer(nextArea));
		//Base::Add(new AreaChange(1,					//次のマップの番号
		//	CRect(m_fmfHeader.byChipWidth * 15,		//エリアチェンジの判定
		//		m_fmfHeader.byChipHeight * 15,		//左上
		//		m_fmfHeader.byChipWidth * 2,		//横サイズ
		//		m_fmfHeader.byChipHeight * 2),		//縦サイズ
		//	CVector2D(m_fmfHeader.byChipWidth * 43,	//次のマップの最初のプレイヤーの場所
		//		m_fmfHeader.byChipHeight * 99)));
		//break;
	}
	
	//プレイヤーの位置決定
	if (Base* p = Base::FindObject(eType_Player)) {
		p->ResetPos(nextplayerpos);
	}
	
}
Map::~Map() {
	//fmfを閉じる
	Close();
}
#pragma region マップ描画 当たり判定

void Map::Draw() {
	if (m_kill) return;

	/*
	//1Fのズレをなくすため、描画の直前でスクロール値確定
	if (Base* p = Base::FindObject(eType_Player)) {
		//スクロール設定
		m_scroll.x = p->m_pos.x - 600;
		m_scroll.y = p->m_pos.y - 500;
	}*/


	//チップの数　一行１６列か　１行２５６列か
	int s = pow(16, (GetLayerBitCount() / 8));

	//表示範囲を限定　画面に移る範囲だけ描画
	int col = CCamera::GetCurrent()->GetWhidth() / GetChipWidth()+2;
	int row = CCamera::GetCurrent()->GetHeight() / GetChipHeight()+2;
	
	int sx = m_scroll.x / GetChipWidth();
	if (sx < 0) sx = 0;
	int ex = sx + col;
	if (ex > GetMapWidth())ex = GetMapWidth();

	int sy = m_scroll.y / GetChipHeight();
	if (sy < 0) sy = 0;
	int ey = sy + row;
	if (ey > GetMapHeight())ey = GetMapHeight();
	

	//レイヤー数だけ繰り返す k=1から始めると判定用の壁だけ表示される
	for (int k = 0; k < GetLayerCount();k++) {
		//行と列の繰り返し
		for (int j = sy; j < ey; j++) {
			for (int i = sx; i < ex; i++) {
				//チップの番号を取得する
				int t = GetValue(k, i, j);
				//透過番号なら表示しない
				if (t == NULL_TIP) continue;
				//チップ番号から使用する画像の場所を計算
				int x = t % s;
				int y = t / s;
				//表示位置設定
				m_map_tip[k].SetPos(CVector2D(m_fmfHeader.byChipWidth*i, m_fmfHeader.byChipHeight*j)-m_scroll);
				//表示矩形設定
				m_map_tip[k].SetRect(x * m_fmfHeader.byChipWidth, y * m_fmfHeader.byChipHeight, (x + 1) * m_fmfHeader.byChipWidth, (y + 1) * m_fmfHeader.byChipHeight);
				//サイズ設定
				m_map_tip[k].SetSize(m_fmfHeader.byChipWidth, m_fmfHeader.byChipHeight);
				//表示
				m_map_tip[k].Draw();
				DrawRect();
			}
		}
	}
	
}

int Map::GetTip(const CVector2D& pos, int* tx, int* ty)
{
	//列を計算
	int x = pos.x / GetChipWidth();
	//列の制限
	if (x < 0) x = 0;
	if (x > GetMapWidth() - 1) x = GetMapWidth() - 1;
	//行を計算
	int y = pos.y / GetChipHeight();
	//行の制限
	if (y < 0) y = 0;
	if (y > GetMapHeight() - 1) y = GetMapHeight() - 1;
	//行と列の出力
	if (ty) *ty = y;
	if (tx) *tx = x;
	//チップデータを返却　壁の番号を返す
	return GetValue(1, x, y);
}

int Map::GetTip(int x, int y)
{
	return GetValue(1, x, y);
}

void Map::SetTip(const CVector2D& pos, int t)
{
	//列を計算
	int x = pos.x / GetChipWidth();
	//列の制限(0〜MAP_WIDTH-1)
	if (x < 0)x = 0;
	if (x > GetMapWidth() - 1)x = GetMapWidth() - 1;
	//行を計算
	int y = pos.y / GetChipHeight();
	//行の制限(0〜MAP_HEIGHT-1)
	if (y < 0)y = 0;
	if (y > GetMapHeight() - 1)y = GetMapHeight() - 1;
	//if (ty) *ty = y;
	//if (tx) *tx = x;
	SetValue(1, x, y, t);
}

int Map::CollisionMap(const CVector2D& pos)
{
	return GetTip(pos);
}

int Map::CollisionMap(const CVector2D& pos, const CRect& rect, CVector2D* rev_pos)
{
	//マップチップのサイズが16ドットと小さいので、壁抜けしないよう6点で判定
	int tx, ty;
	//左上
	int t = GetTip(CVector2D(pos.x + rect.m_left, pos.y + rect.m_top), &tx, &ty);
	if (t != NULL_TIP) {
		//修正後位置
		rev_pos->x = (tx + 1) * GetChipWidth() - rect.m_left + 1;
		rev_pos->y = (ty + 1) * GetChipHeight() - rect.m_top + 1;
		return t;
	}
	//右上
	t = GetTip(CVector2D(pos.x + rect.m_right, pos.y + rect.m_top), &tx, &ty);
	if (t != NULL_TIP) {
		//修正後位置
		rev_pos->x = tx * GetChipWidth() - rect.m_right - 1;
		rev_pos->y = (ty + 1) * GetChipHeight() - rect.m_top + 1;
		return t;
		
	}
	
	//真ん中上
	t = GetTip(CVector2D(pos.x + (rect.m_right+ rect.m_left)/2, pos.y + rect.m_top), &tx, &ty);
	if (t != NULL_TIP) {
		//修正後位置
		rev_pos->x = pos.x;
		rev_pos->y = (ty + 1) * GetChipHeight() - rect.m_top + 1;
		return t;
	}

	//左下
	t = GetTip(CVector2D(pos.x + rect.m_left, pos.y + rect.m_bottom), &tx, &ty);
	if (t != NULL_TIP) {
		//修正後位置
		rev_pos->x = (tx + 1) * GetChipWidth() - rect.m_left + 1;
		rev_pos->y = ty * GetChipHeight() - rect.m_bottom - 1;
		return t;
	}
	//右下
	t = GetTip(CVector2D(pos.x + rect.m_right, pos.y + rect.m_bottom), &tx, &ty);
	if (t != NULL_TIP) {
		//修正後位置
		rev_pos->x = tx * GetChipWidth() - rect.m_right - 1;
		rev_pos->y = ty * GetChipHeight() - rect.m_bottom - 1;
		return t;
	}
	
	//中央下
	t = GetTip(CVector2D(pos.x + (rect.m_right+ rect.m_left)/2, pos.y + rect.m_bottom), &tx, &ty);
	if (t != NULL_TIP) {
		//修正後位置
		rev_pos->x = pos.x;
		rev_pos->y = ty * GetChipHeight() - rect.m_bottom - 1;
		return t;
	}
	return NULL_TIP;
}
#pragma endregion

#pragma region ミニマップ
//static int MiniMapData[100][100] = { NULL };
//static int MiniMapData1[18][18] = { NULL };
MiniMap::MiniMap(int nextArea) :Base(eType_MiniMapBack)
{
	//マップエディタと合わせる
	MiniMapData[120][100] = { NULL };
	MiniMapData1[18][18] = { NULL };
	m_mapnum = nextArea;
	x = 0;
	y = 0;
	s = 0;
	m_img = COPY_RESOURCE("MiniMap", CImage);
	switch (nextArea)
	{
	case 1:
		Open("Map/test64.fmf");

		break;
	case 2:
		Open("Map/test64(2).fmf");
		break;
	}

}

MiniMap::~MiniMap()
{
	//fmfを閉じる
	Close();
}

void MiniMap::Draw()
{
	
	int col = CCamera::GetCurrent()->GetWhidth() / GetChipWidth() + 2;
	int row = CCamera::GetCurrent()->GetHeight() / GetChipHeight() + 2;

	int sx = m_scroll.x / GetChipWidth();
	if (sx < 0) sx = 0;
	int ex = sx + col;
	if (ex > GetMapWidth())ex = GetMapWidth();

	int sy = m_scroll.y / GetChipHeight();
	if (sy < 0) sy = 0;
	int ey = sy + row;
	if (ey > GetMapHeight())ey = GetMapHeight();

	//int* p;
	
	//p = &MiniMapData[0][0];
	//ミニマップ描画範囲
	
	for (int j = sy; j < ey; j++) {
		for (int i = sx; i < ex; i++) {
			/*if (stage1data[i][j] == 0)continue;
			int t = stage1data[i][j];

			int t = GetValue(1, i, j);
			//表示しない制御
			if (t == NULL_TIP) continue;
			*/
			if (GetValue(1, i, j) == NULL_TIP || sy == 0 || sy == GetMapHeight())continue;
			int t = GetValue(1, i, j);

			//m_fmfHeader.byChipWidth*i, m_fmfHeader.byChipHeight*j
			//MiniMapData[GetChipWidth() * i][GetChipHeight() * j] = t;
			switch (m_mapnum)
			{
			case 1:
				MiniMapData[i][j] = t;
				break;
			case 2:
				MiniMapData1[i][j] = t;
				break;
			}
			
			//*p[i][j] = t;
			//ctrl k ctrl c
			//描画
			//m_img.Draw();
		}
	}
	//ミニマップ描画範囲設定
	if (HOLD(CInput::eButton5)) {
		ex = GetMapWidth();
		ey = GetMapHeight();
		sx = 0;
		sy = 0;

		//ミニマップ表示位置(拡大表示)
		//横
		x = (CCamera::GetCurrent()->GetWhidth() / GetMapWidth()) * 6;
		//縦
		y = (CCamera::GetCurrent()->GetHeight() / GetChipHeight()) * 12;
		//y = 150;
		s = 4;
	}
	else {
		ex = min(GetMapWidth(), ex + 20);
		ey = min(GetMapHeight(), ey + 5);
		//ミニマップ表示位置(縮小表示)
		//横
		x = 1;
		//縦
		y = 25;
		//サイズ
		s = 8;
	}
	sy = max(0, sy - 10);
	m_img.DrawBegin();
	//マップチップデータによる表示の繰り返し
	for (int j = sy; j < ey; j++) {
		for (int i = sx; i < ex; i++) {
			//表示しない制御
			switch (m_mapnum)
			{
			case 1:
				if (MiniMapData[i][j] == NULL_TIP)continue;
				break;
			case 2:
				if (MiniMapData1[i][j] == NULL_TIP)continue;
				break;
			}
			//if (MiniMapData[i][j] == NULL_TIP)continue;
			//int t = MiniMapData[i][j];
			int t = GetValue(1, i, j);
			//画像切り抜き
			m_img.SetRect(3 * 1, 0, 3 * 1 + 3, 3);
			//表示サイズ設定
			m_img.SetSize(s, s);
			//表示位置設定
			m_img.SetPos((CCamera::GetCurrent()->GetWhidth() - (ex + x) * s) + i * s, ((-ey + y) * s) + j * s);
			//描画
			m_img.DrawS();
			//プレイヤー表示
			Base* p = Base::FindObject(eType_Player);
			Player* h = dynamic_cast<Player*>(p);
			if (p) {
				CVector2D Ppos = h->m_pos;
				//m_Ppos = h->GetPos();
				int px = Ppos.x / GetChipWidth();
				int py = Ppos.y / GetChipHeight();
				abs(px), abs(py);
				//画像切り抜き
				m_img.SetRect(6, 0, 6 + 3, 3);
				//表示サイズ設定
				m_img.SetSize(s, s * 2);
				m_img.SetCenter(0, s);
				//表示位置設定
				//m_img.SetPos((CCamera::GetCurrent()->GetWhidth() - (ex + 20) * s) + i * s, ((-ey + 25) * s) + j * s);
				m_img.SetPos((CCamera::GetCurrent()->GetWhidth() - (ex + x) * s) + px * s, ((-ey + y) * s) + py * s - s);
				//描画
				m_img.DrawS();
			}
			//bがlist型
			auto d = Base::FindObjects(eType_Door);
			for (auto& b : d) {
				Door* j = dynamic_cast<Door*>(b);
				CVector2D Dpos = j->m_pos;
				int px = Dpos.x / GetChipWidth();
				int py = Dpos.y / GetChipHeight();
				abs(px), abs(py);
				//画像切り抜き
				m_img.SetRect(9, 0, 9 + 3, 3);
				//表示サイズ設定
				m_img.SetSize(s * 2, s * 2);
				m_img.SetCenter(0, s);
				//表示位置設定
				//m_img.SetPos((CCamera::GetCurrent()->GetWhidth() - (ex + 20) * s) + i * s, ((-ey + 25) * s) + j * s);
				m_img.SetPos((CCamera::GetCurrent()->GetWhidth() - (ex + x) * s) + px * s - 6, ((-ey + y)* s) + py * s - s);
				//描画
				m_img.DrawS();
			}
		}
	}
	m_img.DrawEnd();
	//FONT_T()->Draw(100, 200, 1, 1, 1, "sx%d", sx);
	//FONT_T()->Draw(100, 300, 1, 1, 1, "ex%d", ex);
	//FONT_T()->Draw(100, 400, 1, 1, 1, "sy%d", sy);
	//FONT_T()->Draw(100, 500, 1, 1, 1, "ey%d", ey);
}
//実体を定義
int MiniMap::MiniMapData[120][100];
int MiniMap::MiniMapData1[18][18];

#pragma endregion