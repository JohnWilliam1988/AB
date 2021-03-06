
#include "stdafx.h"
#include "AB抓抓.h"
#include "MyPic.h"

extern HWND g_CatchElemhWnd;
extern HWND g_CatchWindowshWnd;
/////////////////////////////////////////////////////////////////////////////
// CMyPic
CMyPic::CMyPic()
{
}

CMyPic::~CMyPic()
{
}


BEGIN_MESSAGE_MAP(CMyPic, CStatic)
	//{{AFX_MSG_MAP(CMyPic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPic message handlers

void CMyPic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	HCURSOR hc=LoadCursor(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR7_EYE));
	::SetCursor(hc);
	HICON hicon2=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_DRAG_LEAVE));
	this->SetIcon(hicon2);
	// 启动抓取网页元素定时器
	if(FromHandle(g_CatchElemhWnd))
	{
		if(FromHandle(g_CatchElemhWnd)->IsWindowVisible())
			FromHandle(g_CatchElemhWnd)->SetTimer(1,200,NULL);
	}
	// 启动抓窗口的定时器
	if(FromHandle(g_CatchWindowshWnd))
	{
		if(FromHandle(g_CatchWindowshWnd)->IsWindowVisible())
			FromHandle(g_CatchWindowshWnd)->SetTimer(1,150,NULL);
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CMyPic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	HICON hicon1=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_ICON_DRAG));
	this->SetIcon(hicon1);	

	//FromHandle(g_CatchElemhWnd)->KillTimer(1);
	// 关闭抓取网页元素定时器
	if(FromHandle(g_CatchElemhWnd))
	{
		if(FromHandle(g_CatchElemhWnd)->IsWindowVisible())
			FromHandle(g_CatchElemhWnd)->KillTimer(1);
	}
	// 关闭抓窗口的定时器
	if(FromHandle(g_CatchWindowshWnd))
	{
		if(FromHandle(g_CatchWindowshWnd)->IsWindowVisible())
		{
			FromHandle(g_CatchWindowshWnd)->KillTimer(1);
			((CMyCatchMouseWindowInfo*)FromHandle(g_CatchWindowshWnd))->GetWndListTree();
		}
	}
	CStatic::OnLButtonUp(nFlags, point);
}
