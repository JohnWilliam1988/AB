// MyAutoBuiltCodeClass.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyAutoBuiltCodeClass.h"
#include "afxdialogex.h"


// CMyAutoBuiltCodeClass 对话框

IMPLEMENT_DYNAMIC(CMyAutoBuiltCodeClass, CDialogEx)

CMyAutoBuiltCodeClass::CMyAutoBuiltCodeClass(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyAutoBuiltCodeClass::IDD, pParent)
{
	m_EnTextShow = _T("");
	m_CnTextShow = _T("");
	m_WndTittleText = _T("");
}

CMyAutoBuiltCodeClass::~CMyAutoBuiltCodeClass()
{
}

void CMyAutoBuiltCodeClass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ENTEXT, m_EnCodeText);
	DDX_Control(pDX, IDC_STATIC_CNTEXT, m_CnCodeText);
	DDX_Control(pDX, IDC_STATIC_TIPTEXT, m_TipText);
}


BEGIN_MESSAGE_MAP(CMyAutoBuiltCodeClass, CDialogEx)
END_MESSAGE_MAP()


// CMyAutoBuiltCodeClass 消息处理程序


BOOL CMyAutoBuiltCodeClass::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_EnCodeText.SetBkColor(RGB(6,121,50));
	m_CnCodeText.SetBkColor(RGB(6,121,50));
	m_TipText.SetBkColor(RGB(6,121,50));
	CString tiptext=_T("复制英文或中文代码到脚本编辑框中使用。");
	m_TipText.SetWindowTextW(tiptext);
	this->SetWindowTextW(m_WndTittleText);

	this->GetDlgItem(IDC_EDIT_ENCODE)->SetWindowTextW(m_EnTextShow);
	this->GetDlgItem(IDC_EDIT_CNCODE)->SetWindowTextW(m_CnTextShow);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
