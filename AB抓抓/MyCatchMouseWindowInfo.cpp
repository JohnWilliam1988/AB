// MyCatchMouseWindowInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyCatchMouseWindowInfo.h"
#include "afxdialogex.h"

extern HWND g_CatchWindowshWnd;
//�ȼ���Դ
#define IDC_USERHOTKEY_CATCHSCREEN                   WM_USER+150

///////////////////////////ö���Ӵ���//////////////
BOOL CALLBACK EnumChildProc(HWND hwnd,LPARAM lParam)
{
	wchar_t titleName[512]={0};
	wchar_t className[512]={0};
	::GetWindowTextW(hwnd,titleName,512);
	::GetClassNameW(hwnd,className,512);
	CMyCatchMouseWindowInfo* mouseWnd = (CMyCatchMouseWindowInfo *)lParam;
	CString infoStr;
	infoStr.Format(_T("���:%x ����:%s ����:%s"),hwnd,className,titleName);
	mouseWnd->m_TreeWndList.InsertItem(infoStr,mouseWnd->m_hTree);

	return TRUE;
}

// CMyCatchMouseWindowInfo �Ի���

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


// CMyCatchMouseWindowInfo ��Ϣ�������


BOOL CMyCatchMouseWindowInfo::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC_MOVEWNDCONTENT)->SetWindowTextW(_T("��ʾ:�����ƶ�����ʱ����ֹͣ���񴰿���Ϣ����������XY����,�ƶ����񴰿ڵ�ָ������λ��!"));

	m_ShowItem.Create(IDD_DIALOG_SUBWNDHANDLE,this);

	m_CatchTip.SetTextColor(RGB(6,121,50));
	m_MoveWndTip.SetTextColor(RGB(6,121,50));
	RegisterHotkey();           // ע��ԭ���ȼ�
	g_CatchWindowshWnd = this->m_hWnd;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


int CMyCatchMouseWindowInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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
	text.Format(_T("��ʾ: %sΪ����/ֹͣ�Ŀ�ݼ�"),hotStr);
	m_CatchTip.SetWindowTextW(text);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHSCREEN);
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHSCREEN,keyMode,keyCode);
}

void CMyCatchMouseWindowInfo::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nHotKeyId==IDC_USERHOTKEY_CATCHSCREEN)
	{
		if(!m_IsGetWnd)
		{
			////////// ��ȡ///////
			// ������ʱ��
			SetTimer(2,100,NULL);
			m_IsGetWnd=true;
			this->GetDlgItem(IDC_BUTTON_CATCH)->SetWindowTextW(_T("ֹͣ"));
		}
		else
		{
			////////ֹͣ//////
			// �رն�ʱ��
			this->KillTimer(2);
			m_IsGetWnd=false;
			this->GetDlgItem(IDC_BUTTON_CATCH)->SetWindowTextW(_T("����"));
			catchWndInfoInTimer();
			GetWndListTree();
		}
	
	}
	CMFCPropertyPage::OnHotKey(nHotKeyId, nKey1, nKey2);
}

/////����ʱ���Ĳ����ȼ� -- ������Ϣ
void CMyCatchMouseWindowInfo::catchWndInfoInTimer()
{
	static HWND oldHwnd=NULL;
	POINT pt;
	::GetCursorPos(&pt);                //�õ�����ƶ�����

	//////// ��ȡ���ھ�� //////
	HWND hwnd=::WindowFromPoint(pt);    //�õ�����ƶ����ھ��
	m_CurrWnd= hwnd;

	//////// ��ȡ���ڱ��� //////
	TCHAR titleName[512]={0};
	::GetWindowText(hwnd,titleName,512*sizeof(TCHAR));

	//////// ��ȡ�������� //////
	TCHAR className[512]={0};
	::GetClassName(hwnd,className,512*sizeof(TCHAR));

	//////////////////////  ��ʾ���ڵ���Ϣ /////////////////////////////
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDTITLE))->SetWindowTextW(titleName);
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDCLASS))->SetWindowTextW(className);
	CString handleStr;
	handleStr.Format(_T("%d"),(int)hwnd);
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDHANDLE))->SetWindowTextW(handleStr);

	///////////////// ��ȡ���ڵ������С //////////////////////////////////
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

	////////////////////////////�϶�ͼ��ͻ���///////////////////////////////////
	if(m_IsDrapCatch)
	{
		CRect paintRect;
		::GetClientRect(hwnd,&paintRect);
		HWND helphWnd = ::GetDesktopWindow();
		HDC DeskDC = ::GetWindowDC(hwnd);     //ȡ�ô����豸����
		POINT cPoint;
		cPoint.x = paintRect.left;
		cPoint.y = paintRect.top;
		//::ClientToScreen(hwnd,&cPoint);
		int oldRop2 = SetROP2(DeskDC, R2_NOTXORPEN);
		HPEN newPen = ::CreatePen(0, 3, RGB(125,0,125));    //�����»���,����DeskDC
		HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);
		int penWidth = 1;
		::Rectangle(DeskDC, cPoint.x, cPoint.y, 
			cPoint.x + paintRect.Width(), cPoint.y + paintRect.Height());  //��ָʾ������Χ��ʾ��˸����
		Sleep(100);
		::Rectangle(DeskDC, cPoint.x, cPoint.y, 
			cPoint.x + paintRect.Width(), cPoint.y + paintRect.Height());  //��ָʾ������Χ��ʾ��˸����
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent==2)
	{
		m_IsDrapCatch = false;
		catchWndInfoInTimer();
		//static HWND oldHwnd=NULL;
		//POINT pt;
		//::GetCursorPos(&pt);                //�õ�����ƶ�����

		////////// ��ȡ���ھ�� //////
		//HWND hwnd=::WindowFromPoint(pt);    //�õ�����ƶ����ھ��

		//m_CurrWnd= hwnd;

		////////// ��ȡ���ڱ��� //////
		//TCHAR titleName[512]={0};
		//::GetWindowText(hwnd,titleName,512*sizeof(TCHAR));

		////////// ��ȡ�������� //////
		//TCHAR className[512]={0};
		//::GetClassName(hwnd,className,512*sizeof(TCHAR));

		////////////////////////  ��ʾ���ڵ���Ϣ /////////////////////////////
		//((CEdit*)this->GetDlgItem(IDC_EDIT_WNDTITLE))->SetWindowTextW(titleName);
		//((CEdit*)this->GetDlgItem(IDC_EDIT_WNDCLASS))->SetWindowTextW(className);
		//CString handleStr;
		//handleStr.Format(_T("%d"),(int)hwnd);
		//((CEdit*)this->GetDlgItem(IDC_EDIT_WNDHANDLE))->SetWindowTextW(handleStr);

		/////////////////// ��ȡ���ڵ������С //////////////////////////////////
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_IsGetWnd)
	{
		////////// ��ȡ///////
		// ������ʱ��
		SetTimer(2,100,NULL);
		m_IsGetWnd=true;
		this->GetDlgItem(IDC_BUTTON_CATCH)->SetWindowTextW(_T("ֹͣ"));
	}
	else
	{
		////////ֹͣ//////
		// �رն�ʱ��
		this->KillTimer(2);
		m_IsGetWnd=false;
		this->GetDlgItem(IDC_BUTTON_CATCH)->SetWindowTextW(_T("����"));

		GetWndListTree();
	}
}


void CMyCatchMouseWindowInfo::OnBnClickedButtonCopywndclassname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString className=_T("");
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDCLASS))->GetWindowTextW(className);

	HANDLE hClip;
	if(::OpenClipboard(NULL))
	{
		//���������������
		EmptyClipboard();
		//�ֽڳ���
		int leng=(className.GetLength()+1)*sizeof(TCHAR);
		//�ڶ��Ϸ�����ƶ����ڴ�飬���򷵻�һ���ڴ���
		hClip=GlobalAlloc(GHND | GMEM_SHARE,leng);
		//����ָ���ַ��͵�ָ�����
		TCHAR * buff;
		//�Է�����ڴ����м��������ڴ����ת����һ��ָ��,������Ӧ�����ü�������һ
		buff=(TCHAR *)GlobalLock(hClip);
		//���û���������ݿ�����ָ������У�ʵ���Ͼ��ǿ�����������ڴ����
		memcpy(buff,className,leng);
		//����д����ϣ����н����������������ü��������ּ�һ
		GlobalUnlock(hClip);
		//����������ݵ��ڴ�������������Դ������
		HANDLE help = SetClipboardData(/*CF_TEXT*/CF_UNICODETEXT,hClip);
		//�رռ����壬�ͷż�������Դ��ռ��Ȩ
		GlobalFree(hClip);
		CloseClipboard();
	}
	::AfxMessageBox(_T("�����������Ѿ����Ƶ����а���!"));
	return;
}


void CMyCatchMouseWindowInfo::OnBnClickedButtonCopytitle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString titleName=_T("");
	((CEdit*)this->GetDlgItem(IDC_EDIT_WNDTITLE))->GetWindowTextW(titleName);

	HANDLE hClip;
	if(::OpenClipboard(NULL))
	{
		//���������������
		EmptyClipboard();
		//�ֽڳ���
		int leng=(titleName.GetLength()+1)*sizeof(TCHAR);
		//�ڶ��Ϸ�����ƶ����ڴ�飬���򷵻�һ���ڴ���
		hClip=GlobalAlloc(GHND | GMEM_SHARE,leng);
		//����ָ���ַ��͵�ָ�����
		TCHAR * buff;
		//�Է�����ڴ����м��������ڴ����ת����һ��ָ��,������Ӧ�����ü�������һ
		buff=(TCHAR *)GlobalLock(hClip);
		//���û���������ݿ�����ָ������У�ʵ���Ͼ��ǿ�����������ڴ����
		memcpy(buff,titleName,leng);
		//����д����ϣ����н����������������ü��������ּ�һ
		GlobalUnlock(hClip);
		//����������ݵ��ڴ�������������Դ������
		HANDLE help = SetClipboardData(/*CF_TEXT*/CF_UNICODETEXT,hClip);
		//�رռ����壬�ͷż�������Դ��ռ��Ȩ
		GlobalFree(hClip);
		CloseClipboard();
	}
	::AfxMessageBox(_T("���ڱ������Ѿ����Ƶ����а���!"));
	return ;
}


void CMyCatchMouseWindowInfo::OnBnClickedButtonOprwnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData();
	if(!m_IsGetWnd)
	{
		::SetWindowPos(m_CurrWnd,HWND_NOTOPMOST,m_Xpoint,m_Ypoint,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	}
	else
	{
		::AfxMessageBox(_T("����ֹͣץ�����ٽ����ƶ����ڹ���!!!!"));
	}
}


void CMyCatchMouseWindowInfo::OnEnChangeEditXpoint()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CMFCPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CMFCPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

	m_hTree = m_TreeWndList.InsertItem(_T(" ��ǰ���ڵ������Ӵ���:"), TVI_ROOT);

	::EnumChildWindows(m_CurrWnd,EnumChildProc,(LPARAM)this);

	m_TreeWndList.Expand(m_hTree,TVE_EXPAND);

	return;
}


void CMyCatchMouseWindowInfo::OnNMDblclkTreeWndlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	HTREEITEM hSel=m_TreeWndList.GetSelectedItem();//ȡ��ѡ����;
	if(hSel==NULL)
	{
		return;//���κ�ѡ���򷵻�
	}
	CString cText=m_TreeWndList.GetItemText(hSel);//ȡ����������

	if(cText.IsEmpty())
	{
		return;
	}
	// "���ھ��:%x ����:%s ����:%s"
	CString wnd;
	CString wndclass;
	CString wndtitlle;
	cText = cText.Right(cText.GetLength() - 3);
	int pos = cText.Find(_T("����:"));
	wnd = cText.Left(pos);

	cText = cText.Right(cText.GetLength() - pos - 3);
	pos = cText.Find(_T("����:"));
	wndclass = cText.Left(pos);
	wndtitlle = cText.Right(cText.GetLength() - pos - 3);
	
	m_ShowItem.AddWndHandle(wnd,wndclass,wndtitlle);
	//m_ShowItem.DoModal();
	m_ShowItem.ShowWindow(TRUE);

	//LONG IDs=m_TreeWndList.GetItemData(hSel);//ȡ�����������
	//::AfxMessageBox(cText);
}
