#include "StdAfx.h"
#include "ABץץ.h"
#include "MyInterfacePropSheet.h"
#include "afxdialogex.h"
#include "MySettingDlgClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CMyPickerColor		g_PickColorDlg;  
//extern  CMyDrawPictureClass	g_DrawPicture;
extern  CButton				g_PicCheck;
extern  HWND				g_MainFormHwnd;

/////////////////////////////////////////////////////////////////////////////
// NewControlsPropSheet

IMPLEMENT_DYNAMIC(CMyInterfacePropSheet, CMFCPropertySheet)

CMyInterfacePropSheet::CMyInterfacePropSheet(CWnd* pParentWnd)
:CMFCPropertySheet(IDS_CAPTION, pParentWnd)
{	
	m_psh.dwFlags |= PSH_NOAPPLYNOW ; //ȥ����Ӧ�á���ť 
	m_psh.dwFlags &=~PSH_HASHELP;     //ȥ������������ť	

	SetLook(CMFCPropertySheet::PropSheetLook_OutlookBar);
	//SetIconsList(IDB_ICONS, 32,RGB(255,255,255));
	//SetIconsList(IDB_ICONS,32,RGB(255,255,255));
	SetIconsList(IDB_ICONS,32,RGB(5,2,6));

	AddPage(&m_ColorInfo);
	AddPage(&m_PicInfoPage);
	AddPage(&m_CatchWndInfo);
	AddPage(&m_CatchMouseShape);
	AddPage(&m_DrawPicWnd);
	AddPage(&m_CatchWebElem);
	//this->SetActivePage();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMyInterfacePropSheet::~CMyInterfacePropSheet()
{
}

BEGIN_MESSAGE_MAP(CMyInterfacePropSheet, CMFCPropertySheet)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDOK, &CMyInterfacePropSheet::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SHOWCATCHCOLOR, &CMyInterfacePropSheet::OnBnClickedShowGetColorCheckButton)
	ON_BN_CLICKED(IDC_BUTTON_SHOWPICTURE, &CMyInterfacePropSheet::OnBnClickedShowPicCheckButton)
	ON_BN_CLICKED(IDC_BUTTON_SHOWSETTING, &CMyInterfacePropSheet::OnClickShowSetting)
	ON_WM_TIMER()
	//ON_MESSAGE(IDC_USER_CLOSEPICKERWND,OnClosePickerMSG)
	//ON_MESSAGE(IDC_USER_CLOSEMAKEPICWND,OnCloseMakePicMSG)
	ON_WM_DESTROY()
//	ON_WM_CLOSE()
//ON_WM_NCPAINT()
//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewControlsPropSheet message handlers

BOOL CMyInterfacePropSheet::OnInitDialog()
{
	BOOL bResult = CMFCPropertySheet::OnInitDialog();
	CMenu*   pSysMenu   =   GetSystemMenu(FALSE);  
	if(pSysMenu   !=   NULL)
	{
		pSysMenu->AppendMenu(MF_STRING,SC_MINIMIZE,_T("��С��"));  
		//pSysMenu->AppendMenu(MF_STRING,   SC_MAXIMIZE,   L"���");  
		ModifyStyle(0,WS_MINIMIZEBOX/* |WS_MAXIMIZEBOX*/);
	}

	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	///////����ȫ�ֵ�����//////
	afxGlobalData.fontRegular.DeleteObject();
    afxGlobalData.fontRegular.CreateFont(
        12,                        // nHeight
        0,                         // nWidth
        0,                         // nEscapement
        0,                         // nOrientation
        FW_NORMAL,                 // nWeight
        FALSE,                     // bItalic
        FALSE,                     // bUnderline
        0,                         // cStrikeOut
        ANSI_CHARSET,              // nCharSet
        OUT_DEFAULT_PRECIS,        // nOutPrecision
        CLIP_DEFAULT_PRECIS, 
        DEFAULT_QUALITY,           // nQuality
        DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
        _T("����"));

	////////////////////////////////��ʾȡɫ��/////////
	RECT rct;
	this->GetClientRect(&rct);	
	rct.left = rct.left+20;
	rct.top = rct.bottom-30;
	rct.right = rct.left+100;
	rct.bottom = rct.bottom-10;
	m_ColorCheck.Create(_T("��ʾȡɫ��"), WS_CHILD|WS_VISIBLE|BS_CHECKBOX,rct,this,IDC_BUTTON_SHOWCATCHCOLOR);
	
	rct.left = rct.left+110;
	rct.right = rct.left+50;
	m_BtnSetting.Create(_T("����"),WS_CHILD|WS_VISIBLE,rct,this,IDC_BUTTON_SHOWSETTING);

	///////��������//////
	CFont* pFont = GetFont();
	if (!pFont) {
		HFONT hFont = (HFONT)GetStockObject (DEFAULT_GUI_FONT);
		if (NULL == hFont) {
			hFont = (HFONT) GetStockObject (ANSI_VAR_FONT);
		}
		if (hFont) {
			pFont = CFont::FromHandle (hFont);
		}
	}
	ASSERT (pFont->GetSafeHandle ());
	m_ColorCheck.SetFont(pFont);
	m_ColorCheck.ShowWindow(TRUE);
	m_BtnSetting.SetFont(pFont);
	m_ColorCheck.SetCheck(BST_CHECKED);

	//////////////////////////////////������͸��ͼ����/////////
	//rct.left = rct.left+110;
	//rct.right = rct.left+150;
	//g_PicCheck.Create(_T("������͸��ͼ����"), WS_CHILD|WS_VISIBLE|BS_CHECKBOX,rct,this,IDC_BUTTON_SHOWPICTURE);
	//g_PicCheck.SetFont(pFont);
	//g_PicCheck.ShowWindow(TRUE);
	//g_PicCheck.SetCheck(BST_UNCHECKED);
	//////////////////////�����ȼ�//////////////////////////////
	
	//////////////////  ����ȡɫ������  ///////////////
	g_PickColorDlg.Create(IDD_DIALOG_PICKCOLOR);
	g_PickColorDlg.ShowWindow(TRUE);

	/*
	int state = pApp->GetProfileInt(_T("ABDATA"),_T("ABSTATE"), 0);*/
	//m_ColorCheck.SetCheck(state);
	//g_PickColorDlg.ShowWindow(state);
		
	////////////////////  ����������ͼ���� ///////////////
	/*g_DrawPicture.Create(IDD_DIALOG_DRAWPICTURE);
	g_DrawPicture.ShowWindow(FALSE);*/

	this->GetDlgItem(IDOK)->ShowWindow(FALSE);
	this->GetDlgItem(IDCANCEL)->ShowWindow(FALSE);

	g_MainFormHwnd = this->m_hWnd;
	this->SetTimer(101,500,NULL);  // ���ABץץ��ȡɫ���Ƿ��
	//CString text = _T("");
	//::GetPrivateProfileString(_T("ABDATA"),_T("INDEX"),_T("1"),text.GetBuffer(10),10,_T(".\\ColorInfo.ini"));
	//text.ReleaseBuffer();
	CWinApp* pApp = AfxGetApp();
	int index = pApp->GetProfileInt(_T("ABDATA"),_T("INDEX"), 1);
	this->SetActivePage(index);
	return bResult;
}

HCURSOR CMyInterfacePropSheet::OnQueryDragIcon()
{
	return(HCURSOR) m_hIcon;
}

void CMyInterfacePropSheet::OnSysCommand(UINT nID, LPARAM lParam)
{	
	CMFCPropertySheet::OnSysCommand(nID, lParam);
}
//
void CMyInterfacePropSheet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CMFCPropertySheet::OnOK();
}

void CMyInterfacePropSheet::OnBnClickedShowGetColorCheckButton()
{
	if(m_ColorCheck.GetCheck() == BST_CHECKED)
	{
		this->KillTimer(101);
		m_ColorCheck.SetCheck(BST_UNCHECKED);
		g_PickColorDlg.ShowWindow(FALSE);
	}
	else
	{
		m_ColorCheck.SetCheck(BST_CHECKED);
		g_PickColorDlg.ShowWindow(TRUE);
		this->SetTimer(101,500,NULL);
	}
}

void CMyInterfacePropSheet::OnBnClickedShowPicCheckButton()
{
	//if(g_PicCheck.GetCheck() == BST_CHECKED)
	//{
	//	this->KillTimer(102);
	//	g_PicCheck.SetCheck(BST_UNCHECKED);
	//	//m_DrawPicture.ShowWindow(FALSE);
	//	//g_DrawPicture.ShowWindow(FALSE);
	//}
	//else
	//{
	//	g_PicCheck.SetCheck(BST_CHECKED);
	//	//m_DrawPicture.ShowWindow(TRUE);
	//	//g_DrawPicture.ShowWindow(TRUE);
	//	this->SetTimer(102,100,NULL);
	//}
}

void CMyInterfacePropSheet::OnClickShowSetting()
{
	CMySettingDlgClass settingDlg;
	settingDlg.DoModal();
}

BOOL CMyInterfacePropSheet::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	//cs.style = cs.style|WS_MINIMIZEBOX|WS_SYSMENU;
	return CMFCPropertySheet::PreCreateWindow(cs);
}


BOOL CMyInterfacePropSheet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->wParam==VK_UP&&pMsg->message==WM_KEYDOWN)
	{
		POINT pt;
		::GetCursorPos(&pt);
		pt.y=pt.y-1;
		::SetCursorPos(pt.x,pt.y);
		return TRUE;
	}
	else if(pMsg->wParam==VK_DOWN&&pMsg->message==WM_KEYDOWN)
	{
		POINT pt;
		::GetCursorPos(&pt);
		pt.y=pt.y+1;
		::SetCursorPos(pt.x,pt.y);
		return TRUE;
	}
	else if(pMsg->wParam==VK_LEFT&&pMsg->message==WM_KEYDOWN)
	{
		POINT pt;
		::GetCursorPos(&pt);
		pt.x=pt.x-1;
		::SetCursorPos(pt.x,pt.y);
		return TRUE;
	}
	else if(pMsg->wParam==VK_RIGHT&&pMsg->message==WM_KEYDOWN)
	{
		POINT pt;
		::GetCursorPos(&pt);
		pt.x=pt.x+1;
		::SetCursorPos(pt.x,pt.y);
		return TRUE;
	}
	return CMFCPropertySheet::PreTranslateMessage(pMsg);
}

void CMyInterfacePropSheet::activeCurrentPage(int page)
{
	//SetActivePage(page);
	switch(page)
	{
	case 1:
		this->SetActivePage(0);
		break;
	case 2:
		this->SetActivePage(1);
		break;
	case 3:
		this->SetActivePage(2);
		break;
	case 4:
		this->SetActivePage(3);
		break;
	case 5:
		this->SetActivePage(4); 
		break;
	case 6:
		this->SetActivePage(5); 
		break;
	default:
		this->SetActivePage(0);          /////Ĭ�ϼ����һ������ҳ
		break;
	}
	return ;
}

void CMyInterfacePropSheet::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == 101)    // ���ABץץ��ȡɫ���Ƿ��
	{
		if(!g_PickColorDlg.IsWindowVisible())
		{
			m_ColorCheck.SetCheck(BST_UNCHECKED);
			this->KillTimer(101);
		}
		else
		{
			m_ColorCheck.SetCheck(BST_CHECKED);
		}
	}
	//if(nIDEvent == 102)
	//{
	//	/*if(!g_DrawPicture.IsWindowVisible())
	//	{
	//		g_PicCheck.SetCheck(BST_UNCHECKED);
	//		this->KillTimer(102);
	//	}*/
	//}
	CMFCPropertySheet::OnTimer(nIDEvent);
}

//LRESULT CMyInterfacePropSheet::OnClosePickerMSG(WPARAM, LPARAM)
//{
//	//m_ColorCheck.SetCheck(BST_UNCHECKED);
//	return 0;
//}
//
//LRESULT CMyInterfacePropSheet::OnCloseMakePicMSG(WPARAM, LPARAM)
//{
//	g_PicCheck.SetCheck(BST_UNCHECKED);
//	return 0;
//}

void CMyInterfacePropSheet::OnDestroy()
{
	CWinApp* pApp = AfxGetApp();
//	RECT rect;
	//::GetWindowRect(this->m_hWnd,&rect);
	//CString text = _T("");
	//text.Format(_T("%d"),rect.left);
	//::WritePrivateProfileString(_T("ABDATA"),_T("ABLEFT"),text,_T(".\\ColorInfo.ini"));
	//text.Format(_T("%d"),rect.top);
	//::WritePrivateProfileString(_T("ABDATA"),_T("ABTOP"),text,_T(".\\ColorInfo.ini"));

	CMFCPropertySheet::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
	//pApp->WriteProfileInt(_T("ABDATA"),_T("ABLEFT"), rect.left);
	//pApp->WriteProfileInt(_T("ABDATA"),_T("ABTOP"), rect.top);
	//////////////////��¼�û�ѡ�����ĸ��˵�///////////////////////////////////
	int pageIndex = this->GetActiveIndex();
	pApp->WriteProfileInt(_T("ABDATA"),_T("INDEX"), pageIndex);
	//CString text = _T("");
	//text.Format(_T("%d"),pageIndex);
	//::WritePrivateProfileString(_T("ABDATA"),_T("INDEX"),text,_T(".\\ColorInfo.ini"));

	int state = m_ColorCheck.GetCheck();	
	pApp->WriteProfileInt(_T("ABDATA"),_T("ABSTATE"), state);
}


//void CMyInterfacePropSheet::OnClose()
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	
//	//////////////////��¼�û�ѡ�����ĸ��˵�///////////////////////////////////
//	int pageIndex = this->GetActiveIndex();
//	CString text = _T("");
//	text.Format(_T("%d"),pageIndex);
//	::WritePrivateProfileString(_T("ABDATA"),_T("INDEX"),text,_T(".\\ColorInfo.ini"));
//
//	CMFCPropertySheet::OnClose();
//}


//void CMyInterfacePropSheet::OnNcPaint()
//{
//	// TODO: �ڴ˴������Ϣ����������
//	// ��Ϊ��ͼ��Ϣ���� CMFCPropertySheet::OnNcPaint()
//
//	//CDC* pDC = GetWindowDC();
//	//if(pDC)
//	//{
//	//	CBitmap bitmap;
//	//	bitmap.LoadBitmapW(IDB_BITMAP2);
//	//	CDC cDC;
//	//	cDC.CreateCompatibleDC(NULL);
//	//	cDC.SelectObject(bitmap.GetSafeHandle());
//	//	
//	//	CRect rect,btnRect;
//	//	GetWindowRect(&rect);
//	//	rect = CRect(0,0,rect.Width(),rect.Height());
//	//	//cDC.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
//	//	btnRect = CRect(rect.right - 110 + 30,rect.top+2,rect.right -110,rect.top + 22);
//	//	//pDC->BitBlt(btnRect.left,btnRect.top,btnRect.Width(),btnRect.Height(),&cDC,0,0,SRCCOPY);
//	//	pDC->StretchBlt(btnRect.left,btnRect.top,btnRect.Width(),btnRect.Height(),&cDC,0,0,28,18,SRCCOPY);
//	//	ReleaseDC(pDC);
//	//	cDC.DeleteDC();
//	//	bitmap.DeleteObject();
//	//}
//}


//BOOL CMyInterfacePropSheet::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	//OnNcPaint();
//	return TRUE;
//	//return CMFCPropertySheet::OnEraseBkgnd(pDC);
//}
