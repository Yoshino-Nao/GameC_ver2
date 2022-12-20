
#include"Map.h"
#include"AreaChange.h"
#include "../Gimmick/Door.h"
#include "../Character/Enemy.h"
#include "../Character/Player.h"
#include "../Item/Item.h"




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
		Base::Add(new MiniMapPlayer(nextArea));
		
		Base::Add(new Door(CVector2D(
			m_fmfHeader.byChipWidth * 36,
			m_fmfHeader.byChipHeight * 98),
			0));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 30,
			m_fmfHeader.byChipHeight * 98), false, eType_E_Slime1));
		/*Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 31,
			m_fmfHeader.byChipHeight * 98), false, eType_E_Slime2));
		Base::Add(new Enemy(CVector2D(
			m_fmfHeader.byChipWidth * 32,
			m_fmfHeader.byChipHeight * 98), false, eType_E_Slime3));*/
		Base::Add(new Item(CVector2D(
			m_fmfHeader.byChipWidth * 26,
			m_fmfHeader.byChipHeight * 94), eType_Item_Score));
		//テストマップ２
		Base::Add(new AreaChange(2,					//次のマップの番号
			CRect(m_fmfHeader.byChipWidth * 43,		//エリアチェンジの判定
				m_fmfHeader.byChipHeight * 97,		//左上
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
		Open("Map/test64(2).fmf");
		Base::Add(new MiniMap(nextArea));
		Base::Add(new MiniMapPlayer(nextArea));
		Base::Add(new AreaChange(1,					//次のマップの番号
			CRect(m_fmfHeader.byChipWidth * 15,		//エリアチェンジの判定
				m_fmfHeader.byChipHeight * 15,		//左上
				m_fmfHeader.byChipWidth * 2,		//横サイズ
				m_fmfHeader.byChipHeight * 2),		//縦サイズ
			CVector2D(m_fmfHeader.byChipWidth * 43,	//次のマップの最初のプレイヤーの場所
				m_fmfHeader.byChipHeight * 99)));
		break;
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
	//列の制限(0～MAP_WIDTH-1)
	if (x < 0)x = 0;
	if (x > GetMapWidth() - 1)x = GetMapWidth() - 1;
	//行を計算
	int y = pos.y / GetChipHeight();
	//行の制限(0～MAP_HEIGHT-1)
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
	MiniMapData[100][100] = { NULL };
	MiniMapData1[18][18] = { NULL };
	m_mapnum = nextArea;
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
			if (GetValue(1, i, j) == NULL_TIP || sy == 0)continue;
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

	//マップチップによる表示の繰り返し
	for (int j = 0; j < GetMapWidth(); j++) {
		for (int i = 0; i < GetMapHeight(); i++) {
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
			m_img.SetRect(3 * t, 0, 3 * t + 3, 3);
			//表示サイズ設定
			m_img.SetSize(3, 3);
			//表示位置設定
			m_img.SetPos((1280 - GetMapWidth() * 3 + i * 3), (1 + j * 3));
			//描画
			m_img.Draw();
		}
	}
}
//実体
int MiniMap::MiniMapData[100][100];
int MiniMap::MiniMapData1[18][18];
MiniMapPlayer::MiniMapPlayer(int nextArea)
	:Base(eType_MiniMapFront)
{
	m_img = COPY_RESOURCE("MiniMap", CImage);
	m_Ppos = CVector2D(0, 0);
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

MiniMapPlayer::~MiniMapPlayer()
{
	Close();
}

void MiniMapPlayer::Draw()
{
	Base* p = Base::FindObject(eType_Player);
	Player* h = dynamic_cast<Player*>(p);
	if (p) {
		m_Ppos = h->GetPos();
		int px = m_Ppos.x / GetChipWidth();
		int py = m_Ppos.y / GetChipHeight();
		abs(px), abs(py);
		//画像切り抜き
		m_img.SetRect(6, 0, 6 + 3, 3);
		//表示サイズ設定
		m_img.SetSize(3, 6);
		m_img.SetCenter(0, 3);
		//表示位置設定
		m_img.SetPos((1280 - GetMapWidth() * 3 + px * 3), (1 + py * 3));
		//描画
		m_img.Draw();
	}
}
#pragma endregion