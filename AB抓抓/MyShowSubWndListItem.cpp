// MyShowSubWndListItem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyShowSubWndListItem.h"
#include "afxdialogex.h"


// CMyShowSubWndListItem �Ի���

IMPLEMENT_DYNAMIC(CMyShowSubWndListItem, CDialogEx)

CMyShowSubWndListItem::CMyShowSubWndListItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyShowSubWndListItem::IDD, pParent)
{

}

CMyShowSubWndListItem::~CMyShowSubWndListItem()
{
}

void CMyShowSubWndListItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyShowSubWndListItem, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMyShowSubWndListItem::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, &CMyShowSubWndListItem::OnBnClickedButtonCancle)
	ON_BN_CLICKED(IDC_CHECK_10JINZHI, &CMyShowSubWndListItem::OnBnClickedCheck10jinzhi)
END_MESSAGE_MAP()


// CMyShowSubWndListItem ��Ϣ�������


void CMyShowSubWndListItem::OnBnClickedButtonOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->OnOK();
}


void CMyShowSubWndListItem::OnBnClickedButtonCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->OnCancel();
}

void	CMyShowSubWndListItem::AddWndHandle(CString wnd,CString wmdClass,CString wndTitle)
{
	CString wndStr=_T("");
	if(((CButton*)GetDlgItem(IDC_CHECK_10JINZHI))->GetCheck() == BST_CHECKED)
	{
		int iWnd = ::wcstol(wnd,NULL,16);
		wnd.Format(_T("%d"),iWnd);
	}
	GetDlgItem(IDC_EDIT_WNDHADLE)->SetWindowTextW(wnd);
	GetDlgItem(IDC_EDIT_WNDCLASSNAME)->SetWindowTextW(wmdClass);
	GetDlgItem(IDC_EDIT_WNDTITLLE)->SetWindowTextW(wndTitle);
}


void CMyShowSubWndListItem::OnBnClickedCheck10jinzhi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString wndStr=_T("");
	if(((CButton*)GetDlgItem(IDC_CHECK_10JINZHI))->GetCheck() == BST_CHECKED) // ת10����
	{
		GetDlgItem(IDC_EDIT_WNDHADLE)->GetWindowTextW(wndStr);
		int iWnd = ::wcstol(wndStr,NULL,16);
		wndStr.Format(_T("%d"),iWnd);		
	}
	else
	{
		// ת16����
		GetDlgItem(IDC_EDIT_WNDHADLE)->GetWindowTextW(wndStr);
		int iWnd = ::wcstol(wndStr,NULL,10);
		wndStr.Format(_T("%x"),iWnd);
	}
	GetDlgItem(IDC_EDIT_WNDHADLE)->SetWindowTextW(wndStr);
}
