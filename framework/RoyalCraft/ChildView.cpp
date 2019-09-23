
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "RoyalCraft.h"
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
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
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
	
	
	return TRUE;
}

void CChildView::OnPaint() 
{
	//CRoyalCraftApp::bRender = true;
	CPaintDC dc(this); // device context for painting

	 // Double buffering start
	CRect rectDraw;
	GetClientRect(rectDraw);
	// 한번에 그리기 위한 buffer역할을 하는 bitmap을 생성한다.(깜빡임은 한번에 그리지 않고 여러번 그리기 때문에 발생함)
	Gdiplus::Bitmap bitmap(rectDraw.Width(), rectDraw.Height());
	Gdiplus::Graphics graphics(dc);
	Gdiplus::Graphics memDC(&bitmap);

	// 그리기 전 bitmap 바탕을 하얗게 그려준다. (이 부분이 없으면 잔상이 남게 된다)
	Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 0, 0, 0));
	memDC.FillRectangle(&whiteBrush, 0, 0, rectDraw.Width(), rectDraw.Height());
	// 원하는 이미지를 bitmap에 그린다.     
	//Gdiplus::Image imageDisplay(TEXT("Asset\\supercell_logo.png"));
	//memDC.DrawImage(&imageDisplay, 0, 0, 300, 300);
	//// 완성된 bitmap은 한번에 화면에 그린다.
	//graphics.DrawImage(&bitmap, 0, 0);
	SceneManager::GetInstance().RenderScene(&graphics);
	CRoyalCraftApp::bRender = true;
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SceneManager::GetInstance().LoadScene(CString("LobbyScene"));
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CWinThread* pThread = AfxBeginThread(&CRoyalCraftApp::funcThread, NULL);

	return 0;
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}
