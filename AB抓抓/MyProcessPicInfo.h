
#pragma once
#include "MyWndHandleList.h"
#include "ColorStatic.h"
#include "afxwin.h"
// CMyProcessPicInfo �Ի���

class CMyProcessPicInfo : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyProcessPicInfo)

public:
	CMyProcessPicInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyProcessPicInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_ProcessPicInfo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CMyWndHandleList m_WndOneHandle;
	// λͼ��·��
	CString m_PicPath;

	void setPicturePathText(CString path);
	void setStartPortText(CString port);
	void setEndPortText(CString port);
	void setSizeText(CString size);

	afx_msg void OnBnClickedButtonLoadbmp();
	afx_msg void OnBnClickedButtonEditbmp();
	virtual BOOL OnInitDialog();
	CMFCButton m_SelectWndHandle;
	afx_msg void OnBnClickedButtonSelectewndhandle();
	CButton m_WndCheckControl;
	afx_msg void OnBnClickedCheckSpecifyhandle();
	CButton m_ShowWndPic;
	afx_msg void OnBnClickedButtonShowwndpic();
	bool SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CColorStatic m_PrintTip;
	afx_msg void OnBnClickedButtonSavepic();
};
