#pragma once
#include<GLLibrary.h>
//重力加速度
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
	//座標データ
	CVector2D m_pos;
	CVector2D m_pos_old;
	static std::list<Base*> m_list;
	//オブジェクトの種類
	int m_type;
	//半径
	float m_rad;
	//移動ベクトル
	CVector2D m_vec;
	//回転値
	float m_ang;
	//スクロール値
	static CVector2D m_scroll;

	bool m_kill;
	Base* Base::FindObject(int type);
	//矩形
	CRect m_rect;


public:
	//typeオブジェクトの種類
	Base(int type);
	virtual ~Base();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Base* b);
	//削除フラグON
	void SetKill() { m_kill = true; }
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void ResetPos(const CVector2D& pos) {
		m_pos = m_pos_old = pos;
	}
	//全てのオブジェクトの更新
	static void UpdateAll();
	//全てのオブジェクトの描画
	static void DrawAll();
	//全てのオブジェクトの当たりの判定検証
	static void CollisionAll();
	//オブジェクトの追加
	static void Add(Base*b);
	//全オブジェクトの削除
	static void KillAll();
	static void KillByType(int type);

	/// <summary>
	/// オブジェクトの追加
	/// </summary>
	/// <param name="b">追加するオブジェクト</param>
	//円同士の衝突
	static bool CollisionCircle(Base* b1, Base* b2);
	//削除チェック
	static void CheckKillAll();
	
	//typeのオブジェクトを探索（複数）
	static std::list<Base*> FindObjects(int type);

	static CVector2D GetScreenPos(const CVector2D& pos);

	//矩形同士の判定
	static bool CollisionRect(Base* b1, Base* b2);
	//矩形の表示
	void DrawRect();
};


