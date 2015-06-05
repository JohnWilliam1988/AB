// MySettingDlgClass.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MySettingDlgClass.h"
#include "afxdialogex.h"

extern  HWND				g_MainFormHwnd;
extern  CMyPickerColor		g_PickColorDlg;
// CMySettingDlgClass 对话框

IMPLEMENT_DYNAMIC(CMySettingDlgClass, CDialogEx)

CMySettingDlgClass::CMySettingDlgClass(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMySettingDlgClass::IDD, pParent)
{
	m_pApp = AfxGetApp();
}

CMySettingDlgClass::~CMySettingDlgClass()
{
}

void CMySettingDlgClass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ID, m_ComboCtrl);
	DDX_Control(pDX, IDC_HOTKEY_PICK, m_PicHotKeyCtrl);
	DDX_Control(pDX, IDC_HOTKEY_OFFSET, m_OffsetColorCtrl);
	DDX_Control(pDX, IDC_HOTKEY_MULTPOINT, m_MultPointCtrl);
	DDX_Control(pDX, IDC_HOTKEY_CATCHSCREE, m_CatchScreenCtrl);
	DDX_Control(pDX, IDC_HOTKEY_MOUSEWND, m_MouseWndCtrl);
}


BEGIN_MESSAGE_MAP(CMySettingDlgClass, CDialogEx)
//	ON_CBN_EDITCHANGE(IDC_COMBO_ID, &CMySettingDlgClass::OnCbnEditchangeComboId)
	ON_CBN_SELCHANGE(IDC_COMBO_ID, &CMySettingDlgClass::OnCbnSelchangeComboId)
	ON_CBN_DROPDOWN(IDC_COMBO_ID, &CMySettingDlgClass::OnCbnDropdownComboId)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMySettingDlgClass::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, &CMySettingDlgClass::OnBnClickedButtonCancle)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMySettingDlgClass::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CMySettingDlgClass 消息处理程序


BOOL CMySettingDlgClass::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ComboCtrl.AddString(_T("第一热键"));
	m_ComboCtrl.AddString(_T("第二热键"));
	m_ComboCtrl.AddString(_T("第三热键"));
	m_ComboCtrl.AddString(_T("第四热键"));
	m_ComboCtrl.AddString(_T("第五热键"));
	m_ComboCtrl.AddString(_T("第六热键"));
	m_ComboCtrl.AddString(_T("第七热键"));
	m_ComboCtrl.AddString(_T("第八热键"));
	m_ComboCtrl.AddString(_T("第九热键"));
	m_ComboCtrl.AddString(_T("第十热键"));
	m_ComboCtrl.SetCurSel(0);

	int keyCode =0,keyMode =0;
	keyCode = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("key1"),0);
	keyMode = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("key1"),MOD_CONTROL);
	keyMode = GetHotKeyModfile(keyMode);
	m_PicHotKeyCtrl.SetHotKey(keyCode,keyMode);   // 热键抓点色

	keyMode = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("pickoffset"),MOD_CONTROL);
	keyCode = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("pickoffset"),'I');
	keyMode = GetHotKeyModfile(keyMode);
	m_OffsetColorCtrl.SetHotKey(keyCode,keyMode);  // 偏色热键

	keyMode = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("catchmutl"),MOD_CONTROL);
	keyCode = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("catchmutl"),'R');
	keyMode = GetHotKeyModfile(keyMode);
	m_MultPointCtrl.SetHotKey(keyCode,keyMode);   // 多点取色热键

	keyMode = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),_T("catchscree"),MOD_CONTROL);
	keyCode = m_pApp->GetProfileIntW(_T("HOTKEY"),_T("catchscree"),'D');
	keyMode = GetHotKeyModfile(keyMode);
	m_CatchScreenCtrl.SetHotKey(keyCode,keyMode);   // 截屏取色热键

	keyMode = m_pApp->GetProfileInt(_T("HOTKEYMODE"),_T("mousewnd"),0);
	keyCode = m_pApp->GetProfileInt(_T("HOTKEY"),_T("mousewnd"),VK_F9);
	keyMode = GetHotKeyModfile(keyMode);
	m_MouseWndCtrl.SetHotKey(keyCode,keyMode);    // 鼠标窗口热键

	RECT rect;
	g_PickColorDlg.GetWindowRect(&rect);
	SetDlgItemInt(IDC_EDIT_XPOINT,rect.left);
	SetDlgItemInt(IDC_EDIT_YPOINT,rect.top);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

///////  // 转换为Regsiter命令识别的键值
WORD CMySettingDlgClass::GetRegisterModfile(WORD inWord)
{
	switch(inWord)
	{
	case HOTKEYF_ALT:
		return MOD_ALT;
		break;
	case HOTKEYF_CONTROL:
		return MOD_CONTROL;
	case HOTKEYF_SHIFT:
		return MOD_SHIFT;
	default:
		break;
	}
	return inWord;
}
///////   // 转换为HotKey控件识别的键值
WORD CMySettingDlgClass::GetHotKeyModfile(WORD inWord)
{
	switch(inWord)
	{
	case MOD_ALT:
		return HOTKEYF_ALT;
		break;
	case MOD_CONTROL:
		return HOTKEYF_CONTROL;
	case MOD_SHIFT:
		return HOTKEYF_SHIFT;
	default:
		break;
	}
	return inWord;
}


void CMySettingDlgClass::OnCbnSelchangeComboId()
{
	// TODO: 在此添加控件通知处理程序代码
	WORD keyCode =0, keyMode =0;
	int curSel = m_ComboCtrl.GetCurSel();

	CString keyStr = _T("");
	keyStr.Format(_T("key%d"),curSel+1);	
	keyCode = m_pApp->GetProfileIntW(_T("HOTKEY"),keyStr,0);
	keyMode = m_pApp->GetProfileIntW(_T("HOTKEYMODE"),keyStr,0);
	keyMode = GetHotKeyModfile(keyMode);
	m_PicHotKeyCtrl.SetHotKey(keyCode,keyMode);
	m_PicHotKeyCtrl.SetFocus();
}


void CMySettingDlgClass::OnCbnDropdownComboId()
{
	// TODO: 在此添加控件通知处理程序代码
	WORD keyCode =0, keyMode =0;
	int curSel = m_ComboCtrl.GetCurSel();
	m_PicHotKeyCtrl.GetHotKey(keyCode,keyMode);
	CString str = _T("");
	str.Format(_T("key%d"),curSel+1);
	keyMode = GetRegisterModfile(keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEY"),str,keyCode);
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),str,keyMode);
	CString hotStr = m_PicHotKeyCtrl.GetHotKeyName();
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),str,hotStr);	
}


void CMySettingDlgClass::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	WORD keyCode =0, keyMode =0;
	CString hotStr = _T("");
	///////  当前下拉框选择的哪个热键//
	int curSel = m_ComboCtrl.GetCurSel();
	m_PicHotKeyCtrl.GetHotKey(keyCode,keyMode);
	CString str = _T("");
	str.Format(_T("key%d"),curSel+1);
	keyMode = GetRegisterModfile(keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEY"),str,keyCode);
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),str,keyMode);
	hotStr = m_PicHotKeyCtrl.GetHotKeyName();
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),str,hotStr);

	/// 获取偏色的热键信息
	m_OffsetColorCtrl.GetHotKey(keyCode,keyMode);
	hotStr = m_OffsetColorCtrl.GetHotKeyName();
	keyMode = GetRegisterModfile(keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("pickoffset"),keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("pickoffset"),keyCode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("pickoffset"),hotStr);

	/// 获取抓多点的热键信息
	keyCode =0, keyMode =0;
	m_MultPointCtrl.GetHotKey(keyCode,keyMode);
	hotStr = m_MultPointCtrl.GetHotKeyName();
	keyMode = GetRegisterModfile(keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("catchmutl"),keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("catchmutl"),keyCode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("catchmutl"),hotStr);

	/// 获取屏幕取色的热键信息
	keyCode =0, keyMode =0;
	m_CatchScreenCtrl.GetHotKey(keyCode,keyMode);
	hotStr = m_CatchScreenCtrl.GetHotKeyName();
	keyMode = GetRegisterModfile(keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("catchscree"),keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("catchscree"),keyCode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("catchscree"),hotStr);

	/// 获取鼠标窗口的热键信息
	keyCode =0, keyMode =0;
	m_MouseWndCtrl.GetHotKey(keyCode,keyMode);
	hotStr = m_MouseWndCtrl.GetHotKeyName();
	keyMode = GetRegisterModfile(keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("mousewnd"),keyMode);
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("mousewnd"),keyCode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("mousewnd"),hotStr);

	g_PickColorDlg.RegisterAllHotKey();
	((CMyInterfacePropSheet*)FromHandle(g_MainFormHwnd))->m_CatchWndInfo.RegisterHotkey();
	this->OnOK();
}


void CMySettingDlgClass::OnBnClickedButtonCancle()
{
	// TODO: 在此添加控件通知处理程序代码
	this->OnCancel();
}


void CMySettingDlgClass::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	WORD keyCode =0, keyMode = MOD_CONTROL;
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key1"),'1');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key1"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key1"),_T("Ctrl + 1"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key2"),'2');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key2"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key2"),_T("Ctrl + 2"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key3"),'3');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key3"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key3"),_T("Ctrl + 3"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key4"),'4');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key4"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key4"),_T("Ctrl + 4"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key5"),'5');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key5"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key5"),_T("Ctrl + 5"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key6"),'6');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key6"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key6"),_T("Ctrl + 6"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key7"),'7');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key7"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key7"),_T("Ctrl + 7"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key8"),'8');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key8"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key8"),_T("Ctrl + 8"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key9"),'9');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key9"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key9"),_T("Ctrl + 9"));

	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("key10"),'0');
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("key10"),keyMode);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("key10"),_T("Ctrl + 0"));

	/// 获取偏色的热键信息
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("pickoffset"),MOD_CONTROL);
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("pickoffset"),'I');
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("pickoffset"),_T("Ctrl + I"));

	/// 获取抓多点的热键信息
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("catchmutl"),MOD_CONTROL);
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("catchmutl"),'R');
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("catchmutl"),_T("Ctrl + R"));

	/// 获取屏幕取色的热键信息
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("catchscree"),MOD_CONTROL);
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("catchscree"),'D');
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("catchscree"),_T("Ctrl + D"));

	/// 获取鼠标窗口的热键信息
	m_pApp->WriteProfileInt(_T("HOTKEYMODE"),_T("mousewnd"),0);
	m_pApp->WriteProfileInt(_T("HOTKEY"),_T("mousewnd"),VK_F9);
	m_pApp->WriteProfileStringW(_T("HOTKEYSTR"),_T("mousewnd"),_T("F9"));

	SetDlgItemInt(IDC_EDIT_XPOINT,0);
	SetDlgItemInt(IDC_EDIT_YPOINT,0);
	g_PickColorDlg.SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);

	g_PickColorDlg.RegisterAllHotKey();
	((CMyInterfacePropSheet*)FromHandle(g_MainFormHwnd))->m_CatchWndInfo.RegisterHotkey();
	//this->OnOK();	
}
