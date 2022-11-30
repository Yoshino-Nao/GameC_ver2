#pragma once
#include<GLLibrary.h>
//�d�͉����x
#define GRAVITY (9.8f/20)

enum {
	eType_Scene,
	eType_Field,
	eType_Player,
	eType_Player_Bullet,
	eType_Enemy,
	eType_E_Slime1,
	eType_E_Slime2,
	eType_E_Slime3,
	eType_E_Witch1,
	eType_E_Witch2,
	eType_E_Dragon1,
	eType_Bullet,
	eType_Goal,
	eType_Door,
	eType_Player_Attack,
	eType_Enemy_Attack,
	eType_Effect,
	eType_AtkEffect,
	eType_Item,
	eType_Item_Score,
	eType_Item_LifeUp,
	eType_start,
	eType_Goal2,

	
	eType_Menu,
	eType_UI_Back,
	eType_UI_Mid,
	eType_UI_Front,
	eType_AreaChange,
};

class Base {
public:
	//���W�f�[�^
	CVector2D m_pos;
	CVector2D m_pos_old;
	static std::list<Base*> m_list;
	//�I�u�W�F�N�g�̎��
	int m_type;
	//���a
	float m_rad;
	//�ړ��x�N�g��
	CVector2D m_vec;
	//��]�l
	float m_ang;
	//�X�N���[���l
	static CVector2D m_scroll;

	bool m_kill;
	Base* Base::FindObject(int type);
	//��`
	CRect m_rect;


public:
	//type�I�u�W�F�N�g�̎��
	Base(int type);
	virtual ~Base();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Base* b);
	//�폜�t���OON
	void SetKill() { m_kill = true; }
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void ResetPos(const CVector2D& pos) {
		m_pos = m_pos_old = pos;
	}
	//�S�ẴI�u�W�F�N�g�̍X�V
	static void UpdateAll();
	//�S�ẴI�u�W�F�N�g�̕`��
	static void DrawAll();
	//�S�ẴI�u�W�F�N�g�̓�����̔��茟��
	static void CollisionAll();
	//�I�u�W�F�N�g�̒ǉ�
	static void Add(Base*b);
	//�S�I�u�W�F�N�g�̍폜
	static void KillAll();
	static void KillByType(int type);

	/// <summary>
	/// �I�u�W�F�N�g�̒ǉ�
	/// </summary>
	/// <param name="b">�ǉ�����I�u�W�F�N�g</param>
	//�~���m�̏Փ�
	static bool CollisionCircle(Base* b1, Base* b2);
	//�폜�`�F�b�N
	static void CheckKillAll();
	
	//type�̃I�u�W�F�N�g��T���i�����j
	static std::list<Base*> FindObjects(int type);

	static CVector2D GetScreenPos(const CVector2D& pos);

	//��`���m�̔���
	static bool CollisionRect(Base* b1, Base* b2);
	//��`�̕\��
	void DrawRect();
};


