
// AB抓抓.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "AB抓抓Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAB抓抓App

BEGIN_MESSAGE_MAP(CAB抓抓App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAB抓抓App 构造

CAB抓抓App::CAB抓抓App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CAB抓抓App 对象

CAB抓抓App theApp;

HWND				g_MainFormHwnd = NULL;

//CMyDrawPictureClass	g_DrawPicture;
HWND				g_ProcessPicInfoHWND = NULL;
CString				g_CurrentExePath = _T("");      // 当前程序的路径
CButton				g_PicCheck;
CString				g_noteText=_T("");
CString				g_StartPortStr=_T("");
CString				g_EndPortStr=_T("");
CString				g_SizePicStr=_T("");
CString				g_PicPathStr=_T("");
CMenu				g_MenuLeftMouseUp;
CMenu				g_MenuRightMouseUp;
HBITMAP				g_HbitMap = NULL;
///////////全屏显示//////////
CMyPicFullScreenShow g_fullScreenDlg;
CMyShowPic			g_ShowPic;                ////位图显示的类
bool				g_IsFullScreen=false;

/////////////取色器////////////
CMyPickerColor		g_PickColorDlg;

/////////////捕获网页元素//////////
HWND g_CatchElemhWnd = NULL;
/////////////捕获窗口信息//////////
HWND g_CatchWindowshWnd = NULL;
// CAB抓抓App 初始化

BOOL CAB抓抓App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//CAB抓抓Dlg dlg;
	//CMyInterfacePropSheet dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “确定”来关闭对话框的代码
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “取消”来关闭对话框的代码
	//}
	TCHAR currentPath[MAX_PATH] = {0};
	::GetModuleFileNameW(NULL,currentPath,MAX_PATH);    // 获取EXE的路径
	CString help = currentPath;
	int pos = help.ReverseFind(L'\\');
	help = help.Left(pos + 1);  
	g_CurrentExePath = help;

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	CMFCButton::EnableWindowsTheming();

	////////////////////  创建取色器界面  ///////////////
	//g_PickColorDlg.Create(IDD_DIALOG_PICKCOLOR);
	//g_PickColorDlg.ShowWindow(TRUE);
	//////////////////////  创建快速制图界面 ///////////////
	//g_DrawPicture.Create(IDD_DIALOG_DRAWPICTURE);
	//g_DrawPicture.ShowWindow(FALSE);

	/*CMyInterfacePropSheet **/pPropSheet = new CMyInterfacePropSheet;
	m_pMainWnd = pPropSheet;
	pPropSheet->DoModal();

	delete pPropSheet;

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
