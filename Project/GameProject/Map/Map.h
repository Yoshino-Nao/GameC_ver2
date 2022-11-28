#pragma once

#include"../Base/Base.h"
//�}�b�v�̉��̃`�b�v��
#define MAP_WIDTH    128
//�}�b�v�̏c�̃`�b�v��
#define MAP_HEIGHT   128
//�}�b�v�`�b�v�̑傫��
#define MAP_TIP_SIZE 64

class Map :public Base {
private:
	CImage m_img;

public:
	Map();
	void Draw();
	//�w����W�̃`�b�v�ԍ����擾
	int GetTip(const CVector2D& pos);
	//�w���A�w��s�̃}�b�v�`�b�v���擾
	int GetTip(int col, int raw);
	void SetTip(const CVector2D& pos, int t);
	//�}�b�v�Ƃ̓����蔻��
	//int CollisionMap(const CVector2D& pos);
	int CollisionMap(const CVector2D& pos);
	int CollisionMap(const CVector2D& pos, const CRect& rect);
};
class MiniMap :public Base {
private:
	CImage m_img;
	int sx, sy, ex, ey, sxmin, symin, exold, eyold;
public:
	
	MiniMap();
	void Draw();
};