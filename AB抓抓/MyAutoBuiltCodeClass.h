#pragma once
#include "afxwin.h"


// CMyAutoBuiltCodeClass 对话框

class CMyAutoBuiltCodeClass : public CDialogEx
{
	DECLARE_DYNAMIC(CMyAutoBuiltCodeClass)

public:
	CMyAutoBuiltCodeClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyAutoBuiltCodeClass();

// 对话框数据
	enum { IDD = IDD_DIALOG_BUILTCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CColorStatic m_EnCodeText;
	CColorStatic m_CnCodeText;
	CColorStatic m_TipText;
	CString      m_WndTittleText;
	CString      m_EnTextShow;
	CString      m_CnTextShow;
	virtual BOOL OnInitDialog();
	
};
