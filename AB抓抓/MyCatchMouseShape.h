#pragma once
#include "afxwin.h"


// CMyCatchMouseShape 对话框

class CMyCatchMouseShape : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyCatchMouseShape)

public:
	CMyCatchMouseShape();
	virtual ~CMyCatchMouseShape();

// 对话框数据
	enum { IDD = IDD_DIALOG_CATCHMOUSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	HBITMAP m_HBitMap;
	HBITMAP BitmapFromIcon(HICON hIcon);
	int     GetBitmapShape();
	CStatic m_MouseShape1;
	CStatic m_MouseShape2;
	CStatic m_MouseShape3;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	CButton m_CtrlKey;
	CButton m_AltKey;
	afx_msg void OnBnClickedCheckCtrl();
	afx_msg void OnBnClickedCheckAlt();
	CColorStatic m_MouseShapeText;
	afx_msg void OnBnClickedButtonCopycode();
};
