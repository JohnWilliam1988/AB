#pragma once
#include "afxcmn.h"


// CMyWndHandleList �Ի���

class CMyWndHandleList : public CDialogEx
{
	DECLARE_DYNAMIC(CMyWndHandleList)

public:
	CMyWndHandleList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyWndHandleList();

// �Ի�������
	enum { IDD = IDD_DIALOG_WNDHANDLELIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancele();
	CListCtrl m_WndList;
	CString	  m_ListWndHandle;
	virtual BOOL OnInitDialog();
};
