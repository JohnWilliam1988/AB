// MyCatchMouseWindowInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyCatchMouseWindowInfo.h"
#include "afxdialogex.h"

extern HWND g_CatchWindowshWnd;
//热键资源
#define IDC_USERHOTKEY_CATCHSCREEN                   WM_USER+150

///////////////////////////枚举子窗口//////////////
BOOL CALLBACK EnumChildProc(HWND hwnd,LPARAM lParam)
{
	wchar_t titleName[512]={0};
	wchar_t className[512]={0};
	::GetWindowTextW(hwnd,titleName,512);
	::GetClassNameW(hwnd,className,512);
	CMyCatchMouseWindowInfo* mouseWnd = (CMyCatchMouseWindowInfo *)lParam;
	CString infoStr;
	infoStr.Format(_T("句柄:%x 类名:%s 标题:%s"),hwnd,className,titleName);
	mouseWnd->m_TreeWndList.InsertItem(infoStr,mouseWnd->m_hTree);

	return TRUE;
}

// CMyCatchMouseWindowInfo 对话框

IMPLEMENT_DYNAMIC(CMyCatchMouseWindowInfo, CMFCPropertyPage)

CMyCatchMouseWindowInfo::CMyCatchMouseWindowInfo()
	: CMFCPropertyPage(CMyCatchMouseWindowInfo::IDD)
	, m_Xpoint(0)
	, m_Ypoint(0)
{
	m_IsDrapCatch = false;
}

CMyCatchMouseWindowInfo::~CMyCatchMouseWindowInfo()
{
}

void CMyCatchMouseWindowInfo::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_WNDLIST, m_TreeWndList);
	DDX_Text(pDX, IDC_EDIT_XPOINT, m_Xpoint);
	DDX_Text(pDX, IDC_EDIT_YPOINT, m_Ypoint);
	DDX_Control(pDX, IDC_STATIC_TISHI, m_CatchTip);
	DDX_Control(pDX, IDC_STATIC_MOVEWNDCONTENT, m_MoveWndTip);
	DDX_Control(pDX, IDC_STATIC_PIC, m_DrapCtrl);
}


BEGIN_MESSAGE_MAP(CMyCatchMouseWindowInfo, CPropertyPage)
	ON_WM_CREATE()
	ON_WM_HOTKEY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CATCH, &CMyCatchMouseWindowInfo::OnBnClickedButtonCatch)
	ON_BN_CLICKED(IDC_BUTTON_COPYWNDCLASSNAME, &CMyCatchMouseWindowInfo::OnBnClickedButtonCopywndclassname)
	ON_BN_CLICKED(IDC_BUTTON_COPYTITLE, &CMyCatchMouseWindowInfo::OnBnClickedButtonCopytitle)
	ON_BN_CLICKED(IDC_BUTTON_OPRWND, &CMyCatchMouseWindowInfo::OnBnClickedButtonOprwnd)
	ON_EN_CHANGE(IDC_EDIT_XPOINT, &CMyCatchMouseWindowInfo::OnEnChangeEditXpoint)
	ON_EN_CHANGE(IDC_EDIT_YPOINT, &CMyCatchMouseWindowInfo::OnEnChangeEditYpoint)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_WNDLIST, &CMyCatchMouseWindowInfo::OnNMDblclkTreeWndlist)
END_MESSAGE_MAP()


// CMyCatchMouseWindowInfo 消息处理程序


BOOL CMyCatchMouseWindowInfo::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_STATIC_MOVEWNDCONTENT)->SetWindowTextW(_T("提示:进行移动窗口时请先停止捕获窗口信息操作。输入XY坐标,移动捕获窗口到指定坐标位置!"));

	m_ShowItem.Create(IDD_DIALOG_SUBWNDHANDLE,this);

	m_CatchTip.SetTextColor(RGB(6,121,50));
	m_MoveWndTip.SetTextColor(RGB(6,121,50));
	RegisterHotkey();           // 注册原有热键
	g_CatchWindowshWnd = this->m_hWnd;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


int CMyCatchMouseWindowInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHSCREEN,NULL,VK_F9);
	m_IsGetWnd=false;
	return 0;
}

void CMyCatchMouseWindowInfo::RegisterHotkey()
{
	if(m_hWnd ==NULL)
		return ;
	WORD keyCode =0, keyMode =0;
	CString hotStr = _T("");
	CWinApp* m_pApp = AfxGetApp();
	keyMode = m_pApp->GetProfileInt(_T("HOTKEYMODE"),_T("mousewnd"),0);
	keyCode = m_pApp->GetProfileInt(_T("HOTKEY"),_T("mousewnd"),VK_F9);
	hotStr = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("mousewnd"),_T("F9"));

	CString text = _T("");
	text.Format(_T("提示: %s为捕获/停止的快捷键"),hotStr);
	m_CatchTip.SetWindowTextW(text);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHSCREEN);
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHSCREEN,keyMode,keyCode);
}

void CMyCatchMouseWindowInfo::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nHotKeyId==IDC_USERHOTKEY_CATCHSCREEN)
	{
		if(!m_IsGetWnd)
		{
			////////// 获取///////
			// 启动定时器
			SetTimer(2,100,NULL);
			m_IsGetWnd=true;
			this->GetDlgItem(IDC_BUTTON_CATCH)->SetWindowTextW(_T("停止"));
		}
		else
		{
			////////停止//////
			// 关闭定时器
			this->KillTimer(2);
			m_IsGetWnd=false;
			this->GetDlgItem(IDC_BUTTON_CATCH)->SetWindowTextW(_T("捕获"));
			catchWndInfoInTimer();
			GetWndListTree();
		}
	
	}
	CMFCPropertyPage::OnHotKey(nHotKeyId, nKey1, nKey2);
}

/////处理定时器的捕获热键 -- 窗口信息
void CMyCatchMouseWindowInfo::catchWndInfoInTimer()
{
	static HWND oldHwnd=NULL;
	POINT pt;
	::GetCursorPos(&pt);                //得到鼠标移动坐标

	//////// 获取窗口句柄 //////
	HWND hwnd=::WindowFromPoint(pt);    //得到鼠标移动窗口句柄
	m_CurrWnd= hwnd;

	//////// 获取窗口标题 //////
	TCHAR titleName[512]={0};
	::GetWindowText(hwnd,titleName,512*sizeof(TCHAR));

	//////// 获取窗口类名 //////
	TCHAR className[512]={0};
	::GetClassName(hwnd,className,512*sizeof(TCHAR));

	//////////////////////  显示窗口的信息 /////////////////////////////
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDTITLE))->SetWindowTextW(titleName);
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDCLASS))->SetWindowTextW(className);
	CString handleStr;
	handleStr.Format(_T("%d"),(int)hwnd);
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDHANDLE))->SetWindowTextW(handleStr);

	///////////////// 获取窗口的区域大小 //////////////////////////////////
	CRect cWndRect;
	CRect cRect;
	::GetClientRect(hwnd,&cRect);
	::GetWindowRect(hwnd,&cWndRect);
	POINT tpoint;
	tpoint.x = cRect.left;
	tpoint.y = cRect.top;
	::ClientToScreen(hwnd,&tpoint);
	CString leftPort;
	//leftPort.Format(_T("%d,%d"),cWndRect.left,cWndRect.top);
	leftPort.Format(_T("%d,%d"),tpoint.x/*-cWndRect.left*/,tpoint.y/*-cWndRect.top*/);
	CString sizeWnd;
	sizeWnd.Format(_T("%d,%d"),cRect.Width(),cRect.Height());
	((CEdit*)this->GetDlgItem(IDC_EDIT_LEFTPOINT))->SetWindowTextW(leftPort);
	((CEdit*)this->GetDlgItem(IDC_EDIT_CLIENTSIZE))->SetWindowTextW(sizeWnd);

	////////////////////////////拖动图标就画线///////////////////////////////////
	if(m_IsDrapCatch)
	{
		CRect paintRect;
		::GetClientRect(hwnd,&paintRect);
		HWND helphWnd = ::GetDesktopWindow();
		HDC DeskDC = ::GetWindowDC(hwnd);     //取得窗口设备场景
		POINT cPoint;
		cPoint.x = paintRect.left;
		cPoint.y = paintRect.top;
		//::ClientToScreen(hwnd,&cPoint);
		int oldRop2 = SetROP2(DeskDC, R2_NOTXORPEN);
		HPEN newPen = ::CreatePen(0, 3, RGB(125,0,125));    //建立新画笔,载入DeskDC
		HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);
		int penWidth = 1;
		::Rectangle(DeskDC, cPoint.x, cPoint.y, 
			cPoint.x + paintRect.Width(), cPoint.y + paintRect.Height());  //在指示窗口周围显示闪烁矩形
		Sleep(100);
		::Rectangle(DeskDC, cPoint.x, cPoint.y, 
			cPoint.x + paintRect.Width(), cPoint.y + paintRect.Height());  //在指示窗口周围显示闪烁矩形
		::SetROP2(DeskDC, oldRop2);
		::SelectObject( DeskDC, oldPen);
		::DeleteObject(newPen);
		::ReleaseDC( hwnd, DeskDC);
		DeskDC = NULL;
	}
	///////////////////////////////////////////////////////////////////////////
	return;
}


void CMyCatchMouseWindowInfo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==2)
	{
		m_IsDrapCatch = false;
		catchWndInfoInTimer();
		//static HWND oldHwnd=NULL;
		//POINT pt;
		//::GetCursorPos(&pt);                //得到鼠标移动坐标

		////////// 获取窗口句柄 //////
		//HWND hwnd=::WindowFromPoint(pt);    //得到鼠标移动窗口句柄

		//m_CurrWnd= hwnd;

		////////// 获取窗口标题 //////
		//TCHAR titleName[512]={0};
		//::GetWindowText(hwnd,titleName,512*sizeof(TCHAR));

		////////// 获取窗口类名 //////
		//TCHAR className[512]={0};
		//::GetClassName(hwnd,className,512*sizeof(TCHAR));

		////////////////////////  显示窗口的信息 /////////////////////////////
		//((CEdit*)this->GetDlgItem(IDC_EDIT_WNDTITLE))->SetWindowTextW(titleName);
		//((CEdit*)this->GetDlgItem(IDC_EDIT_WNDCLASS))->SetWindowTextW(className);
		//CString handleStr;
		//handleStr.Format(_T("%d"),(int)hwnd);
		//((CEdit*)this->GetDlgItem(IDC_EDIT_WNDHANDLE))->SetWindowTextW(handleStr);

		/////////////////// 获取窗口的区域大小 //////////////////////////////////
		//CRect cWndRect;
		//CRect cRect;
		//::GetClientRect(hwnd,&cRect);
		//::GetWindowRect(hwnd,&cWndRect);
		//POINT tpoint;
		//tpoint.x = cRect.left;
		//tpoint.y = cRect.top;
		//::ClientToScreen(hwnd,&tpoint);
		//CString leftPort;
		////leftPort.Format(_T("%d,%d"),cWndRect.left,cWndRect.top);
		//leftPort.Format(_T("%d,%d"),tpoint.x/*-cWndRect.left*/,tpoint.y/*-cWndRect.top*/);
		//CString sizeWnd;
		//sizeWnd.Format(_T("%d,%d"),cRect.Width(),cRect.Height());
		//((CEdit*)this->GetDlgItem(IDC_EDIT_LEFTPOINT))->SetWindowTextW(leftPort);
		//((CEdit*)this->GetDlgItem(IDC_EDIT_CLIENTSIZE))->SetWindowTextW(sizeWnd);
	}
	else if(nIDEvent==1)
	{
		m_IsDrapCatch = true;
		catchWndInfoInTimer();
	}
	CMFCPropertyPage::OnTimer(nIDEvent);
}


void CMyCatchMouseWindowInfo::OnBnClickedButtonCatch()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_IsGetWnd)
	{
		////////// 获取///////
		// 启动定时器
		SetTimer(2,100,NULL);
		m_IsGetWnd=true;
		this->GetDlgItem(IDC_BUTTON_CATCH)->SetWindowTextW(_T("停止"));
	}
	else
	{
		////////停止//////
		// 关闭定时器
		this->KillTimer(2);
		m_IsGetWnd=false;
		this->GetDlgItem(IDC_BUTTON_CATCH)->SetWindowTextW(_T("捕获"));

		GetWndListTree();
	}
}


void CMyCatchMouseWindowInfo::OnBnClickedButtonCopywndclassname()
{
	// TODO: 在此添加控件通知处理程序代码
	CString className=_T("");
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDCLASS))->GetWindowTextW(className);

	HANDLE hClip;
	if(::OpenClipboard(NULL))
	{
		//将剪贴板内容清空
		EmptyClipboard();
		//字节长度
		int leng=(className.GetLength()+1)*sizeof(TCHAR);
		//在堆上分配可移动的内存块，程序返回一个内存句柄
		hClip=GlobalAlloc(GHND | GMEM_SHARE,leng);
		//定义指向字符型的指针变量
		TCHAR * buff;
		//对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加一
		buff=(TCHAR *)GlobalLock(hClip);
		//将用户输入的数据拷贝到指针变量中，实际上就是拷贝到分配的内存块中
		memcpy(buff,className,leng);
		//数据写入完毕，进行解锁操作，并将引用计数器数字减一
		GlobalUnlock(hClip);
		//将存放有数据的内存块放入剪贴板的资源管理中
		HANDLE help = SetClipboardData(/*CF_TEXT*/CF_UNICODETEXT,hClip);
		//关闭剪贴板，释放剪贴板资源的占用权
		GlobalFree(hClip);
		CloseClipboard();
	}
	::AfxMessageBox(_T("窗口类型名已经复制到剪切板中!"));
	return;
}


void CMyCatchMouseWindowInfo::OnBnClickedButtonCopytitle()
{
	// TODO: 在此添加控件通知处理程序代码
	CString titleName=_T("");
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDTITLE))->GetWindowTextW(titleName);

	HANDLE hClip;
	if(::OpenClipboard(NULL))
	{
		//将剪贴板内容清空
		EmptyClipboard();
		//字节长度
		int leng=(titleName.GetLength()+1)*sizeof(TCHAR);
		//在堆上分配可移动的内存块，程序返回一个内存句柄
		hClip=GlobalAlloc(GHND | GMEM_SHARE,leng);
		//定义指向字符型的指针变量
		TCHAR * buff;
		//对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加一
		buff=(TCHAR *)GlobalLock(hClip);
		//将用户输入的数据拷贝到指针变量中，实际上就是拷贝到分配的内存块中
		memcpy(buff,titleName,leng);
		//数据写入完毕，进行解锁操作，并将引用计数器数字减一
		GlobalUnlock(hClip);
		//将存放有数据的内存块放入剪贴板的资源管理中
		HANDLE help = SetClipboardData(/*CF_TEXT*/CF_UNICODETEXT,hClip);
		//关闭剪贴板，释放剪贴板资源的占用权
		GlobalFree(hClip);
		CloseClipboard();
	}
	::AfxMessageBox(_T("窗口标题名已经复制到剪切板中!"));
	return ;
}


void CMyCatchMouseWindowInfo::OnBnClickedButtonOprwnd()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();
	if(!m_IsGetWnd)
	{
		::SetWindowPos(m_CurrWnd,HWND_NOTOPMOST,m_Xpoint,m_Ypoint,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	}
	else
	{
		::AfxMessageBox(_T("请先停止抓窗口再进行移动窗口功能!!!!"));
	}
}


void CMyCatchMouseWindowInfo::OnEnChangeEditXpoint()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strTemp=_T("");
	CEdit* editHelp = ((CEdit*)(GetDlgItem(IDC_EDIT_XPOINT)));
	editHelp->GetWindowText(strTemp);
	int len = strTemp.GetLength();
	for (int i = 0; i < len; i ++)
	{
		if(strTemp.GetAt(i) < '0' || strTemp.GetAt(i) > '9')
		{
			strTemp = strTemp.Left(i);
			editHelp->SetWindowText(strTemp);
			editHelp->SetSel(i,i,TRUE);
			return;
		}
	}
}


void CMyCatchMouseWindowInfo::OnEnChangeEditYpoint()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strTemp=_T("");
	CEdit* editHelp = ((CEdit*)(GetDlgItem(IDC_EDIT_YPOINT)));
	editHelp->GetWindowText(strTemp);
	int len = strTemp.GetLength();
	for (int i = 0; i < len; i ++)
	{
		if(strTemp.GetAt(i) < '0' || strTemp.GetAt(i) > '9')
		{
			strTemp = strTemp.Left(i);
			editHelp->SetWindowText(strTemp);
			editHelp->SetSel(i,i,TRUE);
			return;
		}
	}
}


void CMyCatchMouseWindowInfo::GetWndListTree()
{
	m_TreeWndList.DeleteAllItems();

	m_hTree = m_TreeWndList.InsertItem(_T(" 当前窗口的所有子窗口:"), TVI_ROOT);

	::EnumChildWindows(m_CurrWnd,EnumChildProc,(LPARAM)this);

	m_TreeWndList.Expand(m_hTree,TVE_EXPAND);

	return;
}


void CMyCatchMouseWindowInfo::OnNMDblclkTreeWndlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	HTREEITEM hSel=m_TreeWndList.GetSelectedItem();//取得选项句柄;
	if(hSel==NULL)
	{
		return;//无任何选项则返回
	}
	CString cText=m_TreeWndList.GetItemText(hSel);//取得数据项名

	if(cText.IsEmpty())
	{
		return;
	}
	// "窗口句柄:%x 类名:%s 标题:%s"
	CString wnd;
	CString wndclass;
	CString wndtitlle;
	cText = cText.Right(cText.GetLength() - 3);
	int pos = cText.Find(_T("类名:"));
	wnd = cText.Left(pos);

	cText = cText.Right(cText.GetLength() - pos - 3);
	pos = cText.Find(_T("标题:"));
	wndclass = cText.Left(pos);
	wndtitlle = cText.Right(cText.GetLength() - pos - 3);
	
	m_ShowItem.AddWndHandle(wnd,wndclass,wndtitlle);
	//m_ShowItem.DoModal();
	m_ShowItem.ShowWindow(TRUE);

	//LONG IDs=m_TreeWndList.GetItemData(hSel);//取得数据项序号
	//::AfxMessageBox(cText);
}
