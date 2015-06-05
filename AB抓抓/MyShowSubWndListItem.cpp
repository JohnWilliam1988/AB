// MyShowSubWndListItem.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyShowSubWndListItem.h"
#include "afxdialogex.h"


// CMyShowSubWndListItem 对话框

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


// CMyShowSubWndListItem 消息处理程序


void CMyShowSubWndListItem::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->OnOK();
}


void CMyShowSubWndListItem::OnBnClickedButtonCancle()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CString wndStr=_T("");
	if(((CButton*)GetDlgItem(IDC_CHECK_10JINZHI))->GetCheck() == BST_CHECKED) // 转10进制
	{
		GetDlgItem(IDC_EDIT_WNDHADLE)->GetWindowTextW(wndStr);
		int iWnd = ::wcstol(wndStr,NULL,16);
		wndStr.Format(_T("%d"),iWnd);		
	}
	else
	{
		// 转16进制
		GetDlgItem(IDC_EDIT_WNDHADLE)->GetWindowTextW(wndStr);
		int iWnd = ::wcstol(wndStr,NULL,10);
		wndStr.Format(_T("%x"),iWnd);
	}
	GetDlgItem(IDC_EDIT_WNDHADLE)->SetWindowTextW(wndStr);
}
