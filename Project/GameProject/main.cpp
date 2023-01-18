//ゲーム係機能のインクルード
#include <GLLibrary.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include "Base/Base.h"
#include "Game/AnimData.h"
#include "Character/Enemy.h"
#include "Character/Player.h"
#include "UI/UI.h"
#include "UI/Gauge.h"
#include "Game/GameData.h"
#include "Title/Title.h"
#include "Item/start.h"
#include "Item/Goal2.h"
#include "UI/Menu.h"

//--------------------------------------------
//グローバル変数領域
//--------------------------------------------

void MainLoop(void) {
	//--------------------------------------------------------------
	//ゲーム中の動きはここに書く
	//ゲーム中はこの関数_を1秒間に60回呼び出している
	//--------------------------------------------------------------
	Base::UpdateAll();
	Base::CheckKillAll();
	Base::CollisionAll();
	Base::DrawAll();


}
void Init(void)
{

	CFPS::SetFPS(60);
	//フレーム制御初期化
	CFPS::Init();
	//ボタンの設定
	CInput::Init();//1:攻撃 2:ジャンプ 3:決定 4:キャンセル 5:ミニマップ表示 :6銃 10:ゲームスタート
	CInput::SetButton(0, CInput::eButton4, 'Z');
	CInput::SetButton(0, CInput::eButton3, 'X');
	CInput::SetButton(0, CInput::eButton2, 'C');
	CInput::SetButton(0, CInput::eButton1, 'V');
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton7, 'A');
	CInput::SetButton(0, CInput::eButton6, 'S');
	CInput::SetButton(0, CInput::eButton8, 'D');
	CInput::SetButton(0, CInput::eButton9, 'F');
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eUp, VK_UP);
	CInput::SetButton(0, CInput::eDown, VK_DOWN);
	CInput::SetButton(0, CInput::eLeft, VK_LEFT);
	CInput::SetButton(0, CInput::eRight, VK_RIGHT);
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);
	DIJOYSTATE2* pad = CInput::GetPadData(0);

	//	CInput::SetMouseInside(true);
	//	CInput::ShowCursor(false);
	CInput::Update();
	//CInput::Update();



	SetCurrentDirectory("data");
	CSound::GetInstance();

	//-----------------------------------------------------
	//初期化の命令を書く
	//ゲーム起動時に一度だけ呼ばれる
	//-----------------------------------------------------
	
	//画像の読み込みと登録
	ADD_RESOURCE("Player", CImage::CreateImage("Image/Player2.png", uni_anim_data,194, 194));
	ADD_RESOURCE("Slime1", CImage::CreateImage("Image/Slime.png", enemy_anim_data, 48, 48));
	ADD_RESOURCE("Slime2", CImage::CreateImage("Image/Slime2.png", enemy_anim_data, 48, 48));
	ADD_RESOURCE("Slime3", CImage::CreateImage("Image/Slime3.png", enemy_anim_data, 48, 48));
	ADD_RESOURCE("Witch1", CImage::CreateImage("Image/Witch.png", enemy_witch_anim_data, 131,132));
	ADD_RESOURCE("Witch2", CImage::CreateImage("Image/Witch2.png", enemy_witch_anim_data, 131, 132));
	ADD_RESOURCE("Dragon1", CImage::CreateImage("Image/Dragon.png", enemy_Dragon_anim_data, 230, 150));
	ADD_RESOURCE("Effect_Slash", CImage::CreateImage("Image/Effect_Slash.png", effect_slash_anim_data, 128, 128));
	ADD_RESOURCE("Effect_Smoke", CImage::CreateImage("Image/Effect_Smoke.png", effect_smoke_anim_data, 128, 128));
	ADD_RESOURCE("Effect_Blood", CImage::CreateImage("Image/Effect_Blood.png", effect_blood_anim_data, 128, 128));
	ADD_RESOURCE("Effect_Flame", CImage::CreateImage("Image/Effect_Flame.png", effect_flame_anim_data, 1080, 320));
	ADD_RESOURCE("Effect_Ring", CImage::CreateImage("Image/Effect_Ring.png", effect_ring_anim_data, 160, 720));
	//ADD_RESOURCE("Effect_Ring_yoko", CImage::CreateImage("Image/Effect_Ring_yoko.png", effect_ring_anim_data, 720, 160));
	ADD_RESOURCE("Effect_Ring2", CImage::CreateImage("Image/Effect_Ring_2.png", effect_ring_anim_data, 240, 720));
	ADD_RESOURCE("Effect_Spiral", CImage::CreateImage("Image/Effect_Spiral.png", effect_ring_anim_data, 540, 720));
	ADD_RESOURCE("coin", CImage::CreateImage("Image/coin.png", effect_coin_anim_data, 640, 1080));
	//ADD_RESOURCE("Effect_Kira", CImage::CreateImage("Image/Effect_kirakira.png", effect_ring_anim_data, 360, 360));
	ADD_RESOURCE("Goal", CImage::CreateImage("Image/Door.png"));
	ADD_RESOURCE("Goal2", CImage::CreateImage("Image/Goal2.png"));
	ADD_RESOURCE("Sky", CImage::CreateImage("Image/Sky.png"));
	ADD_RESOURCE("Town", CImage::CreateImage("Image/Town.png"));
	ADD_RESOURCE("ForeGround", CImage::CreateImage("Image/ForeGround.png"));
	ADD_RESOURCE("MapTip", CImage::CreateImage("Image/MapTip.bmp"));
	ADD_RESOURCE("MapTip_64", CImage::CreateImage("Image/MapTip(64).bmp"));
	ADD_RESOURCE("MiniMap", CImage::CreateImage("Image/MiniMap.png"));
	//ADD_RESOURCE("MiniMap_Back", CImage::CreateImage("Image/MiniMap_BackGround.png"));
	ADD_RESOURCE("Title", CImage::CreateImage("Image/Title.png"));
	ADD_RESOURCE("Door", CImage::CreateImage("Image/Door.png"));
	ADD_RESOURCE("License", CImage::CreateImage("Image/Light_Frame.png"));
	ADD_RESOURCE("start", CImage::CreateImage("Image/start.png"));
	ADD_RESOURCE("ball", CImage::CreateImage("Image/ball.png"));
	ADD_RESOURCE("GaugeW", CImage::CreateImage("Image/-5.png"));
	ADD_RESOURCE("GaugeE", CImage::CreateImage("Image/-4.png"));
	ADD_RESOURCE("bullet", CImage::CreateImage("Image/bullet.png"));
	ADD_RESOURCE("Sword", CImage::CreateImage("Image/Sword.png"));
	ADD_RESOURCE("Key", CImage::CreateImage("Image/Key.png"));
	ADD_RESOURCE("Lattice", CImage::CreateImage("Image/a.png"));
//ADD_RESOURCE("Item", CImage::CreateImage("Image/Item.png"));
	/*//プレイヤーの生成
	Base::Add(new Player(CVector2D(200, 500), false));
	//フィールドの生成
	Base::Add(new Field());
	//敵の生成
	Base::Add(new Enemy(CVector2D(800, 500), true));
	*/
	Base::Add(new Title());
	Base::Add(new License());
	//Base::Add(new UI());
	/*
	//画像の事前読み込み
	ADD_RESOURCE("Title", CImage::CreateImage("Image/Title.png"));
	ADD_RESOURCE("MapTip", CImage::CreateImage("Image/MapTip.png"));
	ADD_RESOURCE("Dungeon", CImage::CreateImage("Image/Dungeon.png"));
	ADD_RESOURCE("Sky", CImage::CreateImage("Image/Sky.png"));
	ADD_RESOURCE("Town", CImage::CreateImage("Image/Town.png"));
	ADD_RESOURCE("ForeGround", CImage::CreateImage("Image/ForeGround.png"));
	ADD_RESOURCE("Door", CImage::CreateImage("Image/Door.png"));
	ADD_RESOURCE("Goal", CImage::CreateImage("Image/Goal.png"));
	ADD_RESOURCE("Player", CImage::CreateImage("Image/Player.png", player_anim_data, 256, 256));
	ADD_RESOURCE("Enemy", CImage::CreateImage("Image/Enemy.png", enemy_anim_data, 256, 256));
	ADD_RESOURCE("Effect_Slash", CImage::CreateImage("Image/Effect_Slash.png", effect_slash_anim_data, 128, 128));
	ADD_RESOURCE("Effect_Smoke", CImage::CreateImage("Image/Effect_Smoke.png", effect_smoke_anim_data, 128, 128));
	ADD_RESOURCE("Effect_Blood", CImage::CreateImage("Image/Effect_Blood.png", effect_blood_anim_data, 128, 128));
	SOUND("SE_Shot")->Load("Sound/SE/SE_Shot.wav");
	SOUND("SE_Hit")->Load("Sound/SE/SE_Hit.wav");
	SOUND("SE_Bomb")->Load("Sound/SE/SE_Bomb.wav");
	SOUND("SE_Zasi")->Load("Sound/SE/SE_Zasi.wav");
	SOUND("BGM_Game")->Load("Sound/BGM/BGM_Game.wav");
	*/
	
	//Base::Add(new Title());




}


void Release()
{
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->Viewport(0, 0, w, h);
	CCamera::GetCurrent()->Perspective(DtoR(60.0), (float)w / (float)h, 1.0, 1000.0);

	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv) {
	// メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(1);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	Init();
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();


		CInput::Update();
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();


		glfwSwapBuffers(GL::window);


		CFPS::Wait();

		char title[32];
		sprintf_s(title, "math fps:%d dt:%.3f", CFPS::GetFPS(), CFPS::GetDeltaTime());
		glfwSetWindowTitle(GL::window, title);

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();




	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}
