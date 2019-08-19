
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "GP_subproject_first.h"
#include "ChildView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);
	ObjectManager::GetInstance();
	return TRUE;
}
void grayscale(int width, int height, Gdiplus::BitmapData& pData)
{
	BYTE* pt = static_cast<BYTE*>(pData.Scan0);
	BYTE* pt2 = pt;
	for (int i = 0; i < height; ++i)
	{
		pt = pt2 + i * pData.Width * 4;
		for (int j = 0; j < width; ++j)
		{
			BYTE calc = *(pt) * 0.299 + *(pt + 1) * 0.587 + *(pt + 2) * 0.114;
			*(pt) = calc;
			*(pt + 1) = calc;
			*(pt + 2) = calc;
			pt += 4;
		}
	}
}
void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	Gdiplus::Graphics MainG(dc);

	 // Double buffering start
	CRect rc;
	GetClientRect(rc);
	Gdiplus::Rect rc2(rc.left, rc.top, rc.Width(), rc.Height());

	// 한번에 그리기 위한 buffer역할을 하는 bitmap을 생성한다.(깜빡임은 한번에 그리지 않고 여러번 그리기 때문에 발생함)
	Gdiplus::Bitmap BackBuffer(rc.Width(), rc.Height(), PixelFormat32bppARGB);
	Gdiplus::Graphics MemG(&BackBuffer);

	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 0, 0, 0));
	MemG.FillRectangle(&WhiteBrush, rc2);
	//sm.Update();
	//그리기
	SceneManager::GetInstance().GetCurScene()->GetBuffer(&BackBuffer);
 	SceneManager::GetInstance().RenderScene(&MemG);

	/*if (((GameScene*)SceneManager::GetInstance().GetCurScene())->endflag  == true)
	{
		BitmapData pt;
		Gdiplus::Rect rc3(0, 0, rc.Width(), rc.Height());
		BackBuffer.LockBits(&rc3, ImageLockModeWrite, PixelFormat32bppARGB, &pt);
		grayscale(rc3.Width , rc3.Height, pt);
		BackBuffer.UnlockBits(&pt);
	}*/
	//CGPsubprojectfirstApp::bRender = true;
	
	MainG.DrawImage(&BackBuffer, 0, 0, rc.Width(), rc.Height());
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SceneManager::GetInstance().SendLButtonDown(nFlags, point);
	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	SceneManager::GetInstance().LoadScene(CString("LogoScene"));
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CWinThread* pThread = AfxBeginThread(&CGPsubprojectfirstApp::funcThread, NULL);
	return 0;
}
