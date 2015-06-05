// MyAutoBuiltCodeClass.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyAutoBuiltCodeClass.h"
#include "afxdialogex.h"


// CMyAutoBuiltCodeClass �Ի���

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


// CMyAutoBuiltCodeClass ��Ϣ�������


BOOL CMyAutoBuiltCodeClass::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_EnCodeText.SetBkColor(RGB(6,121,50));
	m_CnCodeText.SetBkColor(RGB(6,121,50));
	m_TipText.SetBkColor(RGB(6,121,50));
	CString tiptext=_T("����Ӣ�Ļ����Ĵ��뵽�ű��༭����ʹ�á�");
	m_TipText.SetWindowTextW(tiptext);
	this->SetWindowTextW(m_WndTittleText);

	this->GetDlgItem(IDC_EDIT_ENCODE)->SetWindowTextW(m_EnTextShow);
	this->GetDlgItem(IDC_EDIT_CNCODE)->SetWindowTextW(m_CnTextShow);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
