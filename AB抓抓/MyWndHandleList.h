#pragma once
#include "afxcmn.h"


// CMyWndHandleList 对话框

class CMyWndHandleList : public CDialogEx
{
	DECLARE_DYNAMIC(CMyWndHandleList)

public:
	CMyWndHandleList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyWndHandleList();

// 对话框数据
	enum { IDD = IDD_DIALOG_WNDHANDLELIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancele();
	CListCtrl m_WndList;
	CString	  m_ListWndHandle;
	virtual BOOL OnInitDialog();
};
