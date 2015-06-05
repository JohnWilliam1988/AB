// MyNoteText.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyNoteText.h"
#include "afxdialogex.h"

extern   CString g_noteText;
// CMyNoteText 对话框

IMPLEMENT_DYNAMIC(CMyNoteText, CDialogEx)

CMyNoteText::CMyNoteText(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyNoteText::IDD, pParent)
{

}

CMyNoteText::~CMyNoteText()
{
}

void CMyNoteText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyNoteText, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMyNoteText::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyNoteText 消息处理程序


void CMyNoteText::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->GetDlgItem(IDC_EDIT_NOTE)->GetWindowTextW(g_noteText);
	CDialogEx::OnOK();
}


BOOL CMyNoteText::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->GetDlgItem(IDC_EDIT_NOTE)->SetFocus();
	this->GetDlgItem(IDC_EDIT_NOTE)->SetWindowTextW(g_noteText);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
