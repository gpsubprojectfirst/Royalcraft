#include "pch.h"
#include "UIButton.h"
#include "SoundMgr.h"

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
	case 0: //로비 가기
		m_ImgBefore = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\newstart.png"));
		m_ImgAfter = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\newstart2.png"));
		break;

	case 1: //게임 종료
		m_ImgBefore = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\gameend.png"));
		m_ImgAfter = new Gdiplus::Image(TEXT("Asset\\3.game\\4.ui\\gameend2.png"));
		break;

	default:
		break;

	}
	m_iBtnID = btnID;
	ParentImg = m_ImgBefore;
	m_bColBtn = false;
}


void UIButton::Update(float Delta)
{
	POINT	pt = MouseMgr::GetInstance().GetMousePos();
	m_bColBtn = false;

	CString curSceneName = SceneManager::GetInstance().GetCurScene()->Name;
	if (PtInRect(&GetRect(), pt))
	{
		m_bColBtn = true;
		if (KeyMgr::GetInstance().GetKey() & KEY_LBUTTON)
		{
			switch (m_iBtnID)
			{
			case 0: 
				if (!curSceneName.Compare(CString("LobbyScene")))
				{
					//게임씬가기
					SoundMgr::GetInstance()->SoundStop(5);
					SceneManager::GetInstance().LoadScene(CString("GameScene"));
				}
				else if (!curSceneName.Compare(CString("GameScene")))
				{
					//로비가기
					for (unsigned int i = 0; i < SoundMgr::GetInstance()->m_vecSoundBuff.size(); ++i)
					{
						if (SoundMgr::GetInstance()->SoundPlaying(i) == true)
						{
							SoundMgr::GetInstance()->SoundStop(i);
							std::cout << i << std::endl;
						}
					}
					SceneManager::GetInstance().GetCurScene()->Release();
					SceneManager::GetInstance().LoadScene(CString("LobbyScene"));
				}
			
				

				break;


			case 1: //게임종료
				for (unsigned int i = 0; i < SoundMgr::GetInstance()->m_vecSoundBuff.size(); ++i)
				{
					if (SoundMgr::GetInstance()->SoundPlaying(i) == true)
					{
						SoundMgr::GetInstance()->SoundStop(i);
					}
				}

				AfxGetMainWnd()->PostMessage(WM_CLOSE);

				break;
			}

		}
	}

}

void UIButton::Render(Gdiplus::Graphics* MemG)
{
	int width = rc.Width;
	int height = rc.Height;
	
	if (m_bColBtn)
	{
		ParentImg = m_ImgAfter;
	}
	else
	{
		ParentImg = m_ImgBefore;
	}
		
	Gdiplus::Rect Dst1( rc.X, rc.Y, width, height );
	MemG->DrawImage(ParentImg, Dst1);

}

void UIButton::Release()
{
	
}