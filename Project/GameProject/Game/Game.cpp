#include "Game.h"
#include "Field.h"
#include "../Item/Goal.h"
#include "../Item/start.h"
#include "../Item/Goal2.h"
#include "Map.h"
#include "GameData.h"
#include "../UI/UI.h"
#include "../UI/Gauge.h"
#include "../Character/Player.h"
#include "../Character/Enemy.h"
#include "../Item/Item.h"
#include "../Title/Title.h"
#include "../Attack/Attack.h"
#include "../Gimmick/Door.h"
#include <iostream>

Game::Game() :Base(eType_Scene)
{
	//Base::Add(new Field());
	Base::Add(new Map());
	Base::Add(new Player(CVector2D(MAP_TIP_SIZE * 98 + MAP_TIP_SIZE / 2, MAP_TIP_SIZE * 23 - 1), false));
	//Base::Add(new Attack(CVector2D(1280, 560), false));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
	//Base::Add(new Goal(CVector2D(0, 0)));
	Base::Add(new Enemy(CVector2D(MAP_TIP_SIZE * 16 + MAP_TIP_SIZE / 2, MAP_TIP_SIZE * 7 - 1), false, eType_E_Slime1));
	Base::Add(new Enemy(CVector2D(MAP_TIP_SIZE * 17 + MAP_TIP_SIZE / 2, MAP_TIP_SIZE * 7 - 1), false, eType_E_Slime1));
	Base::Add(new Enemy(CVector2D(MAP_TIP_SIZE * 18 + MAP_TIP_SIZE / 2, MAP_TIP_SIZE * 7 - 1), false, eType_E_Slime1));
	Base::Add(new Enemy(CVector2D(MAP_TIP_SIZE * 19 + MAP_TIP_SIZE / 2, MAP_TIP_SIZE * 7 - 1), false, eType_E_Slime1));
	Base::Add(new Enemy(CVector2D(MAP_TIP_SIZE * 20 + MAP_TIP_SIZE / 2, MAP_TIP_SIZE * 7 - 1), false, eType_E_Slime1));
	//Base::Add(new Item_Score(CVector2D(MAP_TIP_SIZE * 4, MAP_TIP_SIZE * 6)));
	Base::Add(new Door(CVector2D(MAP_TIP_SIZE * 24 + MAP_TIP_SIZE / 2, MAP_TIP_SIZE * 6)));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), false,eType_Enemy2));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), false,eType_Enemy3));
	Base::Add(new Enemy(CVector2D(MAP_TIP_SIZE * 32 + MAP_TIP_SIZE / 2, MAP_TIP_SIZE * 6 - 1), false, eType_E_Witch1));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 15, 1000), true, eType_Enemy5));
	Base::Add(new Goal(CVector2D(1258, 2950)));
	//Base::Add(new Item(CVector2D(2048, 940)));
	Base::Add(new start(CVector2D(1200, 600)));
	//Base::Add(new Goal2(CVector2D(1300, 600)));
	Base::Add(new UI());
	Base::Add(new GaugeBack());
	Base::Add(new GaugeRed());
	Base::Add(new GaugeGreen());
	Base::Add(new MiniMap());
	GameData::s_score = 0;
	GameData::s_time = 60 * 60 * 10;
	
}


Game::~Game()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	Base::Add(new Title());
}

void Game::Update()
{
	//std::cout << "game" << std::endl;
	//ゴールがなければゲームシーン終了
	if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}
	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}
