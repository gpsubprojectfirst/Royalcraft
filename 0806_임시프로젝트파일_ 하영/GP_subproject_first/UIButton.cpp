#include "pch.h"
#include "UIButton.h"

UIButton::UIButton()
{

}

UIButton::~UIButton()
{

}
void UIButton::Init(int btnID)
{
	switch (btnID)
	{
	case 0: //게임 종료
		m_ImgBefore = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\gameend.png"));
		break;

	case 1: //로비 가기
		m_ImgBefore = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\newstart.png"));
		break;

	default:
		break;

	}
	m_iBtnID = btnID;
	ParentImg = m_ImgBefore;
}


void UIButton::Update(float Delta)
{
	POINT	pt = MouseMgr::GetInstance().GetMousePos();

	if (PtInRect(&GetRect(), pt))
	{
		if (KeyMgr::GetInstance().GetKey() & KEY_RBUTTON)
		{
			switch (m_iBtnID)
			{
			case 0:
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
				std::cout << m_iBtnID << "click!" << endl;
				break;

			case 1:
				SceneManager::GetInstance().GetCurScene()->Release();
				SceneManager::GetInstance().LoadScene(CString("LobbyScene"));
				std::cout << m_iBtnID << "click!" << endl; std::cout << "click!"  << endl;
				break;
			}

		}
	}
}

void UIButton::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;

	Gdiplus::Rect Dst1( rc.X, rc.Y, width, height );
	MemG->DrawImage(ParentImg, Dst1);
}