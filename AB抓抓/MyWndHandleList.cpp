// MyWndHandleList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyWndHandleList.h"
#include "afxdialogex.h"

static	 int g_ListLineNum = 0;
static	 HWND g_OldWndHandle = NULL;
////////////////////////////////////ö������Ĵ���////////
BOOL CALLBACK MyEnumProc( HWND wnd, LPARAM lParam )
{
	//do something with window here
	CMyWndHandleList* clist = (CMyWndHandleList*)lParam;
	TCHAR wndName[512]={0};
	::GetWindowTextW(wnd,wndName,512);
	if(::wcslen(wndName)==0)
	{
		return TRUE;
	}
	if(::GetParent(wnd)!=NULL)
	{
		return TRUE;
	}
	//clist->m_WndList.InsertItem(g_ListLineNum,wndName);
	TCHAR handleStr[20]={0};
	::wsprintfW(handleStr,_T("%d"),(int)wnd);
	//clist->m_WndList.SetItemText(g_ListLineNum,1,handleStr);
	//clist->m_WndList.SetItemText(g_ListLineNum,2,wndName);
	clist->m_WndList.InsertItem(g_ListLineNum, _T(""));
	clist->m_WndList.SetItem(g_ListLineNum,1,LVIF_TEXT,handleStr,0,0L,0L,0L);
	clist->m_WndList.SetItem(g_ListLineNum,2,LVIF_TEXT,wndName,0,0L,0L,0L);
	g_ListLineNum++;
	return TRUE;
}

// CMyWndHandleList �Ի���

IMPLEMENT_DYNAMIC(CMyWndHandleList, CDialogEx)

CMyWndHandleList::CMyWndHandleList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyWndHandleList::IDD, pParent)
{

}

CMyWndHandleList::~CMyWndHandleList()
{
}

void CMyWndHandleList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WNDLIST, m_WndList);
}


BEGIN_MESSAGE_MAP(CMyWndHandleList, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMyWndHandleList::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCELE, &CMyWndHandleList::OnBnClickedButtonCancele)
END_MESSAGE_MAP()


// CMyWndHandleList ��Ϣ�������
void CMyWndHandleList::OnBnClickedButtonOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	m_ListWndHandle=_T("");
	POSITION pos=m_WndList.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		MessageBox(_T("������ѡ��һ��"),_T("ABץץ"),MB_ICONEXCLAMATION);
		return;
	}
	int nId;
	//�õ��кţ�ͨ��POSITIONת��
	nId=(int)m_WndList.GetNextSelectedItem(pos);
	m_ListWndHandle=m_WndList.GetItemText(nId,1);
	//::AfxMessageBox(m_ListWndHandle);
	g_ListLineNum = 0;
	m_WndList.DeleteAllItems();
}


void CMyWndHandleList::OnBnClickedButtonCancele()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	g_ListLineNum = 0;
	m_WndList.DeleteAllItems();
}


BOOL CMyWndHandleList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	g_ListLineNum = 0;
	DWORD dwStyle = m_WndList.GetExtendedStyle();
	m_WndList.SetExtendedStyle(dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_WndList.InsertColumn(0, _T("ͼ��"));
	m_WndList.InsertColumn(1, _T("���"));
	m_WndList.InsertColumn(2, _T("���ڱ���"));

	m_WndList.SetColumnWidth(0, 40);
	m_WndList.SetColumnWidth(1, 60);
	m_WndList.SetColumnWidth(2, 160);

	//EnumDesktopWindows( ::GetThreadDesktop(GetCurrentThreadId()), MyEnumProc, (LPARAM)this);
	EnumWindows(MyEnumProc, (LPARAM)this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
