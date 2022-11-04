#include "Title.h"
#include"../Game/Game.h"

Title::Title():Base(eType_Scene)
,m_title_text("C:\\Windows\\Fonts\\msgothic.ttc",64) {
	m_img = COPY_RESOURCE("Title", CImage);
}
Title::~Title() {
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�Q�[���V�[����
	Base::Add(new Game());
}
void Title::Update(){
	//�{�^��1�Ń^�C�g���j��
	if (PUSH(CInput::eButton1)) {
		SetKill();
	}
}
void Title::Draw() {
	m_img.Draw();
	//�����\��
	m_title_text.Draw(64, 256, 0, 0, 0, "Titel");
	m_title_text.Draw(64, 512, 0, 0, 0, "Push.Z");
}

License::License():Base(eType_Scene)
{
	m_img = COPY_RESOURCE("License", CImage);
	m_img.SetPos(1280 - 73, 720 - 63);
	m_img.SetSize(73, 63);
}

void License::Update()
{
	if (PUSH(CInput::eButton1)) {
		SetKill();
	}
}

void License::Draw()
{
	m_img.Draw();
}
