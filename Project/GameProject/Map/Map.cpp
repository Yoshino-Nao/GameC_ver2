
#include"Map.h"
#include"AreaChange.h"
#include "../Gimmick/Door.h"
#include "../Character/Enemy.h"
#include "../Character/Player.h"
#include "../Item/Item.h"




Map::Map(int nextArea,const CVector2D& nextplayerpos) : Base(eType_Field) {
	
	//���C���[0
	m_map_tip[0] = COPY_RESOURCE("MapTip_64", CImage);
	//���C���[1
	m_map_tip[1] = COPY_RESOURCE("MapTip_64", CImage);
	
	switch (nextArea) {
	case 1:
		//fmf����}�b�v�f�[�^��ǂݍ���
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
		//�e�X�g�}�b�v�Q
		Base::Add(new AreaChange(2,					//���̃}�b�v�̔ԍ�
			CRect(m_fmfHeader.byChipWidth * 43,		//�G���A�`�F���W�̔���
				m_fmfHeader.byChipHeight * 97,		//����
				m_fmfHeader.byChipWidth * 2,		//���T�C�Y
				m_fmfHeader.byChipHeight * 2),		//�c�T�C�Y
			CVector2D(m_fmfHeader.byChipWidth * 1,	//���̃}�b�v�̍ŏ��̃v���C���[�̏ꏊ
				m_fmfHeader.byChipHeight * 16)));
		/*//�L���@����
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
		Base::Add(new AreaChange(1,					//���̃}�b�v�̔ԍ�
			CRect(m_fmfHeader.byChipWidth * 15,		//�G���A�`�F���W�̔���
				m_fmfHeader.byChipHeight * 15,		//����
				m_fmfHeader.byChipWidth * 2,		//���T�C�Y
				m_fmfHeader.byChipHeight * 2),		//�c�T�C�Y
			CVector2D(m_fmfHeader.byChipWidth * 43,	//���̃}�b�v�̍ŏ��̃v���C���[�̏ꏊ
				m_fmfHeader.byChipHeight * 99)));
		break;
	}
	
	//�v���C���[�̈ʒu����
	if (Base* p = Base::FindObject(eType_Player)) {
		p->ResetPos(nextplayerpos);
	}
	
}
Map::~Map() {
	//fmf�����
	Close();
}
#pragma region �}�b�v�`�� �����蔻��

void Map::Draw() {
	if (m_kill) return;

	/*
	//1F�̃Y�����Ȃ������߁A�`��̒��O�ŃX�N���[���l�m��
	if (Base* p = Base::FindObject(eType_Player)) {
		//�X�N���[���ݒ�
		m_scroll.x = p->m_pos.x - 600;
		m_scroll.y = p->m_pos.y - 500;
	}*/


	//�`�b�v�̐��@��s�P�U�񂩁@�P�s�Q�T�U��
	int s = pow(16, (GetLayerBitCount() / 8));

	//�\���͈͂�����@��ʂɈڂ�͈͂����`��
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
	

	//���C���[�������J��Ԃ� k=1����n�߂�Ɣ���p�̕ǂ����\�������
	for (int k = 0; k < GetLayerCount();k++) {
		//�s�Ɨ�̌J��Ԃ�
		for (int j = sy; j < ey; j++) {
			for (int i = sx; i < ex; i++) {
				//�`�b�v�̔ԍ����擾����
				int t = GetValue(k, i, j);
				//���ߔԍ��Ȃ�\�����Ȃ�
				if (t == NULL_TIP) continue;
				//�`�b�v�ԍ�����g�p����摜�̏ꏊ���v�Z
				int x = t % s;
				int y = t / s;
				//�\���ʒu�ݒ�
				m_map_tip[k].SetPos(CVector2D(m_fmfHeader.byChipWidth*i, m_fmfHeader.byChipHeight*j)-m_scroll);
				//�\����`�ݒ�
				m_map_tip[k].SetRect(x * m_fmfHeader.byChipWidth, y * m_fmfHeader.byChipHeight, (x + 1) * m_fmfHeader.byChipWidth, (y + 1) * m_fmfHeader.byChipHeight);
				//�T�C�Y�ݒ�
				m_map_tip[k].SetSize(m_fmfHeader.byChipWidth, m_fmfHeader.byChipHeight);
				//�\��
				m_map_tip[k].Draw();
				DrawRect();
			}
		}
	}
	
}

int Map::GetTip(const CVector2D& pos, int* tx, int* ty)
{
	//����v�Z
	int x = pos.x / GetChipWidth();
	//��̐���
	if (x < 0) x = 0;
	if (x > GetMapWidth() - 1) x = GetMapWidth() - 1;
	//�s���v�Z
	int y = pos.y / GetChipHeight();
	//�s�̐���
	if (y < 0) y = 0;
	if (y > GetMapHeight() - 1) y = GetMapHeight() - 1;
	//�s�Ɨ�̏o��
	if (ty) *ty = y;
	if (tx) *tx = x;
	//�`�b�v�f�[�^��ԋp�@�ǂ̔ԍ���Ԃ�
	return GetValue(1, x, y);
}

int Map::GetTip(int x, int y)
{
	return GetValue(1, x, y);
}

void Map::SetTip(const CVector2D& pos, int t)
{
	//����v�Z
	int x = pos.x / GetChipWidth();
	//��̐���(0�`MAP_WIDTH-1)
	if (x < 0)x = 0;
	if (x > GetMapWidth() - 1)x = GetMapWidth() - 1;
	//�s���v�Z
	int y = pos.y / GetChipHeight();
	//�s�̐���(0�`MAP_HEIGHT-1)
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
	//�}�b�v�`�b�v�̃T�C�Y��16�h�b�g�Ə������̂ŁA�ǔ������Ȃ��悤6�_�Ŕ���
	int tx, ty;
	//����
	int t = GetTip(CVector2D(pos.x + rect.m_left, pos.y + rect.m_top), &tx, &ty);
	if (t != NULL_TIP) {
		//�C����ʒu
		rev_pos->x = (tx + 1) * GetChipWidth() - rect.m_left + 1;
		rev_pos->y = (ty + 1) * GetChipHeight() - rect.m_top + 1;
		return t;
	}
	//�E��
	t = GetTip(CVector2D(pos.x + rect.m_right, pos.y + rect.m_top), &tx, &ty);
	if (t != NULL_TIP) {
		//�C����ʒu
		rev_pos->x = tx * GetChipWidth() - rect.m_right - 1;
		rev_pos->y = (ty + 1) * GetChipHeight() - rect.m_top + 1;
		return t;
		
	}
	
	//�^�񒆏�
	t = GetTip(CVector2D(pos.x + (rect.m_right+ rect.m_left)/2, pos.y + rect.m_top), &tx, &ty);
	if (t != NULL_TIP) {
		//�C����ʒu
		rev_pos->x = pos.x;
		rev_pos->y = (ty + 1) * GetChipHeight() - rect.m_top + 1;
		return t;
	}

	//����
	t = GetTip(CVector2D(pos.x + rect.m_left, pos.y + rect.m_bottom), &tx, &ty);
	if (t != NULL_TIP) {
		//�C����ʒu
		rev_pos->x = (tx + 1) * GetChipWidth() - rect.m_left + 1;
		rev_pos->y = ty * GetChipHeight() - rect.m_bottom - 1;
		return t;
	}
	//�E��
	t = GetTip(CVector2D(pos.x + rect.m_right, pos.y + rect.m_bottom), &tx, &ty);
	if (t != NULL_TIP) {
		//�C����ʒu
		rev_pos->x = tx * GetChipWidth() - rect.m_right - 1;
		rev_pos->y = ty * GetChipHeight() - rect.m_bottom - 1;
		return t;
	}
	
	//������
	t = GetTip(CVector2D(pos.x + (rect.m_right+ rect.m_left)/2, pos.y + rect.m_bottom), &tx, &ty);
	if (t != NULL_TIP) {
		//�C����ʒu
		rev_pos->x = pos.x;
		rev_pos->y = ty * GetChipHeight() - rect.m_bottom - 1;
		return t;
	}
	return NULL_TIP;
}
#pragma endregion

#pragma region �~�j�}�b�v
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
	//fmf�����
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
	//�~�j�}�b�v�`��͈�
	for (int j = sy; j < ey; j++) {
		for (int i = sx; i < ex; i++) {
			/*if (stage1data[i][j] == 0)continue;
			int t = stage1data[i][j];

			int t = GetValue(1, i, j);
			//�\�����Ȃ�����
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
			//�`��
			//m_img.Draw();
		}
	}

	//�}�b�v�`�b�v�ɂ��\���̌J��Ԃ�
	for (int j = 0; j < GetMapWidth(); j++) {
		for (int i = 0; i < GetMapHeight(); i++) {
			//�\�����Ȃ�����
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

			
			//�摜�؂蔲��
			m_img.SetRect(3 * t, 0, 3 * t + 3, 3);
			//�\���T�C�Y�ݒ�
			m_img.SetSize(3, 3);
			//�\���ʒu�ݒ�
			m_img.SetPos((1280 - GetMapWidth() * 3 + i * 3), (1 + j * 3));
			//�`��
			m_img.Draw();
		}
	}
}
//����
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
		//�摜�؂蔲��
		m_img.SetRect(6, 0, 6 + 3, 3);
		//�\���T�C�Y�ݒ�
		m_img.SetSize(3, 6);
		m_img.SetCenter(0, 3);
		//�\���ʒu�ݒ�
		m_img.SetPos((1280 - GetMapWidth() * 3 + px * 3), (1 + py * 3));
		//�`��
		m_img.Draw();
	}
}
#pragma endregion