// CatchScreenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "CatchScreenDlg.h"
#include "afxdialogex.h"

// CCatchScreenDlg 对话框
// CCatchScreenDlg 消息处理程序
//保存旧的RGB值字符串
static CString strOld=_T("");

extern CString g_StartPortStr;
extern CString g_EndPortStr;
extern CString g_SizePicStr;
extern CString g_PicPathStr;
extern CString g_CurrentExePath;
extern HBITMAP g_HbitMap;

extern  CButton				g_PicCheck;
//extern  CMyDrawPictureClass	g_DrawPicture; ///制作透明图
extern  CMyShowPic			g_ShowPic;
extern CAB抓抓App theApp;

/////////////取色器////////////
extern CMyPickerColor		g_PickColorDlg;
/////////////////////////////////////////////////////////////////////////////
// CCatchScreenDlg dialog
IMPLEMENT_DYNAMIC(CCatchScreenDlg, CDialog)

	CCatchScreenDlg::CCatchScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatchScreenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCatchScreenDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

	//*******************************************************************************
	//初始化像皮筋类,新增的resizeMiddle 类型
	m_rectTracker.m_nStyle=CMyTracker::resizeMiddle|CMyTracker::solidLine;  
	m_rectTracker.m_rect.SetRect(-1,-2,-3,-4);
	//设置矩形颜色
	m_rectTracker.SetRectColor(RGB(10,100,130));
	//设置矩形调整时光标,默认的太小了,弄了个大点的
	m_rectTracker.SetResizeCursor(IDC_CURSOR6,IDC_CURSOR5,IDC_CURSOR2,IDC_CURSOR3,IDC_CURSOR4);

	m_hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);  


	m_bDraw=FALSE;
	m_bFirstDraw=FALSE;
	m_bQuit=FALSE;
	m_bShowMsg=FALSE;
	m_startPt=0;

	//获取屏幕分辩率
	m_xScreen = GetSystemMetrics(SM_CXSCREEN);
	m_yScreen = GetSystemMetrics(SM_CYSCREEN);

	//截取屏幕到位图中
	CRect rect(0, 0,m_xScreen,m_yScreen);
	m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(&rect));

	//初始化刷新窗口区域 m_rgn
	m_rgn.CreateRectRgn(0,0,50,50);
	//*******************************************************************************
}

void CCatchScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCatchScreenDlg)
	DDX_Control(pDX, IDC_EDITINFO1, m_tipEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCatchScreenDlg, CDialog)
	//{{AFX_MSG_MAP(CCatchScreenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID__SAVEPIC, &CCatchScreenDlg::OnClickSaveBmp)
	ON_COMMAND(ID__EXITSCREEN, &CCatchScreenDlg::OnExitCatchScreen)
	ON_WM_CREATE()
	ON_COMMAND(ID_ABMAKEPIN, &CCatchScreenDlg::OnAbmakepin)
	ON_COMMAND(ID_SYSMAKEPIC, &CCatchScreenDlg::OnSysmakepic)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatchScreenDlg message handlers

BOOL CCatchScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//**************************************************************************
	//把对化框设置成全屏顶层窗口
	::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);
	////// 测试代码 截小屏便于调试代码
	//SetWindowPos(&wndNoTopMost/*wndTopMost*/,0,0,200,200,SWP_SHOWWINDOW);
	//::SetWindowPos(g_PickColorDlg.m_hWnd,HWND_TOP/*HWND_TOPMOST*/,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);

	//移动操作提示窗口
	CRect rect;
	m_tipEdit.GetWindowRect(&rect);
	m_tipEdit.MoveWindow(10,10,rect.Width(),rect.Height());

	//显示操作提示窗口文字
	DrawTip();
	////**************************************************************************

	// TODO: Add extra initialization here
	//KillTimer(1001);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
////// OnCreate /////////////////////
int CCatchScreenDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//SetWindowPos(&wndTopMost,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);

	//移动操作提示窗口
	/*CRect rect;
	m_tipEdit.GetWindowRect(&rect);
	m_tipEdit.MoveWindow(10,10,rect.Width(),rect.Height());*/

	//显示操作提示窗口文字
	//DrawTip();
	return 0;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCatchScreenDlg::OnPaint() 
{

	//**************************************************************************
	CPaintDC dc(this);

	//显示截取矩形大小信息
	if(m_bShowMsg&&m_bFirstDraw)
	{
		//得到当前矩形大小
		CRect rect;
		m_rectTracker.GetTrueRect(&rect);
		//传递CPaintDC 是为了不在了窗口上画信息
		DrawMessage(rect,&dc);
	}

	//画出像皮筋矩形
	if(m_bFirstDraw)
	{
		m_rectTracker.Draw(&dc);
	}

	//::SetWindowPos(g_PickColorDlg.m_hWnd,HWND_BOTTOM/*HWND_TOPMOST*/,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);

	//*************************************************************************
	CDialog::OnPaint();
}
///////////
void CCatchScreenDlg::OnOK() 
{
	// TODO: Add extra validation here
	//if(m_bFirstDraw)
	//{
	//	//取消已画矩形变量
	//	m_bFirstDraw=FALSE;
	//	m_bDraw=FALSE;
	//	m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
	//	PaintWindow();
	//}
	//else
	{
		CDialog::OnOK();
	}

	//CDialog::OnOK();
}

void CCatchScreenDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//***************************************************************
	if(m_bFirstDraw)
	{
		//取消已画矩形变量
		m_bFirstDraw=FALSE;
		m_bDraw=FALSE;
		m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
		PaintWindow();
	}
	else
	{
		CDialog::OnCancel();
	}
	//*******************************************************************
}

//// 鼠标移动过程
void CCatchScreenDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//**************************************************************************************
	if(m_bDraw)
	{
		//动态调整矩形大小,并刷新画出
		m_rectTracker.m_rect.SetRect(m_startPt.x+4,m_startPt.y+4,point.x,point.y);
		PaintWindow();
	}

	//弥补调整大小和位置时,接收不到MouseMove消息
	CRect rect;
	m_tipEdit.GetWindowRect(&rect);
	// if(rect.PtInRect(point))
	//m_tipEdit.SendMessage(WM_MOUSEMOVE);

	//ChangeRGB();

	DrawTip();
	//*****************************************************************************************
	CDialog::OnMouseMove(nFlags, point);
}
////// 左键按下
void CCatchScreenDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//*****************************************************************************************
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);

	//判断击中位置
	if(nHitTest<0)
	{
		if(!m_bFirstDraw)
		{
			//第一次画矩形
			m_startPt=point;
			m_bDraw=TRUE;
			m_bFirstDraw=TRUE;
			//设置当当鼠标按下时最小的矩形大小
			m_rectTracker.m_rect.SetRect(point.x,point.y,point.x+4,point.y+4);	

			//保证当鼠标当下时立刻显示信息
			if(m_bFirstDraw)
				m_bShowMsg=TRUE;		
			DrawTip();
			PaintWindow();
		}
	}
	else
	{
		//保证当鼠标当下时立刻显示信息
		m_bShowMsg=TRUE;		
		PaintWindow();

		if(m_bFirstDraw)
		{
			//调束大小时,Track会自动调整矩形大小,在些期间,消息归CRectTracker内部处理
			m_rectTracker.Track(this,point,TRUE);
			//SendMessage(WM_LBUTTONUP,NULL,NULL);
			PaintWindow();

		}
	}
	//****************************************************************************************
	CDialog::OnLButtonDown(nFlags, point);
}

////// 左键弹起
void CCatchScreenDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//****************************************************************************************

	m_bShowMsg=FALSE;
	m_bDraw=FALSE;
	DrawTip();

	PaintWindow();
	//****************************************************************************************
	CDialog::OnLButtonUp(nFlags, point);
}

///////左键双击 退出截图。并保存位图到粘贴板中,bSave 为TRUE,
void CCatchScreenDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);
	//如果在是矩形内部双击
	if(nHitTest==8)      
	{
		//保存位图到粘贴板中,bSave 为TRUE,
		HBITMAP hbmp = CopyScreenToBitmap(m_rectTracker.m_rect,TRUE);
		//PostQuitMessage(0);
		//g_ShowPic.LoadClipboardBMP();
		CString pathStr = g_CurrentExePath+ _T("abpic.bmp");
		theApp.pPropSheet->activeCurrentPage(2);
		g_ShowPic.SaveBmpFile(hbmp,pathStr);
		g_ShowPic.ShowBmp(pathStr);
		this->OnOK();
		//::PostQuitMessage(0);
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

///右键弹起
void CCatchScreenDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//****************************************************************************************
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);
	//如果是在矩形内部右击
	if(nHitTest==8)
	{
		if(m_bFirstDraw)
		{
			POINT   pt;   
			GetCursorPos(&pt);
			CMenu menu;
			menu.LoadMenu(IDR_MENU_CATCHSCREEN);
			menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
		}
	}
	else
		if(m_bFirstDraw)
		{
			//如果已经截取矩则清除截取矩形
			m_bFirstDraw=FALSE;
			//清除矩形大小
			m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
			DrawTip();
			PaintWindow();
		}
		else
		{
			//关闭程序
			//PostQuitMessage(0);
			OnCancel();
		}
		//****************************************************************************************
		CDialog::OnRButtonUp(nFlags, point);
}
//设置操作提示窗口文本颜色
HBRUSH CCatchScreenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	// TODO: Return a different brush if the default is not desired
	//***********************************************************
	//设置操作提示窗口文本颜色
	if(pWnd->GetDlgCtrlID()==IDC_EDITINFO1)
	{
		pDC->SetTextColor(RGB(255,255,255));
	}
	//***************************************************************
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

//用整个桌面填充全屏对话框背景
BOOL CCatchScreenDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//**************************************************************************************
	//用整个桌面填充全屏对话框背景
	BITMAP bmp;
	m_pBitmap->GetBitmap(&bmp);

	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);

	dcCompatible.SelectObject(m_pBitmap);

	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);

	return TRUE;
	//**************************************************************************************
	//return CDialog::OnEraseBkgnd(pDC);
}

//设置改变截取矩形大小时光标
BOOL CCatchScreenDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	// ***********************************************************************
	// 设置改变截取矩形大小时光标
	if (pWnd == this &&m_rectTracker.SetCursor(this, nHitTest)
		&&!m_bDraw &&m_bFirstDraw) //此处判断保截取时当标始中为彩色光标
	{
		return TRUE; 
	}

	//设置彩色光标
	SetCursor(m_hCursor);
	return TRUE;

	//*******************************************************************
	//return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


//*********************增加的函数**********************************************************
//考贝屏幕,这段代码是拿来主义 呵呵
HBITMAP CCatchScreenDlg::CopyScreenToBitmap(LPRECT lpRect,BOOL bSave)
	//lpRect 代表选定区域
{
	HDC       hScrDC, hMemDC;      
	// 屏幕和内存设备描述表
	HBITMAP    hBitmap, hOldBitmap;   
	// 位图句柄
	int       nX, nY, nX2, nY2;      
	// 选定区域坐标
	int       nWidth, nHeight;

	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);

	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > m_xScreen)
		nX2 = m_xScreen;
	if (nY2 > m_yScreen)
		nY2 = m_yScreen;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap
		(hScrDC, nWidth, nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	if(bSave)
	{
		//创建军兼容DC,当bSave为中时把开始保存的全屏位图,按截取矩形大小保存
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(CDC::FromHandle(hMemDC));
		dcCompatible.SelectObject(m_pBitmap);

		BitBlt(hMemDC, 0, 0, nWidth, nHeight,dcCompatible, nX, nY, CAPTUREBLT|SRCCOPY);

	}
	else
	{
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,hScrDC, nX, nY, CAPTUREBLT|SRCCOPY);
	}

	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//得到屏幕位图的句柄
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);

	if(bSave)
	{
		if (::OpenClipboard(NULL)) 
		{
			//清空剪贴板
			EmptyClipboard();
			//把屏幕内容粘贴到剪贴板上,
			//hBitmap 为刚才的屏幕位图句柄
			SetClipboardData(CF_BITMAP, hBitmap);
			//关闭剪贴板
			CloseClipboard();
		}
	}
	// 返回位图句柄
	return hBitmap;
}
HBITMAP CCatchScreenDlg::CopyRectToBitmap(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;      
	// 屏幕和内存设备描述表
	HBITMAP hBitmap,hOldBitmap;   
	// 位图句柄
	int       nX, nY, nX2, nY2;      
	// 选定区域坐标
	int       nWidth, nHeight;      
	// 位图宽度和高度
	int       xScrn, yScrn;         
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;

	//为屏幕创建设备描述表
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	// 获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, CAPTUREBLT|SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// 返回位图句柄
	return hBitmap;
}
//显示操作提示信息
void CCatchScreenDlg::DrawTip()
{
	static COLORREF oldColor=0;

	//得当前坐标像素,
	CPoint pt;
	GetCursorPos(&pt);

	//当到当前R,G,B,各像素值
	COLORREF color;
	CClientDC dc(this);
	color=dc.GetPixel(pt);
	BYTE rValue,gValue,bValue;
	rValue=GetRValue(color);
	gValue=GetGValue(color);
	bValue=GetGValue(color);

	if(oldColor==color)
		return ;

	oldColor=color;

	//按格式排放字符串
	CString string;
	CString strTemp;
	string.Format(_T("\r\n\r\n\r\n ·当前像素RGB (%d,%d,%d)\r\n"),rValue,gValue,bValue);

	if(!m_bDraw&&!m_bFirstDraw)
	{
		strTemp=_T("\r\n ·按下鼠标左键不放选择截取\r\n 范围\r\n\r\n ·按ESC键或鼠标右键退出");
	}
	else
		if(m_bDraw&&m_bFirstDraw)
		{
			strTemp=_T("\r\n ·松开鼠标左键确定截取范围\r\n\r\n ·按ESC键退出");
		}
		else
			if(m_bFirstDraw)
			{
				strTemp=_T("\r\n ·用鼠标左键调整截取范围的\r\n 大小和位置\r\n\r\n ·截取范围内双击鼠标左键保\r\n 存图像，结束操作\r\n\r\n ·点击鼠标右键重新选择");
			}
			string+=strTemp;
			//显示到编缉框中,操作提示窗口
			m_tipEdit.SetWindowText(string);
}

//显示截取矩形信息
void CCatchScreenDlg::DrawMessage(CRect &inRect,CDC * pDC)
{
	//截取矩形大小信息离鼠标间隔
	const int space=3;    
	//设置字体颜色大小

	CPoint pt;
	CPen pen(PS_SOLID,1,RGB(147,147,147));

	//dc.SetTextColor(RGB(147,147,147));
	CFont font;
	CFont * pOldFont;
	font.CreatePointFont(90,_T("宋体"));
	pOldFont=pDC->SelectObject(&font);

	//得到字体宽度和高度
	GetCursorPos(&pt);
	int OldBkMode;
	OldBkMode=pDC->SetBkMode(TRANSPARENT);

	TEXTMETRIC tm;
	int charHeight;
	CSize size;
	int	lineLength;
	pDC->GetTextMetrics(&tm);
	charHeight = tm.tmHeight+tm.tmExternalLeading;
	size=pDC->GetTextExtent(_T("顶点位置  "),/*strlen*/wcslen(_T("顶点位置  ")));
	lineLength=size.cx;

	//初始化矩形, 以保证写下六行文字
	CRect rect(pt.x+space,pt.y-charHeight*6-space,pt.x+lineLength+space,pt.y-space);

	//创建临时矩形
	CRect rectTemp;
	//当矩形到达桌面边缘时调整方向和大小
	if((pt.x+rect.Width())>=m_xScreen)
	{
		//桌面上方显示不下矩形
		rectTemp=rect;
		rectTemp.left=rect.left-rect.Width()-space*2;
		rectTemp.right=rect.right-rect.Width()-space*2;;
		rect=rectTemp;
	}

	if((pt.y-rect.Height())<=0)
	{
		//桌面右方显示不下矩形
		rectTemp=rect;
		rectTemp.top=rect.top+rect.Height()+space*2;;
		rectTemp.bottom=rect.bottom+rect.Height()+space*2;;
		rect=rectTemp;

	}

	//创建空画刷画矩形
	CBrush * pOldBrush;
	pOldBrush=pDC->SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));

	pDC->Rectangle(rect);
	rect.top+=2;
	//在矩形中显示文字
	CRect outRect(rect.left,rect.top,rect.left+lineLength,rect.top+charHeight);
	CString string(_T("顶点位置"));
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight,rect.left+lineLength,charHeight+rect.top+charHeight);
	string.Format(_T("(%d,%d)"),inRect.left,inRect.top);
	pDC->DrawText(string,outRect,DT_CENTER);


	outRect.SetRect(rect.left,rect.top+charHeight*2,rect.left+lineLength,charHeight+rect.top+charHeight*2);
	string=_T("矩形大小");
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*3,rect.left+lineLength,charHeight+rect.top+charHeight*3);
	string.Format(_T("(%d,%d)"),inRect.Width(),inRect.Height());
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*4,rect.left+lineLength,charHeight+rect.top+charHeight*4);
	string=_T("光标坐标");
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*5,rect.left+lineLength,charHeight+rect.top+charHeight*5);
	string.Format(_T("(%d,%d)"),pt.x,pt.y);
	pDC->DrawText(string,outRect,DT_CENTER);

	pDC->SetBkMode(OldBkMode);
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldBrush);

	/*g_StartPortStr.Format(_T("%d , %d"),inRect.left,inRect.top);
	g_EndPortStr.Format(_T("%d , %d"),inRect.right-m_rectTracker,inRect.bottom);
	g_SizePicStr.Format(_T("%d , %d"),inRect.Width(),inRect.Height());*/
}
//重画窗口
void CCatchScreenDlg::PaintWindow()
{
	//获取当全屏对话框窗口大小
	CRect rect1;
	GetWindowRect(rect1);

	//获取编辑框窗口大小
	CRect rect2;
	//m_tipEdit.GetWindowRect(rect2);

	CRgn rgn1,rgn2;
	rgn1.CreateRectRgnIndirect(rect1);
	//rgn2.CreateRectRgnIndirect(rect2);

	//获取更新区域,就是除了编辑框窗口不更新
	//m_rgn.CombineRgn(&rgn1,&rgn2,RGN_DIFF);

	InvalidateRgn(&rgn1);
}
//改变操作提示窗口当RGB值
void CCatchScreenDlg::ChangeRGB()
{
	CPoint pt;
	GetCursorPos(&pt);

	//当到当前R,G,B,各像素值
	COLORREF color;
	CClientDC dc(this);
	color=dc.GetPixel(pt);
	BYTE rValue,gValue,bValue;
	rValue=GetRValue(color);
	gValue=GetGValue(color);
	bValue=GetGValue(color);

	//按格式排放字符串
	CString string;
	string.Format(_T("(%d,%d,%d)"),rValue,gValue,bValue);
	//如果当前颜色没变则不刷新RGB值,以免窗口有更多闪烁
	if(strOld!=string)
	{
		//得到RGB文本那一行的文本长度
		int LineLength=m_tipEdit.LineLength(6);
		//复选RGB值文本,也就是(255,255,255)形式
		m_tipEdit.SetSel(20,LineLength+6);

		//替换RGB内容
		m_tipEdit.ReplaceSel(string);
	}

	strOld=string;

}

//*******************************************************************************************

BOOL CCatchScreenDlg::CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi)
{ 
	BITMAP bmp; 
	// Retrieve the bitmap color format, width, and height. 
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
	{
		return FALSE;
	}

	int width = ::GetSystemMetrics(SM_CXSCREEN);
	int height = ::GetSystemMetrics(SM_CYSCREEN);
	if(2*width<bmp.bmWidth||2*height<bmp.bmHeight)
	{
		//////表示保存的时候出现了异常。保存失败！！！！
		return false;
	}

	pbmi = (PBITMAPINFO) LocalAlloc(LPTR,sizeof(BITMAPINFOHEADER)); 

	// Initialize the fields in the BITMAPINFO structure. 

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	pbmi->bmiHeader.biWidth = bmp.bmWidth; 
	pbmi->bmiHeader.biHeight = bmp.bmHeight; 
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
	pbmi->bmiHeader.biBitCount = /*bmp.bmBitsPixel*/24; 

	// If the bitmap is not compressed, set the BI_RGB flag. 
	pbmi->bmiHeader.biCompression = BI_RGB; 

	// Compute the number of bytes in the array of color 
	// indices and store the result in biSizeImage. 
	// For Windows NT, the width must be DWORD aligned unless 
	// the bitmap is RLE compressed. This example shows this. 
	// For Windows 95/98/Me, the width must be WORD aligned unless the 
	// bitmap is RLE compressed.
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * 24 +31) & ~31) /8
		* pbmi->bmiHeader.biHeight; 
	// Set biClrImportant to 0, indicating that all of the 
	// device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0; 
	return TRUE; 
} 

BOOL CCatchScreenDlg::CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC) 
{ 
	HANDLE hf;                 // file handle 
	BITMAPFILEHEADER hdr;       // bitmap file-header 
	PBITMAPINFOHEADER pbih;     // bitmap info-header 
	LPBYTE lpBits;              // memory pointer 
	DWORD dwTotal;              // total count of bytes 
	DWORD cb;                   // incremental count of bytes 
	BYTE *hp;                   // byte pointer 
	DWORD dwTmp; 

	pbih = (PBITMAPINFOHEADER) pbi; 
	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits) 
		return FALSE;

	// Retrieve the color table (RGBQUAD array) and the bits 
	// (array of palette indices) from the DIB. 
	if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, 
		DIB_RGB_COLORS)) 
	{
		return FALSE;
	}

	// Create the .BMP file. 
	hf = CreateFile(pszFile, 
		GENERIC_READ | GENERIC_WRITE, 
		(DWORD) 0, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL); 
	if (hf == INVALID_HANDLE_VALUE) 
		return FALSE;
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
	// Compute the size of the entire file. 
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof(RGBQUAD) + pbih->biSizeImage); 
	hdr.bfReserved1 = 0; 
	hdr.bfReserved2 = 0; 

	// Compute the offset to the array of color indices. 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof (RGBQUAD); 

	// Copy the BITMAPFILEHEADER into the .BMP file. 
	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
		(LPDWORD) &dwTmp,  NULL)) 
	{
		return FALSE;
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
		+ pbih->biClrUsed * sizeof (RGBQUAD), 
		(LPDWORD) &dwTmp, ( NULL))) 
		return FALSE;

	// Copy the array of color indices into the .BMP file. 
	dwTotal = cb = pbih->biSizeImage; 
	hp = lpBits; 
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
		return FALSE;
	// Close the .BMP file. 
	if (!CloseHandle(hf)) 
		return FALSE;

	// Free memory. 
	GlobalFree((HGLOBAL)lpBits);

	return TRUE;
}


void CCatchScreenDlg::OnClickSaveBmp()
{
	// TODO: 在此添加命令处理程序代码
	SYSTEMTIME time;
	::GetLocalTime(&time);
	CString lpTime=_T("");
	if(time.wMinute<10&&time.wSecond<10)
		lpTime.Format(_T("TC截图%d%d%d%d%0d%0d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else if(time.wMinute<10)
		lpTime.Format(_T("TC截图%d%d%d%d%0d%d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else if(time.wSecond<10)
		lpTime.Format(_T("TC截图%d%d%d%d%d%0d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else
		lpTime.Format(_T("TC截图%d%d%d%d%d%d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);

	TCHAR fileBuffer[256]={_T("TC")};
	::memset(fileBuffer,0,256*sizeof(TCHAR));
	::memcpy(fileBuffer,lpTime.LockBuffer(),lpTime.GetLength()*sizeof(TCHAR));

	TCHAR OldPath[MAX_PATH]={0};
	::GetCurrentDirectoryW(MAX_PATH,OldPath);

	CFileDialog PathDlg(FALSE, _T("*.bmp"), fileBuffer, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Save File(*.bmp)|*.bmp||"));

	PathDlg.m_ofn.lpstrDefExt=_T("bmp");

	HBITMAP tbmp;

	if(PathDlg.DoModal()==IDOK)
	{
		if(m_rectTracker.m_rect.left>m_rectTracker.m_rect.right)
		{
			int left = m_rectTracker.m_rect.left;
			int top = m_rectTracker.m_rect.top;
			m_rectTracker.m_rect.left = m_rectTracker.m_rect.right;
			m_rectTracker.m_rect.top  = m_rectTracker.m_rect.bottom;
			m_rectTracker.m_rect.right = left;
			m_rectTracker.m_rect.bottom = top;
		}
		if(m_rectTracker.m_rect.top>m_rectTracker.m_rect.bottom)
		{
			int bottom = m_rectTracker.m_rect.bottom;
			int top = m_rectTracker.m_rect.top;
			m_rectTracker.m_rect.top = bottom;
			m_rectTracker.m_rect.bottom = top;
		}
		tbmp=CopyScreenToBitmap(m_rectTracker.m_rect,TRUE);

		if(tbmp==NULL)
		{
			this->OnOK();
			/*::AfxMessageBox(_T("图片未保存！"));*/
		}

		g_HbitMap = tbmp;

		PBITMAPINFO pbmp;
		if(!CreateBitmapInfoStruct(tbmp, pbmp))
		{
			return;
		}

		g_PicPathStr = PathDlg.GetPathName();

		if(!CreateBMPFile(g_PicPathStr.LockBuffer(), pbmp, tbmp, GetDC()->GetSafeHdc()))
		{
			//::AfxMessageBox(_T("位图保存失败!"));
			this->OnOK();
			return ;
		}

		g_StartPortStr.Format(_T("%d , %d"),m_rectTracker.m_rect.left,m_rectTracker.m_rect.top);
		g_EndPortStr.Format(_T("%d , %d"),m_rectTracker.m_rect.right-1,m_rectTracker.m_rect.bottom-1);
		g_SizePicStr.Format(_T("%d , %d"),m_rectTracker.m_rect.Width()-1,m_rectTracker.m_rect.Height()-1);

		::SetCurrentDirectoryW(OldPath);

		this->OnOK();
	}
	else
	{
		this->OnOK();
		::SetCurrentDirectoryW(OldPath);
	}
}

void CCatchScreenDlg::OnExitCatchScreen()
{
	// TODO: 在此添加命令处理程序代码
	//关闭程序
	//PostQuitMessage(1);
	this->OnCancel();
}


void CCatchScreenDlg::OnAbmakepin()
{
	// TODO: 在此添加命令处理程序代码
	if(m_rectTracker.m_rect.left>m_rectTracker.m_rect.right)
	{
		int left = m_rectTracker.m_rect.left;
		int top = m_rectTracker.m_rect.top;
		m_rectTracker.m_rect.left = m_rectTracker.m_rect.right;
		m_rectTracker.m_rect.top  = m_rectTracker.m_rect.bottom;
		m_rectTracker.m_rect.right = left;
		m_rectTracker.m_rect.bottom = top;
	}
	if(m_rectTracker.m_rect.top>m_rectTracker.m_rect.bottom)
	{
		int bottom = m_rectTracker.m_rect.bottom;
		int top = m_rectTracker.m_rect.top;
		m_rectTracker.m_rect.top = bottom;
		m_rectTracker.m_rect.bottom = top;
	}
	HBITMAP tbmp;
	CRect m_Rect/* = m_rectTracker.m_rect*/;
	m_Rect.SetRect(m_rectTracker.m_rect.left+2,m_rectTracker.m_rect.top+2,m_rectTracker.m_rect.right-2,m_rectTracker.m_rect.bottom-2);
	this->ClientToScreen(&m_Rect);

	tbmp=CopyRectToBitmap(m_Rect);
	if(tbmp==NULL)
	{
		this->OnOK();
		::DeleteObject(tbmp);
		return ;
	}

	PBITMAPINFO pbmp;
	if(!CreateBitmapInfoStruct(tbmp, pbmp))
	{
		this->OnOK();
		::DeleteObject(tbmp);
		return;
	}

	::Sleep(500);

	bool IsSaveOK = true;
	HDC hdc = ::GetDC(NULL);
	CString pathStr = g_CurrentExePath+_T("tctemp.bmp");
	if(!CreateBMPFile(pathStr.LockBuffer(), pbmp, tbmp, hdc))
	{
		IsSaveOK = false;
	}

	this->OnOK();

	if(IsSaveOK)
	{
		//if(g_DrawPicture.IsWindowVisible())
		//{
		//	//::AfxMessageBox(_T("copy位图到制图界面"));
		//	g_DrawPicture.Loadbmp(pathStr);
		//}
		//else
		//{
		//	g_PicCheck.SetCheck(BST_CHECKED);
		//	g_DrawPicture.ShowWindow(TRUE);
		//	g_DrawPicture.Loadbmp(pathStr);
		//}

		theApp.pPropSheet->activeCurrentPage(5);
		theApp.pPropSheet->m_DrawPicWnd.Loadbmp(pathStr);
	}

	::ReleaseDC(NULL,hdc);
	::DeleteObject(tbmp);
}


void CCatchScreenDlg::OnSysmakepic()
{
	// TODO: 在此添加命令处理程序代码
	this->OnOK();
	if(m_rectTracker.m_rect.left>m_rectTracker.m_rect.right)
	{
		int left = m_rectTracker.m_rect.left;
		int top = m_rectTracker.m_rect.top;
		m_rectTracker.m_rect.left = m_rectTracker.m_rect.right;
		m_rectTracker.m_rect.top  = m_rectTracker.m_rect.bottom;
		m_rectTracker.m_rect.right = left;
		m_rectTracker.m_rect.bottom = top;
	}
	
	if(m_rectTracker.m_rect.top>m_rectTracker.m_rect.bottom)
	{
		int bottom = m_rectTracker.m_rect.bottom;
		int top = m_rectTracker.m_rect.top;
		m_rectTracker.m_rect.top = bottom;
		m_rectTracker.m_rect.bottom = top;
	}
	HBITMAP tbmp;
	CRect m_Rect = m_rectTracker.m_rect;
	this->ClientToScreen(&m_Rect);

	tbmp=CopyRectToBitmap(m_Rect);
	if(tbmp==NULL)
	{
		::DeleteObject(tbmp);
		return ;
	}

	PBITMAPINFO pbmp;
	if(!CreateBitmapInfoStruct(tbmp, pbmp))
	{
		::DeleteObject(tbmp);
		return;
	}
	bool IsSaveOK = true;
	HDC hdc = ::GetDC(NULL);
	CString pathStr = g_CurrentExePath+_T("tctemp.bmp");
	if(!CreateBMPFile(pathStr.LockBuffer(), pbmp, tbmp, hdc))
	{
		IsSaveOK = false;
	}

	if(IsSaveOK)
	{
		char path[MAX_PATH]={0};
		USES_CONVERSION;
		::strcat(path,"mspaint.exe ");
		::strcat(path,W2A(pathStr.LockBuffer()));
		::WinExec(path,SW_SHOWNORMAL);
	}

	::ReleaseDC(NULL,hdc);
	::DeleteObject(tbmp);
}
