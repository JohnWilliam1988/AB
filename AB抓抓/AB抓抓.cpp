
// ABץץ.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ABץץ.h"
#include "ABץץDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CABץץApp

BEGIN_MESSAGE_MAP(CABץץApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CABץץApp ����

CABץץApp::CABץץApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CABץץApp ����

CABץץApp theApp;

HWND				g_MainFormHwnd = NULL;

//CMyDrawPictureClass	g_DrawPicture;
HWND				g_ProcessPicInfoHWND = NULL;
CString				g_CurrentExePath = _T("");      // ��ǰ�����·��
CButton				g_PicCheck;
CString				g_noteText=_T("");
CString				g_StartPortStr=_T("");
CString				g_EndPortStr=_T("");
CString				g_SizePicStr=_T("");
CString				g_PicPathStr=_T("");
CMenu				g_MenuLeftMouseUp;
CMenu				g_MenuRightMouseUp;
HBITMAP				g_HbitMap = NULL;
///////////ȫ����ʾ//////////
CMyPicFullScreenShow g_fullScreenDlg;
CMyShowPic			g_ShowPic;                ////λͼ��ʾ����
bool				g_IsFullScreen=false;

/////////////ȡɫ��////////////
CMyPickerColor		g_PickColorDlg;

/////////////������ҳԪ��//////////
HWND g_CatchElemhWnd = NULL;
/////////////���񴰿���Ϣ//////////
HWND g_CatchWindowshWnd = NULL;
// CABץץApp ��ʼ��

BOOL CABץץApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//CABץץDlg dlg;
	//CMyInterfacePropSheet dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȷ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȡ�������رնԻ���Ĵ���
	//}
	TCHAR currentPath[MAX_PATH] = {0};
	::GetModuleFileNameW(NULL,currentPath,MAX_PATH);    // ��ȡEXE��·��
	CString help = currentPath;
	int pos = help.ReverseFind(L'\\');
	help = help.Left(pos + 1);  
	g_CurrentExePath = help;

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	CMFCButton::EnableWindowsTheming();

	////////////////////  ����ȡɫ������  ///////////////
	//g_PickColorDlg.Create(IDD_DIALOG_PICKCOLOR);
	//g_PickColorDlg.ShowWindow(TRUE);
	//////////////////////  ����������ͼ���� ///////////////
	//g_DrawPicture.Create(IDD_DIALOG_DRAWPICTURE);
	//g_DrawPicture.ShowWindow(FALSE);

	/*CMyInterfacePropSheet **/pPropSheet = new CMyInterfacePropSheet;
	m_pMainWnd = pPropSheet;
	pPropSheet->DoModal();

	delete pPropSheet;

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
