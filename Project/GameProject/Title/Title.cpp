#include "Title.h"
#include"../Game/Game.h"
#include "../UI/Menu.h"
#include "../Map/Map.h"
Title::Title() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc",64) {
	m_img = COPY_RESOURCE("Title", CImage);
}
Title::~Title() {
	//全てのオブジェクトを破棄
	Base::KillAll();
	//ゲームシーンへ
	
	Base::Add(new Game());
}
void Title::Update(){
	m_img.SetSize(CCamera::GetCurrent()->GetWhidth(), CCamera::GetCurrent()->GetHeight());
	//ボタン1でタイトル破棄
	if (PUSH(CInput::eButton10)) {

		SetKill();
	}
}
void Title::Draw() {
	m_img.Draw();
	//文字表示
	m_title_text.Draw(CCamera::GetCurrent()->GetWhidth() / 2 - 180, CCamera::GetCurrent()->GetHeight() / 2, 1, 1, 1, "Title");
	m_title_text.Draw(CCamera::GetCurrent()->GetWhidth() / 2 - 180, CCamera::GetCurrent()->GetHeight() / 1.2, 1, 1, 1, "Push.Enter");
}

License::License():Base(eType_Scene)
{
	m_img = COPY_RESOURCE("License", CImage);
	
	m_img.SetSize(73, 63);
}

void License::Update()
{
	m_img.SetPos(CCamera::GetCurrent()->GetWhidth() - 73, CCamera::GetCurrent()->GetHeight() - 63);
	if (PUSH(CInput::eButton10)) {
		SetKill();
	}
}

void License::Draw()
{
	m_img.Draw();
}
