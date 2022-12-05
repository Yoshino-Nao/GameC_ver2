
#include"Map.h"
#include"AreaChange.h"

Map::Map(int nextArea,const CVector2D& nextplayerpos) : Base(eType_Field) {
	//���C���[0
	m_map_tip[0] = COPY_RESOURCE("MapTip_64", CImage);
	//���C���[1
	m_map_tip[1] = COPY_RESOURCE("MapTip_64", CImage);
	switch (nextArea) {
	case 1:
		//fmf����}�b�v�f�[�^��ǂݍ���
		Open("Map/test64.fmf");

		
		/*
		//�L���@�E��
		Base::Add(new AreaChange(2,					//���̃}�b�v�̔ԍ�
			CRect(m_fmfHeader.byChipWidth * 33,		//�G���A�`�F���W�̔���
				m_fmfHeader.byChipHeight * 14,		//����
				m_fmfHeader.byChipWidth * 1,		//���T�C�Y
				m_fmfHeader.byChipHeight * 13),		//�c�T�C�Y
			CVector2D(m_fmfHeader.byChipWidth * 1,	//���̃}�b�v�̍ŏ��̃v���C���[�̏ꏊ
				m_fmfHeader.byChipHeight * 20)));
		//�L���@����
		Base::Add(new AreaChange(4,
			CRect(m_fmfHeader.byChipWidth * 1,
				m_fmfHeader.byChipHeight * 14,
				m_fmfHeader.byChipWidth * 1,
				m_fmfHeader.byChipHeight * 13),
			CVector2D(m_fmfHeader.byChipWidth * 31,
				m_fmfHeader.byChipHeight * 20)));*/
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
/*
void Map::SetTip(const CVector2D& pos, int t)
{
	//����v�Z
	int col = pos.x / GetChipWidth();
	//��̐���(0�`MAP_WIDTH-1)
	if (col < 0)col = 0;
	if (col > GetMapWidth() - 1)col = GetMapWidth() - 1;
	//�s���v�Z
	int raw = pos.y / GetChipHeight();
	//�s�̐���(0�`MAP_HEIGHT-1)
	if (raw < 0)raw = 0;
	if (raw > GetMapHeight() - 1)raw = GetMapHeight() - 1;
	(1, raw, col) = t;
}*/

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
static int MiniMapData[100][100] = { NULL };
MiniMap::MiniMap(int nextArea) :Base(eType_UI_Front)
{
	m_img = COPY_RESOURCE("MiniMap", CImage);
	switch (nextArea)
	{
	case 1:

		Open("Map/test64.fmf");
		break;
	}

}

void MiniMap::Draw()
{
	/*
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
	*/

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

	//�~�j�}�b�v�`��͈�
	for (int j = sy; j < ey; j++) {
		for (int i = sx; i < ex; i++) {
			/*if (stage1data[i][j] == 0)continue;
			int t = stage1data[i][j];

			int t = GetValue(1, i, j);
			//�\�����Ȃ�����
			if (t == NULL_TIP) continue;
			*/
			if (GetValue(1, i, j) == NULL_TIP)continue;
			int t = GetValue(1, i, j);

			//m_fmfHeader.byChipWidth*i, m_fmfHeader.byChipHeight*j
			//MiniMapData[GetChipWidth() * i][GetChipHeight() * j] = t;
			MiniMapData[i][j] = t;
			//�`��
			//m_img.Draw();
		}
	}
	/*
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
	*/

	//�}�b�v�`�b�v�ɂ��\���̌J��Ԃ�
	for (int j = 0; j < GetMapWidth(); j++) {
		for (int i = 0; i < GetMapHeight(); i++) {
			//�\�����Ȃ�����

			if (MiniMapData[i][j] == NULL_TIP)continue;
			//int t = MiniMapData[i][j];

			int t = GetValue(1, i, j);


			//�摜�؂蔲��
			m_img.SetRect(3 * t, 0, 3 * t + 3, 3);
			//�\���T�C�Y�ݒ�
			m_img.SetSize(3, 3);
			//�\���ʒu�ݒ�
			m_img.SetPos((1280 - GetMapHeight() * 3 + i * 3), (1 + j * 3));
			//�`��
			m_img.Draw();
		}
	}
}
