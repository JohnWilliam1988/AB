// MyNoteText.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyNoteText.h"
#include "afxdialogex.h"

extern   CString g_noteText;
// CMyNoteText �Ի���

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


// CMyNoteText ��Ϣ�������


void CMyNoteText::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->GetDlgItem(IDC_EDIT_NOTE)->GetWindowTextW(g_noteText);
	CDialogEx::OnOK();
}


BOOL CMyNoteText::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	this->GetDlgItem(IDC_EDIT_NOTE)->SetFocus();
	this->GetDlgItem(IDC_EDIT_NOTE)->SetWindowTextW(g_noteText);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
