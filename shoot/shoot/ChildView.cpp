
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "shoot.h"
#include "ChildView.h"
#include "SceneManager.h"

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

	SceneManager::GetInstance().LoadScene(CString("Scene_Start"));

	return TRUE;
}

void CChildView::OnPaint() 
{
	CshootApp::bRender = true;

	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	Graphics MainG(dc);
	

	/*CMemDC memDC(dc, this);
	CBrush br(RGB(0, 0, 0));
	memDC.GetDC().FillRect(rc, &br);
	*/
	
	CRect rc;
	GetClientRect(rc);
	Rect rc2(rc.left, rc.top, rc.Width(), rc.Height());
	Bitmap BackBuffer(rc.Width(), rc.Height(), PixelFormat32bppARGB);
	Graphics* MemG = Graphics::FromImage(&BackBuffer);
	//32비트
	Color color(255, 255, 255, 255);
	SolidBrush br(Color(255, 255, 255, 255));
	MemG->FillRectangle(&br, rc2);

	MainG.DrawImage(&BackBuffer, rc2);


	//DWORD delta = GetTickCount() - theApp.PrevTick;
	//DWORD value = delta == 0 ? 0 :  1000 / delta;
	//memDC.GetDC().SetTextColor(RGB(255, 0, 0));
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SceneManager::GetInstance().RenderScene(&memDC.GetDC());

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
	CString temp;
	temp.Format(TEXT("%d"), value);
	memDC.GetDC().DrawText(temp, rc, DT_LEFT | DT_VCENTER);

	CshootApp::bRender = false;
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

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CWinThread* pThread = AfxBeginThread(&CshootApp::funcThread, NULL);

	return 0;
}
