// MyPickerColor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyPickerColor.h"
#include "afxdialogex.h"
#include "MyNoteText.h"


//�ȼ���Դ
#define IDC_USERHOTKEY_PICKERCOLOR1                   WM_USER+101
#define IDC_USERHOTKEY_PICKERCOLOR2                   WM_USER+102
#define IDC_USERHOTKEY_PICKERCOLOR3                   WM_USER+103
#define IDC_USERHOTKEY_PICKERCOLOR4                   WM_USER+104
#define IDC_USERHOTKEY_PICKERCOLOR5                   WM_USER+105
#define IDC_USERHOTKEY_PICKERCOLOR6                   WM_USER+106
#define IDC_USERHOTKEY_PICKERCOLOR7                   WM_USER+107
#define IDC_USERHOTKEY_PICKERCOLOR8                   WM_USER+108
#define IDC_USERHOTKEY_PICKERCOLOR9                   WM_USER+109
#define IDC_USERHOTKEY_PICKERCOLOR10                  WM_USER+110

#define IDC_USERHOTKEY_PICKEROFFSETCOLOR              WM_USER+111
#define IDC_USERHOTKEY_CATCHSCREENWND                 WM_USER+120
#define IDC_USERHOTKEY_CATCHMUTIPOINT                 WM_USER+121

//////////////////	ȫ�ֻ������ñ���  ///////////////
extern   CString g_noteText;
extern	 HWND		g_MainFormHwnd;

// CMyPickerColor �Ի���

IMPLEMENT_DYNAMIC(CMyPickerColor, CDialogEx)

CMyPickerColor::CMyPickerColor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyPickerColor::IDD, pParent)
	, m_SetDefineX(0)
	, m_SetDefineY(0)
{
	m_LastColor = 0;
	m_pApp = AfxGetApp();
}

CMyPickerColor::~CMyPickerColor()
{
}

void CMyPickerColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_COLOR1, m_SeeColor1);
	DDX_Control(pDX, IDC_STATIC_COLOR2, m_SeeColor2);
	DDX_Control(pDX, IDC_STATIC_COLOR3, m_SeeColor3);
	DDX_Control(pDX, IDC_STATIC_COLOR4, m_SeeColor4);
	DDX_Control(pDX, IDC_STATIC_COLOR5, m_SeeColor5);
	DDX_Control(pDX, IDC_STATIC_COLOR6, m_SeeColor6);
	DDX_Control(pDX, IDC_STATIC_COLOR7, m_SeeColor7);
	DDX_Control(pDX, IDC_STATIC_COLOR8, m_SeeColor8);
	DDX_Control(pDX, IDC_STATIC_COLOR9, m_SeeColor9);
	DDX_Control(pDX, IDC_STATIC_COLOR10, m_SeeColor10);
	DDX_Control(pDX, IDC_STATIC_X, m_postX);
	DDX_Control(pDX, IDC_STATIC_Y, m_postY);
	DDX_Control(pDX, IDC_STATIC_R, m_rgb_r);
	DDX_Control(pDX, IDC_STATIC_G, m_rgb_g);
	DDX_Control(pDX, IDC_STATIC_B, m_rgb_b);
	DDX_Control(pDX, IDC_STATIC_COLORVALUE, m_colorValue);
	DDX_Control(pDX, IDC_STATIC_OFFSETCOL, m_GetOffsetColor);
	DDX_Text(pDX, IDC_EDIT_SETDEFX, m_SetDefineX);
	DDX_Text(pDX, IDC_EDIT_SETDEFY, m_SetDefineY);
	DDX_Control(pDX, IDC_STATIC_LOGTEXT1, m_SetLogText1);
	DDX_Control(pDX, IDC_LIST_MUTIPOINT, m_MutiPointAndColor);
	DDX_Control(pDX, IDC_STATIC_CATCHPOINTLOG, m_CatchPoint);
}


BEGIN_MESSAGE_MAP(CMyPickerColor, CDialogEx)
	ON_WM_CREATE()
	ON_WM_HOTKEY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ZHEDIE, &CMyPickerColor::OnBnClickedButtonZhedie)
	ON_BN_CLICKED(IDC_BUTTON_CATCHSCREEN, &CMyPickerColor::OnBnClickedButtonCatchscreen)
	ON_STN_DBLCLK(IDC_STATIC_NOTE1, &CMyPickerColor::OnStnDblclickStaticNote1)
	ON_STN_DBLCLK(IDC_STATIC_NOTE2, &CMyPickerColor::OnStnDblclickStaticNote2)
	ON_STN_DBLCLK(IDC_STATIC_NOTE3, &CMyPickerColor::OnStnDblclickStaticNote3)
	ON_STN_DBLCLK(IDC_STATIC_NOTE4, &CMyPickerColor::OnStnDblclickStaticNote4)
	ON_STN_DBLCLK(IDC_STATIC_NOTE5, &CMyPickerColor::OnStnDblclickStaticNote5)
	ON_STN_DBLCLK(IDC_STATIC_NOTE6, &CMyPickerColor::OnStnDblclickStaticNote6)
	ON_STN_DBLCLK(IDC_STATIC_NOTE7, &CMyPickerColor::OnStnDblclickStaticNote7)
	ON_STN_DBLCLK(IDC_STATIC_NOTE8, &CMyPickerColor::OnStnDblclickStaticNote8)
	ON_STN_DBLCLK(IDC_STATIC_NOTE9, &CMyPickerColor::OnStnDblclickStaticNote9)
	ON_STN_DBLCLK(IDC_STATIC_NOTE10, &CMyPickerColor::OnStnDblclickStaticNote10)
	ON_WM_DESTROY()
	ON_WM_PAINT()
//	ON_WM_CLOSE()
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_BUTTON_FINDMUTIPOINT, &CMyPickerColor::OnBnClickedButtonFindmutipoint)
ON_BN_CLICKED(IDC_BUTTON_CLEARALLDATA, &CMyPickerColor::OnBnClickedButtonClearalldata)
ON_BN_CLICKED(IDC_BUTTON_DELETELASTSTEP, &CMyPickerColor::OnBnClickedButtonDeletelaststep)
ON_BN_CLICKED(IDC_CHECK_SETTOP, &CMyPickerColor::OnBnClickedCheckSettop)
ON_EN_CHANGE(IDC_EDIT_SETDEFX, &CMyPickerColor::OnEnChangeEditSetdefx)
ON_EN_UPDATE(IDC_EDIT_SETDEFY, &CMyPickerColor::OnEnUpdateEditSetdefy)
ON_BN_CLICKED(IDC_BTN_CLEARALL, &CMyPickerColor::OnBnClickedBtnClearall)
END_MESSAGE_MAP()


// CMyPickerColor ��Ϣ�������

BOOL CMyPickerColor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/////////////ע���ȼ�///////////////
	RegisterAllHotKey();
	/////////////ע���ȼ�///////////////

	///// ȡɫ����ͼ��
	//m_hIcon1 = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	///// ���طŴ���������Դ
	m_hIcon2 = AfxGetApp()->LoadIcon(IDI_ICON_MOUSE);

	SetIcon(m_hIcon1, TRUE); // Set big icon
	SetIcon(m_hIcon1, FALSE); // Set small icon

	// �����ϴα��������
	LoadSet();

	////////////////////��ȡABץץǰһ�ص�λ��/////////////////////////////
	int xport = -1,yport = -1;
	//CString text = _T("");
	//::GetPrivateProfileString(_T("ABDATA"),_T("ABLEFT"),_T("-1"),text.GetBuffer(10),10,_T(".\\ColorInfo.ini"));
	//text.ReleaseBuffer();
	//xport = ::wcstol(text,NULL,10);

	//::GetPrivateProfileString(_T("ABDATA"),_T("ABTOP"),_T("-1"),text.GetBuffer(10),10,_T(".\\ColorInfo.ini"));
	//text.ReleaseBuffer();
	//yport = ::wcstol(text,NULL,10);
	xport = m_pApp->GetProfileInt(_T("ABDATA"),_T("ABLEFT"),0);
	yport = m_pApp->GetProfileInt(_T("ABDATA"),_T("ABTOP"),0);
	//  �ö���ǰ��ȡɫ����
	if(xport!=-1&&yport!=-1)
		::SetWindowPos(this->m_hWnd,HWND_TOPMOST,xport,yport,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	else
		::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);
	/////////////////////�ö���ťĬ��ѡ��//////////////////////
	((CButton*)GetDlgItem(IDC_CHECK_SETTOP))->SetCheck(BST_CHECKED);

	// ������ʱ��
	SetTimer(1,100,NULL);
	//////////////���ڵ�ԭʼ��С////////////////////////////////
	CRect hRect;
	this->GetWindowRect(&hRect);
	m_Width=hRect.Width();
	m_heigth=hRect.Height();
	/////////����������չ��/////////
	m_Click = false;
	m_MutiClick = false;
	CRect   pRect,tRect;
	this->GetWindowRect(&pRect);
	(this->GetDlgItem(IDC_BUTTON_FINDMUTIPOINT))->GetWindowRect(&tRect);
	(this->GetDlgItem(IDC_BUTTON_FINDMUTIPOINT))->SetWindowTextW(_T("�� �Ҷ��"));
	//SetWindowPos(&wndTopMost, 0, 0,tRect.right-pRect.left+5,tRect.bottom-pRect.top+5,SWP_NOMOVE|SWP_SHOWWINDOW);
	////////////////////////////////////////////////////////////////////
	//this->GetWindowRect(&hRect);
	m_LastWidth=pRect.right-pRect.left/*hRect.Width()*/;
	m_Lastheigth=pRect.bottom-pRect.top/*hRect.Height()*/;
	///////////////////////////////////////////////////
	((CEdit *)GetDlgItem(IDC_EDIT_OFFSETCOL))->SetWindowTextW(_T("(0,0) 000000"));
	m_GetOffsetColor.SetBkColor(0);

	m_IsCatchScreen  = false;

	//this->SetBackgroundColor(0xf5e7dd);

	m_SetLogText1.SetTextColor(RGB(6,121,50));
	m_CatchPoint.SetTextColor(RGB(6,121,50));
	m_FristPoint.x=m_FristPoint.y=m_PointAcount=0;

	//GetDlgItem(IDC_EDIT_SETDEFX)->SetWindowTextW(_T("0"));
	//GetDlgItem(IDC_EDIT_SETDEFY)->SetWindowTextW(_T("0"));
	m_SetDefineX = 0;
	m_SetDefineY = 0;
	/////////////��ʼ��ץ���Ľ���/////////////////////////////////////
	DWORD dwStyle = m_MutiPointAndColor.GetExtendedStyle();
	m_MutiPointAndColor.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//m_MutiPointAndColor.InsertColumn(0, _T("���"));
	//m_MutiPointAndColor.SetColumnWidth(0,42);
	m_MutiPointAndColor.InsertColumn(0, _T("��������ɫ"));
	m_MutiPointAndColor.SetColumnWidth(0,160);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

int CMyPickerColor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	// ע���ȼ���Դ  ȡɫ�Ŀ�ݼ�
	//UINT fsModifiers =0,vkey =0;
	//CString keyStr = _T("");
	//for(int i = 0;i<10;i++)
	//{
	//	keyStr.Format(_T("key%d"),i+1);
	//	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),keyStr,MOD_ALT);
	//	if(i<9)
	//		vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),keyStr,'1'+i);
	//	else
	//		vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),keyStr,'0');
	//	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR1+i,fsModifiers,vkey);
	//}

	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR2,fsModifiers,'2');
	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR3,fsModifiers,'3');
	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR4,fsModifiers,'4');
	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR5,fsModifiers,'5');
	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR6,fsModifiers,'6');
	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR7,fsModifiers,'7');
	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR8,fsModifiers,'8');
	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR9,fsModifiers,'9');
	////RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR10,fsModifiers,'0');
	/////////////////////////////////��ͼ��ݼ�/////////////////////////////////
	//fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("catchscree"),MOD_ALT);
	//vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("catchscree"),'D');
	//RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHSCREENWND,fsModifiers,vkey);
	////////////////////��ȡƫɫ�Ŀ�ݼ�/////////////////////////////////////
	//fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("pickoffset"),MOD_CONTROL);
	//vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("pickoffset"),'I');
	//RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKEROFFSETCOLOR,fsModifiers,vkey);
	///////////////////////��ȡ�����ɫ�ȼ�//////////////////////////////////IDC_USERHOTKEY_CATCHMUTIPOINT
	//fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("catchmutl"),MOD_CONTROL);
	//vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("catchmutl"),'R');
	//RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHMUTIPOINT,fsModifiers,vkey);
	/*RegisterAllHotKey();*/
	return 0;
}

///////  ���غ�ע������ȡɫ������ȼ�
void CMyPickerColor::RegisterAllHotKey()
{
	if(m_hWnd ==NULL)
		return ;
	//return ;
	/// �ͷ�ԭ���������ȼ�
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR1);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR2);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR3);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR4);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR5);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR6);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR7);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR8);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR9);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR10);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHSCREENWND);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKEROFFSETCOLOR);
	UnregisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHMUTIPOINT);
	UINT fsModifiers =0,vkey =0;
	CString str = _T(""),helpStr = _T("");
	CString keyStr = _T("");
	////////////////////////=== �����ȼ� ====////////////////////////////
	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key1"),_T("Ctrl+1"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key1"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key1"),'1');	
	BOOL ret = RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR1,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC_HOT1))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key2"),_T("Ctrl+2"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key2"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key2"),'2');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR2,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC__HOT2))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key3"),_T("Ctrl+3"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key3"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key3"),'3');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR3,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC__HOT3))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key4"),_T("Ctrl+4"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key4"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key4"),'4');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR4,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC__HOT4))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key5"),_T("Ctrl+5"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key5"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key5"),'5');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR5,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC__HOT5))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key6"),_T("Ctrl+6"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key6"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key6"),'6');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR6,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC_HOT6))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key7"),_T("Ctrl+7"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key7"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key7"),'7');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR7,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC__HOT7))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key8"),_T("Ctrl+8"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key8"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key8"),'8');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR8,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC_HOT8))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key9"),_T("Ctrl+9"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key9"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key9"),'9');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR9,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC__HOT9))->SetWindowText(str);

	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("key10"),_T("Ctrl+0"));
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key10"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key10"),'0');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKERCOLOR10,fsModifiers,vkey);
	((CStatic*)GetDlgItem(IDC_STATIC__HOT10))->SetWindowText(str);
	////////////////////////=== �����ȼ� ====////////////////////////////

	////////////////////////======== ���� =========/////////////////
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("catchscree"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("catchscree"),'D');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHSCREENWND,fsModifiers,vkey);
	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("catchscree"),_T("Ctrl+D"));
	GetDlgItem(IDC_BUTTON_CATCHSCREEN)->SetWindowTextW(_T("����ȡɫ(")+str+_T(")"));
	//////////////////��ȡƫɫ�Ŀ�ݼ�/////////////////////////////////////
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("pickoffset"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("pickoffset"),'I');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_PICKEROFFSETCOLOR,fsModifiers,vkey);
	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("pickoffset"),_T("Ctrl+I"));
	((CStatic*)GetDlgItem(IDC_STATIC_11))->SetWindowText(str);
	/////////////////////��ȡ�����ɫ�ȼ�//////////////////////////////////IDC_USERHOTKEY_CATCHMUTIPOINT
	fsModifiers = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("catchmutl"),MOD_CONTROL);
	vkey = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("catchmutl"),'R');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_CATCHMUTIPOINT,fsModifiers,vkey);
	str = m_pApp->GetProfileStringW(_T("HOTKEYSTR"),_T("catchmutl"),_T("Ctrl+R"));
	GetDlgItem(IDC_STATIC_MULTPOINT)->SetWindowText(str);
}

void CMyPickerColor::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nHotKeyId)
	{
	case IDC_USERHOTKEY_PICKERCOLOR1:
		runHotKeyFunction(IDC_STATIC_NOTE1,IDC_EDIT_COLORANDPOINT1,IDC_STATIC_COLOR1);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR2:
		runHotKeyFunction(IDC_STATIC_NOTE2,IDC_EDIT_COLORANDPOINT2,IDC_STATIC_COLOR2);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR3:
		runHotKeyFunction(IDC_STATIC_NOTE3,IDC_EDIT_COLORANDPOINT3,IDC_STATIC_COLOR3);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR4:
		runHotKeyFunction(IDC_STATIC_NOTE4,IDC_EDIT_COLORANDPOINT4,IDC_STATIC_COLOR4);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR5:
		runHotKeyFunction(IDC_STATIC_NOTE5,IDC_EDIT_COLORANDPOINT5,IDC_STATIC_COLOR5);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR6:
		runHotKeyFunction(IDC_STATIC_NOTE6,IDC_EDIT_COLORANDPOINT6,IDC_STATIC_COLOR6);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR7:
		runHotKeyFunction(IDC_STATIC_NOTE7,IDC_EDIT_COLORANDPOINT7,IDC_STATIC_COLOR7);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR8:
		runHotKeyFunction(IDC_STATIC_NOTE8,IDC_EDIT_COLORANDPOINT8,IDC_STATIC_COLOR8);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR9:
		runHotKeyFunction(IDC_STATIC_NOTE9,IDC_EDIT_COLORANDPOINT9,IDC_STATIC_COLOR9);
		break;
	case IDC_USERHOTKEY_PICKERCOLOR10:
		runHotKeyFunction(IDC_STATIC_NOTE10,IDC_EDIT_COLORANDPOINT10,IDC_STATIC_COLOR10);
		break;
	//	///////////////////////////////��ݼ���ͼ///////////////////////
	case IDC_USERHOTKEY_CATCHSCREENWND:
		OnBnClickedButtonCatchscreen();
		break;
	case IDC_USERHOTKEY_PICKEROFFSETCOLOR:
		{
			/////////////////////// ��ݼ����ڻ�ȡƫɫ���ܵĻ�ɫ����ɫ
			//�õ�ǰ��������ɫ,
			CPoint pt;
			GetCursorPos(&pt);
			COLORREF color;
			color=::GetPixel(::GetDC(NULL),pt.x,pt.y);
			m_GetOffsetColor.SetBkColor(color);
			CString colorStr=_T("");
			CString strColor=_T("");
	/*		if(color==0)
				strColor.Format(_T("000000"));
			else if(color<=0XF)
				strColor.Format(_T("00000%x"),color);
			else if(color<=0XFF)
				strColor.Format(_T("0000%x"),color);
			else if(color<=0XFFF)
				strColor.Format(_T("000%x"),color);
			else if(color<=0XFFFF)
				strColor.Format(_T("00%x"),color);
			else if(color<=0XFFFFF)
				strColor.Format(_T("0%x"),color);
			else*/
			strColor.Format(_T("%06X"),color);

			colorStr.Format(_T("(%d,%d) %s"),pt.x,pt.y,strColor);

			colorStr.MakeUpper();
			((CEdit *)GetDlgItem(IDC_EDIT_OFFSETCOL))->SetWindowTextW(colorStr);
			//CString see;
			//see.Format(_T("%d"),(int)color);
			//::WritePrivateProfileString(_T("ColorOff"),_T("color"),see,_T(".\\ColorInfo.ini"));
			m_pApp->WriteProfileInt(_T("ColorOff"),_T("color"),color);
		}
		break;
	case IDC_USERHOTKEY_CATCHMUTIPOINT:
		{
			PromCatchMutiPoint();
		}
		break;
	default:
		break;
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CMyPickerColor::runHotKeyFunction(UINT nNote,UINT nEditID,UINT nColorID)
{
	this->UpdateData();

	//***********���ñ�ע������***********//
	CString noteText;
	((CEdit *)GetDlgItem(nNote))->GetWindowTextW(noteText);
	if(noteText.IsEmpty())
	{
		noteText.Format(_T("��ע1"));
	}	
	((CEdit *)GetDlgItem(nNote))->SetWindowTextW(noteText);

	//************�����ǻ�ȡ����������ɫ�Լ�������ɫ�������������*************//
	 //�õ�ǰ��������,
	CPoint pt;
	GetCursorPos(&pt);
	
	//������ǰR,G,B,������ֵ
	COLORREF color;
	HDC hDC = ::GetDC(NULL);
	color=::GetPixel(hDC,pt.x,pt.y);
	::ReleaseDC(NULL,hDC);

	////////////////////�ж��Ƿ��ȡƫɫ///////////////////////////
	if(((CButton*)GetDlgItem(IDC_CHECK_GETOFFSETCOL))->GetCheck() == BST_CHECKED)
	{
		CString text;
		GetDlgItem(IDC_EDIT_OFFSETCOL)->GetWindowTextW(text);
		int pos = text.Find(_T(")"));
		text = text.Right(text.GetLength() - pos -1);
		text.Trim();
		color = ::abs((long)(color - ::wcstol(text,NULL,16)));
	}

	CString colorStr=_T("");
	CString strColor=_T("");
	//if(color==0)
	//	strColor.Format(_T("000000"));
	//else if(color<=0XF)
	//	strColor.Format(_T("00000%x"),color);
	//else if(color<=0XFF)
	//	strColor.Format(_T("0000%x"),color);
	//else if(color<=0XFFF)
	//	strColor.Format(_T("000%x"),color);
	//else if(color<=0XFFFF)
	//	strColor.Format(_T("00%x"),color);
	//else if(color<=0XFFFFF)
	//	strColor.Format(_T("0%x"),color);
	//else
	strColor.Format(_T("%06X"),color);
	
	colorStr.Format(_T("(%d,%d) %s"),pt.x-m_SetDefineX,pt.y-m_SetDefineY,strColor);

	colorStr.MakeUpper();
	((CEdit *)GetDlgItem(nEditID))->SetWindowTextW(colorStr);

	//***********����Ԥ������ɫ***********//	
	m_BackColor=color;
	CString see;

	switch(nColorID)
	{
	case IDC_STATIC_COLOR1:
		m_SeeColor1.SetBkColor(m_BackColor);		
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see1"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see1"),m_BackColor);
		break;
	case IDC_STATIC_COLOR2:
		m_SeeColor2.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see2"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see2"),m_BackColor);
		break;
	case IDC_STATIC_COLOR3:
		m_SeeColor3.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see3"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see3"),m_BackColor);
		break;
	case IDC_STATIC_COLOR4:
		m_SeeColor4.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see4"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see4"),m_BackColor);
		break;
	case IDC_STATIC_COLOR5:
		m_SeeColor5.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see5"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see5"),m_BackColor);
		break;
	case IDC_STATIC_COLOR6:
		m_SeeColor6.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see6"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see6"),m_BackColor);
		break;
	case IDC_STATIC_COLOR7:
		m_SeeColor7.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see7"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see7"),m_BackColor);
		break;
	case IDC_STATIC_COLOR8:
		m_SeeColor8.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see8"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see8"),m_BackColor);
		break;
	case IDC_STATIC_COLOR9:
		m_SeeColor9.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see9"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see9"),m_BackColor);
		break;
	case IDC_STATIC_COLOR10:
		m_SeeColor10.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see10"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see10"),m_BackColor);
		break;
	default:
		break;
	}
	
}

/////////////////////////////////////////////��ȡ�����൱���ڵ��������ɫֵ///////////////////////////////////////////////
void	CMyPickerColor::RightClickPickColor(UINT key,CPoint spt,CPoint bkPt)
{
	switch(key)
	{
	case 1:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE1,IDC_EDIT_COLORANDPOINT1,IDC_STATIC_COLOR1,spt,bkPt);
		break;
	case 2:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE2,IDC_EDIT_COLORANDPOINT2,IDC_STATIC_COLOR2,spt,bkPt);
		break;
	case 3:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE3,IDC_EDIT_COLORANDPOINT3,IDC_STATIC_COLOR3,spt,bkPt);
		break;
	case 4:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE4,IDC_EDIT_COLORANDPOINT4,IDC_STATIC_COLOR4,spt,bkPt);
		break;
	case 5:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE5,IDC_EDIT_COLORANDPOINT5,IDC_STATIC_COLOR5,spt,bkPt);
		break;
	case 6:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE6,IDC_EDIT_COLORANDPOINT6,IDC_STATIC_COLOR6,spt,bkPt);
		break;
	case 7:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE7,IDC_EDIT_COLORANDPOINT7,IDC_STATIC_COLOR7,spt,bkPt);
		break;
	case 8:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE8,IDC_EDIT_COLORANDPOINT8,IDC_STATIC_COLOR8,spt,bkPt);
		break;
	case 9:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE9,IDC_EDIT_COLORANDPOINT9,IDC_STATIC_COLOR9,spt,bkPt);
		break;
	case 10:
		runIntWndHotKeyFunction(IDC_STATIC_NOTE10,IDC_EDIT_COLORANDPOINT10,IDC_STATIC_COLOR10,spt,bkPt);
		break;
	default:
		break;
	}
}
void CMyPickerColor::runIntWndHotKeyFunction(UINT nNote,UINT nEditID,UINT nColorID,CPoint pt,CPoint bkPt)
{
	//***********���ñ�ע������***********//
	CString noteText;
	((CEdit *)GetDlgItem(nNote))->GetWindowTextW(noteText);
	if(noteText.IsEmpty())
	{
		noteText.Format(_T("��ע1"));
	}	
	((CEdit *)GetDlgItem(nNote))->SetWindowTextW(noteText);

	//************�����ǻ�ȡ����������ɫ�Լ�������ɫ�������������*************//
	 //�õ�ǰ��������,
	//CPoint pt;
	//GetCursorPos(&pt);
	
	
	//������ǰR,G,B,������ֵ
	COLORREF color;
	color=::GetPixel(::GetDC(NULL),pt.x,pt.y);
	CString colorStr=_T("");
	CString strColor=_T("");
	//if(color==0)
	//	strColor.Format(_T("000000"));
	//else if(color<=0XF)
	//	strColor.Format(_T("00000%x"),color);
	//else if(color<=0XFF)
	//	strColor.Format(_T("0000%x"),color);
	//else if(color<=0XFFF)
	//	strColor.Format(_T("000%x"),color);
	//else if(color<=0XFFFF)
	//	strColor.Format(_T("00%x"),color);
	//else if(color<=0XFFFFF)
	//	strColor.Format(_T("0%x"),color);
	//else
	strColor.Format(_T("%06X"),color);
	if(bkPt.x==0&&bkPt.y==0)
		colorStr.Format(_T("[%d,%d] %s"),pt.x,pt.y,strColor);
	else
		colorStr.Format(_T("[%d,%d] %s"),bkPt.x,bkPt.y,strColor);

	colorStr.MakeUpper();
	((CEdit *)GetDlgItem(nEditID))->SetWindowTextW(colorStr);

	//***********����Ԥ������ɫ***********//	
	m_BackColor=color;
	CString see;

	switch(nColorID)
	{
	case IDC_STATIC_COLOR1:
		m_SeeColor1.SetBkColor(m_BackColor);		
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see1"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see1"),m_BackColor);
		break;
	case IDC_STATIC_COLOR2:
		m_SeeColor2.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see2"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see2"),m_BackColor);
		break;
	case IDC_STATIC_COLOR3:
		m_SeeColor3.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see3"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see3"),m_BackColor);
		break;
	case IDC_STATIC_COLOR4:
		m_SeeColor4.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see4"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see4"),m_BackColor);
		break;
	case IDC_STATIC_COLOR5:
		m_SeeColor5.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see5"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see5"),m_BackColor);
		break;
	case IDC_STATIC_COLOR6:
		m_SeeColor6.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see6"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see6"),m_BackColor);
		break;
	case IDC_STATIC_COLOR7:
		m_SeeColor7.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see7"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see7"),m_BackColor);
		break;
	case IDC_STATIC_COLOR8:
		m_SeeColor8.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see8"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see8"),m_BackColor);
		break;
	case IDC_STATIC_COLOR9:
		m_SeeColor9.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see9"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see9"),m_BackColor);
		break;
	case IDC_STATIC_COLOR10:
		m_SeeColor10.SetBkColor(m_BackColor);
		//see.Format(_T("%d"),(int)m_BackColor);
		//::WritePrivateProfileString(_T("ColorSet"),_T("see10"),see,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileInt(_T("ColorSet"),_T("see10"),m_BackColor);
		break;
	default:
		break;
	}
	
}

void CMyPickerColor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!this->IsWindowVisible())
		return ;

	POINT pt;
	::GetCursorPos(&pt);

	//��ȡ��ǰ���λ�õ���ɫֵ�����ڶԻ�������ʾ��Ӧ������
	COLORREF color;
	/*color=::GetPixel(::GetDC(NULL),pt.x,pt.y);*/
	HDC ScreenDc=::GetDC(NULL);
	color=::GetPixel(ScreenDc,pt.x,pt.y);

	///////////////////����ƫɫ�Ļ�ȡ//////////////////////
	bool isGetColorOff = false;
	long helpColorOff=0;
	if(((CButton*)GetDlgItem(IDC_CHECK_GETOFFSETCOL))->GetCheck() == BST_CHECKED)
	{
		isGetColorOff = true;
		CString text;
		GetDlgItem(IDC_EDIT_OFFSETCOL)->GetWindowTextW(text);
		int pos = text.Find(_T(")"));
		text = text.Right(text.GetLength() - pos -1);
		text.Trim();
		//color = ::abs((long)(color - ::wcstol(text,NULL,16)));
		helpColorOff = ::wcstol(text,NULL,16);
	}

	::ReleaseDC(NULL,ScreenDc);

	//////////////////////////////// �ж����δ��//////////////////
	if( (pt.x==m_LastPoint.x&&pt.y==m_LastPoint.y) && m_LastColor==color )
		return ;
	else
	{
		m_LastPoint.x=pt.x;
		m_LastPoint.y=pt.y;
	}
	/////////////////////////////////////////////////////////////
	m_LastColor=color;
	BYTE rValue,gValue,bValue;
	if(isGetColorOff)
	{
		rValue=abs((int)GetRValue(color)-(int)GetRValue(helpColorOff));
		gValue=abs((int)GetGValue(color)-(int)GetGValue(helpColorOff));;
		bValue=abs((int)GetBValue(color)-(int)GetBValue(helpColorOff));
	}
	else
	{
		rValue=GetRValue(color);
		gValue=GetGValue(color);
		bValue=GetBValue(color);
	}

	this->UpdateData();

	CString strX;
	CString strY;

	CString strColor;
	CString strR;
	CString strG;
	CString strB;

	////// ���ý��������������
	strX.Format(_T("X:%d"),pt.x-m_SetDefineX);
	strY.Format(_T("Y:%d"),pt.y-m_SetDefineY);
	m_postX.SetWindowTextW(strX);
	m_postY.SetWindowTextW(strY);

	//if(color==0)
	//	strColor.Format(_T("000000"));
	//else if(color<=0XF)
	//	strColor.Format(_T("00000%x"),color);
	//else if(color<=0XFF)
	//	strColor.Format(_T("0000%x"),color);
	//else if(color<=0XFFF)
	//	strColor.Format(_T("000%x"),color);
	//else if(color<=0XFFFF)
	//	strColor.Format(_T("00%x"),color);
	//else if(color<=0XFFFFF)
	//	strColor.Format(_T("0%x"),color);
	//else
	strColor.Format(_T("%06X"),color);
	
	strColor.MakeUpper();
	m_colorValue.SetWindowTextW(strColor);

	strR.Format(_T("R:%d"),rValue);
	strG.Format(_T("G:%d"),gValue);
	strB.Format(_T("B:%d"),bValue);
	////// ���ý�����RGB��ֵ������
	m_rgb_r.SetWindowTextW(strR);
	m_rgb_g.SetWindowTextW(strG);
	m_rgb_b.SetWindowTextW(strB);
	//////////////////////////////////////////////////////////////////////////////

	HDC hScrDC, hMemDC; 
	static int  offset = 8;
	CRect lpRect;
	lpRect.left=pt.x-offset;
	lpRect.top=pt.y-offset;
	lpRect.right=pt.x+offset;
	lpRect.bottom=pt.y+offset;

	/*HDC hScrDC, hMemDC; */     
	// ��Ļ���ڴ��豸������
	HBITMAP hBitmap,hOldBitmap;   
	// λͼ���
	int       nX, nY, nX2, nY2;      
	// ѡ����������
	int       nWidth, nHeight;      
	// λͼ��Ⱥ͸߶�
	int       xScrn, yScrn;         

	// ��Ļ�ֱ���
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(&lpRect))
		return ;

	////Ϊ��Ļ�����豸������
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect.left;
	nY = lpRect.top;
	nX2 = lpRect.right;
	nY2 = lpRect.bottom;

	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���
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
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	//BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, CAPTUREBLT|SRCCOPY);
	//CDC* pDc= GetDC();
	CClientDC   pDc(this);
	HDC helpDC=NULL;
	helpDC=pDc.m_hDC;

	int mX=0,mY=0;	
	CRect recPic;
	this->GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&recPic);

	POINT point;
	point.x = recPic.left;
	point.y = recPic.top;
	::ScreenToClient(this->m_hWnd,&point);
	
	//CRect mRet;
	//m_FangDajingGroup.GetWindowRect(mRet);

	//mX=recPic.left-mRet.left+2;       // left right is X
	//mY=recPic.top-mRet.top+1;         // top  buttom is Y

	StretchBlt(helpDC,point.x,point.y, recPic.Width(), recPic.Height(), hScrDC, nX, nY, nWidth, nHeight, SRCCOPY);
	
	////��� 
	DeleteDC(hMemDC);
	DeleteDC(hScrDC);

	DeleteObject(hBitmap);
	
	// ���������Դ
	pDc.DrawIcon(recPic.Width()/2,recPic.Height()/2+13,m_hIcon2);
	CDialogEx::OnTimer(nIDEvent);
}

//��������ϵ�����
void CMyPickerColor::SaveAllSetText()
{
	this->UpdateData();
	CString note;
	CString portandcolor;

	//1
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE1))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note1"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT1))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color1"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note1"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color1"),portandcolor);

	//2
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE2))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note2"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT2))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color2"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note2"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color2"),portandcolor);
	//3
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE3))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note3"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT3))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color3"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note3"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color3"),portandcolor);
	//4
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE4))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note4"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT4))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color4"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note4"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color4"),portandcolor);
	//5
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE5))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note5"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT5))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color5"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note5"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color5"),portandcolor);
	//6
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE6))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note6"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT6))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color6"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note6"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color6"),portandcolor);
	//7
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE7))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note7"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT7))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color7"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note7"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color7"),portandcolor);
	//8
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE8))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note8"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT8))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color8"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note8"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color8"),portandcolor);
	//9
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE9))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note9"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT9))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color9"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note9"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color9"),portandcolor);
	//10
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE10))->GetWindowTextW(note);
	//::WritePrivateProfileString(_T("ColorSet"),_T("note10"),note,_T(".\\ColorInfo.ini"));
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT10))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorSet"),_T("color10"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("note10"),note);
	m_pApp->WriteProfileStringW(_T("ColorSet"),_T("color10"),portandcolor);
	// ƫɫ�ı���
	((CEdit*)GetDlgItem(IDC_EDIT_OFFSETCOL))->GetWindowTextW(portandcolor);
	//::WritePrivateProfileString(_T("ColorOff"),_T("offset"),portandcolor,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileStringW(_T("ColorOff"),_T("offset"),portandcolor);
}

// �����ϴν��汣�������
void CMyPickerColor::LoadSet()
{
	CString note;
	CString portandcolor;
	//CString seecolor;
	//int iSeecolor = 0;
	//1
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note1"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color1"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see1"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE1))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT1))->SetWindowTextW(portandcolor);
	m_SeeColor1.SetBkColor(m_BackColor);

	//2
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note2"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color2"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see2"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE2))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT2))->SetWindowTextW(portandcolor);
	m_SeeColor2.SetBkColor(m_BackColor);

	//3
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note3"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color3"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see3"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE3))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT3))->SetWindowTextW(portandcolor);
	m_SeeColor3.SetBkColor(m_BackColor);

	//4
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note4"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color4"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see4"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE4))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT4))->SetWindowTextW(portandcolor);
	m_SeeColor4.SetBkColor(m_BackColor);

	//5
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note5"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color5"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see5"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE5))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT5))->SetWindowTextW(portandcolor);
	m_SeeColor5.SetBkColor(m_BackColor);

	//6
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note6"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color6"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see6"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE6))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT6))->SetWindowTextW(portandcolor);
	m_SeeColor6.SetBkColor(m_BackColor);

	//7
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note7"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color7"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see7"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE7))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT7))->SetWindowTextW(portandcolor);
	m_SeeColor7.SetBkColor(m_BackColor);

	//8
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note8"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color8"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see8"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE8))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT8))->SetWindowTextW(portandcolor);
	m_SeeColor8.SetBkColor(m_BackColor);

	//9
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note9"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color9"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see9"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE9))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT9))->SetWindowTextW(portandcolor);
	m_SeeColor9.SetBkColor(m_BackColor);

	//10
	note = m_pApp->GetProfileStringW(_T("ColorSet"),_T("note10"),_T("˫���޸�"));
	portandcolor = m_pApp->GetProfileStringW(_T("ColorSet"),_T("color10"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorSet"),_T("see10"),0);
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE10))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT10))->SetWindowTextW(portandcolor);
	m_SeeColor10.SetBkColor(m_BackColor);


	////////// ƫɫ�Ĵ��� ///////////////////
	// ƫɫ�ı���
	portandcolor = m_pApp->GetProfileStringW(_T("ColorOff"),_T("offset"),_T(""));
	m_BackColor = m_pApp->GetProfileIntW(_T("ColorOff"),_T("color"),0);
	((CEdit*)GetDlgItem(IDC_EDIT_OFFSETCOL))->SetWindowTextW(portandcolor);
	m_GetOffsetColor.SetBkColor(m_BackColor);
}

// ���ý�����������
void CMyPickerColor::Reset()
{
	this->UpdateData(TRUE);

	CString note = _T("˫���޸�");
	CString portandcolor = _T("");
	CString seecolor = _T("0");
	m_BackColor = 0;               // ������ɫȫ������Ϊ0 ��ɫ
	//1
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE1))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT1))->SetWindowTextW(portandcolor);	
	m_SeeColor1.SetBkColor(m_BackColor);

	//2
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE2))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT2))->SetWindowTextW(portandcolor);	
	m_SeeColor2.SetBkColor(m_BackColor);

	//3
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE3))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT3))->SetWindowTextW(portandcolor);	
	m_SeeColor3.SetBkColor(m_BackColor);

	//4
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE4))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT4))->SetWindowTextW(portandcolor);	
	m_SeeColor4.SetBkColor(m_BackColor);

	//5
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE5))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT5))->SetWindowTextW(portandcolor);	
	m_SeeColor5.SetBkColor(m_BackColor);

	//6
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE6))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT6))->SetWindowTextW(portandcolor);	
	m_SeeColor6.SetBkColor(m_BackColor);

	//7
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE7))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT7))->SetWindowTextW(portandcolor);	
	m_SeeColor7.SetBkColor(m_BackColor);

	//8
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE8))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT8))->SetWindowTextW(portandcolor);	
	m_SeeColor8.SetBkColor(m_BackColor);

	//9
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE9))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT9))->SetWindowTextW(portandcolor);	
	m_SeeColor9.SetBkColor(m_BackColor);

	//10
	((CStatic*)GetDlgItem(IDC_STATIC_NOTE10))->SetWindowTextW(note);
	((CEdit*)GetDlgItem(IDC_EDIT_COLORANDPOINT10))->SetWindowTextW(portandcolor);	
	m_SeeColor10.SetBkColor(m_BackColor);

	CString keyStr = _T("");
	for(int i=1;i<=10;i++)
	{
		keyStr.Format(_T("see%d"),i);
		//::WritePrivateProfileString(_T("ColorSet"),keyStr,0,_T(".\\ColorInfo.ini"));
		m_pApp->WriteProfileStringW(_T("ColorSet"),keyStr,0);
	}

	this->UpdateData(FALSE);
}

void CMyPickerColor::OnBnClickedButtonZhedie()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_Click)
	{
		m_Click=false;
		(this->GetDlgItem(IDC_BUTTON_ZHEDIE))->SetWindowTextW(_T("�۵� <<"));
		if(m_MutiClick)
		{
			if(((CButton*)GetDlgItem(IDC_CHECK_SETTOP))->GetCheck()==BST_CHECKED)
				SetWindowPos(&wndTopMost, 0, 0,m_Width,m_heigth,SWP_NOMOVE|SWP_SHOWWINDOW);
			else
				SetWindowPos(&wndNoTopMost, 0, 0,m_Width,m_heigth,SWP_NOMOVE|SWP_SHOWWINDOW);
		}
		else
		{
			if(((CButton*)GetDlgItem(IDC_CHECK_SETTOP))->GetCheck()==BST_CHECKED)
				SetWindowPos(&wndTopMost, 0, 0,m_LastWidth,m_Lastheigth,SWP_NOMOVE|SWP_SHOWWINDOW);
			else
				SetWindowPos(&wndNoTopMost, 0, 0,m_LastWidth,m_Lastheigth,SWP_NOMOVE|SWP_SHOWWINDOW);
		}
	}
	else
	{
		m_Click=true;
		CRect   pRect,tRect;
		this->GetWindowRect(&pRect);
		(this->GetDlgItem(IDC_BUTTON_ZHEDIE))->GetWindowRect(&tRect);
		(this->GetDlgItem(IDC_BUTTON_ZHEDIE))->SetWindowTextW(_T("չ�� >>"));
		if(((CButton*)GetDlgItem(IDC_CHECK_SETTOP))->GetCheck()==BST_CHECKED)
			SetWindowPos(&wndTopMost, 0, 0,pRect.right-pRect.left,tRect.bottom-pRect.top+15,SWP_NOMOVE|SWP_SHOWWINDOW);
		else
			SetWindowPos(&wndNoTopMost, 0, 0,pRect.right-pRect.left,tRect.bottom-pRect.top+15,SWP_NOMOVE|SWP_SHOWWINDOW);
	}
}


void CMyPickerColor::OnBnClickedButtonCatchscreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//::AfxMessageBox(L"��ʵ��");
	/*CCatchScreenDlg screenDlg;
	screenDlg.DoModal();*/
	if(!m_IsCatchScreen)
	{
		m_IsCatchScreen=true;
		//this->ShowWindow(SW_HIDE);
		::Sleep(300);	
		CCatchScreenDlg dlg;
		if(IDOK==dlg.DoModal())
		{
			
		}
		//this->ShowWindow(SW_SHOWNORMAL);
		m_IsCatchScreen=false;
		
	}
	
	//m_CatchScreenDlg.Create(IDD_DIALOG_CATCHSCREEN);
	//m_CatchScreenDlg.ShowWindow(TRUE);
	//m_CatchScreenDlg.DoModal();
}


void CMyPickerColor::OnStnDblclickStaticNote1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE1)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE1)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE2)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE2)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE3)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE3)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE4)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE4)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE5)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE5)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE6)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE6)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE7)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE7)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE8)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE8)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE9)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE9)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnStnDblclickStaticNote10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_STATIC_NOTE10)->GetWindowTextW(g_noteText);
	CMyNoteText noteDLG;
	noteDLG.DoModal();
	this->GetDlgItem(IDC_STATIC_NOTE10)->SetWindowTextW(g_noteText);
}


void CMyPickerColor::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	RECT rect;
	//::GetWindowRect(this->m_hWnd,&rect);
	this->GetWindowRect(&rect);
	//CString text = _T("");
	//text.Format(_T("%d"),rect.left);
	//::WritePrivateProfileString(_T("ABDATA"),_T("ABLEFT"),text,_T(".\\ColorInfo.ini"));
	//text.Format(_T("%d"),rect.top);
	//::WritePrivateProfileString(_T("ABDATA"),_T("ABTOP"),text,_T(".\\ColorInfo.ini"));
	m_pApp->WriteProfileInt(_T("ABDATA"),_T("ABLEFT"),rect.left);
	m_pApp->WriteProfileInt(_T("ABDATA"),_T("ABTOP"),rect.top);
	SaveAllSetText();
	// TODO: �ڴ˴������Ϣ����������
}


BOOL CMyPickerColor::PreTranslateMessage(MSG* pMsg)
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
	else if(pMsg->wParam==VK_RETURN)
	{
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyPickerColor::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	//  �ö���ǰ��ȡɫ����
	//::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
}


//void CMyPickerColor::OnClose()
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	::SendMessage(g_MainFormHwnd,IDC_USER_CLOSEPICKERWND,0,0);
//	CDialogEx::OnClose();
//}


void CMyPickerColor::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//RECT rect;
	//::GetWindowRect(this->m_hWnd,&rect);
	//CString text = _T("");
	//text.Format(_T("%d"),rect.left);
	//::WritePrivateProfileString(_T("ABDATA"),_T("ABLEFT"),text,_T(".\\ColorInfo.ini"));
	//text.Format(_T("%d"),rect.top);
	//::WritePrivateProfileString(_T("ABDATA"),_T("ABTOP"),text,_T(".\\ColorInfo.ini"));

	CDialogEx::OnClose();
}


void CMyPickerColor::OnBnClickedButtonFindmutipoint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_MutiClick)   ///////Ĭ�ϵ��۵�״̬
	{
		m_MutiClick=true;
		/*CRect   pRect,tRect;
		this->GetWindowRect(&pRect);
		(this->GetDlgItem(IDC_BUTTON_FINDMUTIPOINT))->GetWindowRect(&tRect);*/
		(this->GetDlgItem(IDC_BUTTON_FINDMUTIPOINT))->SetWindowTextW(_T("�� �Ҷ��"));
		if(((CButton*)GetDlgItem(IDC_CHECK_SETTOP))->GetCheck()==BST_CHECKED)
			SetWindowPos(&wndTopMost, 0, 0,m_Width,m_heigth,SWP_NOMOVE|SWP_SHOWWINDOW);
		else
			SetWindowPos(&wndNoTopMost, 0, 0,m_Width,m_heigth,SWP_NOMOVE|SWP_SHOWWINDOW);

	}
	else
	{
		m_MutiClick=false;
		/*CRect   pRect,tRect;
		this->GetWindowRect(&pRect);
		(this->GetDlgItem(IDC_BUTTON_FINDMUTIPOINT))->GetWindowRect(&tRect);*/

		(this->GetDlgItem(IDC_BUTTON_FINDMUTIPOINT))->SetWindowTextW(_T("�� �Ҷ��"));
		if(((CButton*)GetDlgItem(IDC_CHECK_SETTOP))->GetCheck()==BST_CHECKED)
			SetWindowPos(&wndTopMost, 0, 0,m_LastWidth,m_Lastheigth,SWP_NOMOVE|SWP_SHOWWINDOW);
		else
			SetWindowPos(&wndNoTopMost, 0, 0,m_LastWidth,m_Lastheigth,SWP_NOMOVE|SWP_SHOWWINDOW);
		//SetWindowPos(&wndTopMost, 0, 0,tRect.right-pRect.left+5,tRect.bottom-pRect.top+5,SWP_NOMOVE|SWP_SHOWWINDOW);
	}
}

///////////////////// ץ�����ȼ�ʵ�ַ���/////////////////
void CMyPickerColor::PromCatchMutiPoint()
{
	CString strColor=_T("");
	//************�����ǻ�ȡ����������ɫ�Լ�������ɫ�������������*************//
	 //�õ�ǰ��������,
	POINT pt;
	GetCursorPos(&pt);	
	//������ǰR,G,B,������ֵ
	COLORREF color;
	HDC hDC = ::GetDC(NULL);
	color=::GetPixel(hDC,pt.x,pt.y);
	::ReleaseDC(NULL,hDC);
	//if(color==0)
	//	strColor.Format(_T("000000"));
	//else if(color<=0XF)
	//	strColor.Format(_T("00000%x"),color);
	//else if(color<=0XFF)
	//	strColor.Format(_T("0000%x"),color);
	//else if(color<=0XFFF)
	//	strColor.Format(_T("000%x"),color);
	//else if(color<=0XFFFF)
	//	strColor.Format(_T("00%x"),color);
	//else if(color<=0XFFFFF)
	//	strColor.Format(_T("0%x"),color);
	//else
	strColor.Format(_T("%06X"),color);

	m_PointAcount ++;
	m_MutiPointAndColor.InsertItem(m_PointAcount, _T(""));
	/////////////////////////�ж��ǲ��ǵ�һ����////////////
	if(m_FristPoint.x==m_FristPoint.y&&m_FristPoint.x ==0)
	{
		m_FristPoint = pt;
		CString pColor=_T("");
		pColor.Format(_T("%d: %d,%d %s"),m_PointAcount-1,pt.x,pt.y,strColor);
		pColor.MakeUpper();
		//m_MutiPointAndColor.SetItem(m_PointAcount-1,0,pColor);
		m_MutiPointAndColor.SetItem(m_PointAcount-1,0,LVIF_TEXT,pColor,0,0L,0L,0L);
		pColor.Format(_T("%x"),color);
		m_FristColor.Append(pColor);

		this->GetDlgItem(IDC_EDIT_MUTIPOINTANDCOLOR)->SetWindowText(m_FristColor);
	}
	else
	{
		CString pColor=_T("");
		pColor.Format(_T("%d: %d,%d %s"),m_PointAcount-1,pt.x,pt.y,strColor);
		pColor.MakeUpper();
		//m_MutiPointAndColor.SetItem(m_PointAcount-1,0,pColor);
		m_MutiPointAndColor.SetItem(m_PointAcount-1,0,LVIF_TEXT,pColor,0,0L,0L,0L);
		if(m_PointAcount==2)
			pColor.Format(_T("%d|%d|%s"),pt.x-m_FristPoint.x,pt.y-m_FristPoint.y,strColor);
		else
			pColor.Format(_T(",%d|%d|%s"),pt.x-m_FristPoint.x,pt.y-m_FristPoint.y,strColor);
		m_MutilColor.Append(pColor);
		//m_MutilColor = m_MutilColor.Left(m_MutilColor.GetLength()-1);
		pColor.Format(_T("%s,\"%s\""),m_FristColor,m_MutilColor);
		this->GetDlgItem(IDC_EDIT_MUTIPOINTANDCOLOR)->SetWindowText(pColor);
	}
}


void CMyPickerColor::OnBnClickedButtonClearalldata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_MutilColor = _T("");
	m_FristColor = _T("");
	this->GetDlgItem(IDC_EDIT_MUTIPOINTANDCOLOR)->SetWindowText(m_MutilColor);
	m_MutiPointAndColor.DeleteAllItems();
	m_FristPoint.x = m_FristPoint.y = 0;
	m_PointAcount=0;
}


void CMyPickerColor::OnBnClickedButtonDeletelaststep()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_MutiPointAndColor.DeleteItem(m_PointAcount-1);
	m_PointAcount--;

	if(m_MutilColor.IsEmpty())
	{
		m_FristColor = _T("");
		m_PointAcount = 0;
		m_FristPoint.x = m_FristPoint.y = 0;
		this->GetDlgItem(IDC_EDIT_MUTIPOINTANDCOLOR)->SetWindowText(m_FristColor);
		return ;
	}
	else
	{
		CString helpStr=_T(""),pStr=_T("");
		int pos =-1;
		while(true)
		{
			pos = m_MutilColor.Find(_T(","));
			if(pos==-1)
			{
				break;
			}
			pStr = m_MutilColor.Left(pos+1);
			helpStr.Append(pStr);
			m_MutilColor = m_MutilColor.Right(m_MutilColor.GetLength()-pos-1);
		}
		if(helpStr.IsEmpty())
		{
			m_MutilColor = _T("");
			this->GetDlgItem(IDC_EDIT_MUTIPOINTANDCOLOR)->SetWindowText(m_FristColor);
		}
		else
		{
			m_MutilColor = helpStr.Left(helpStr.GetLength()-1);
			helpStr.Format(_T("%s,\"%s\""),m_FristColor,m_MutilColor);
			this->GetDlgItem(IDC_EDIT_MUTIPOINTANDCOLOR)->SetWindowText(helpStr);
		}
	}

	return;
}


void CMyPickerColor::OnBnClickedCheckSettop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(((CButton*)GetDlgItem(IDC_CHECK_SETTOP))->GetCheck()==BST_CHECKED)
	{
		::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
	}
	else
	{
		::SetWindowPos(this->m_hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
	}
}


void CMyPickerColor::OnEnChangeEditSetdefx()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("");
	this->GetDlgItem(IDC_EDIT_SETDEFX)->GetWindowTextW(str);
	if(str.GetLength()==0)
	{
		this->GetDlgItem(IDC_EDIT_SETDEFX)->SetWindowTextW(_T("0"));
	}
}


void CMyPickerColor::OnEnUpdateEditSetdefy()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str=_T("");
	this->GetDlgItem(IDC_EDIT_SETDEFY)->GetWindowTextW(str);
	if(str.GetLength()==0)
	{
		this->GetDlgItem(IDC_EDIT_SETDEFY)->SetWindowTextW(_T("0"));
	}
}


void CMyPickerColor::OnBnClickedBtnClearall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Reset();
}
