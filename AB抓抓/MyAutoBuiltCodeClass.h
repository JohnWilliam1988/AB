#pragma once
#include "afxwin.h"


// CMyAutoBuiltCodeClass �Ի���

class CMyAutoBuiltCodeClass : public CDialogEx
{
	DECLARE_DYNAMIC(CMyAutoBuiltCodeClass)

public:
	CMyAutoBuiltCodeClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyAutoBuiltCodeClass();

// �Ի�������
	enum { IDD = IDD_DIALOG_BUILTCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
