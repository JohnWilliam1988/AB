#pragma once
#include "afxwin.h"

#include "ColorStatic.h"
// CMyColorDialogInfo 对话框

class CMyColorDialogInfo : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyColorDialogInfo)

public:
	CMyColorDialogInfo();
	virtual ~CMyColorDialogInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CColorStatic m_ColorShow;
	afx_msg void OnBnClickedButton1();
	CButton m_IsCheckWndHandle;
	int     m_Hue;
	int     m_Saturation;
	int		m_Light;
	void	RGBtoHSL(/*[in]*/const BYTE rColor,/*[in]*/const BYTE gColor,/*[in]*/const BYTE bColor);
	void    CatchColorInfoOnForeground();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEditXpoint();
	afx_msg void OnEnChangeEditYpoint();
	afx_msg void OnEnChangeEditInputhandle();
	CMFCButton m_SelectWndHandle;
	afx_msg void OnBnClickedCheckIswndhandle();
	afx_msg void OnBnClickedButtonSelectwndh();
	bool	processBKWindow(HWND src_hWnd,int &color,int x,int y);
	afx_msg void OnBnClickedButtonMakergb();

	int     RGBStrToIntDate(CString value);     // R G B 三值字符串转换成整型数据
	afx_msg void OnBnClickedButtonLookrgb();
	afx_msg void OnBnClickedRadio16date();
	afx_msg void OnBnClickedRadio10date();
	int m_Selecte16_Date;
	///////设置 标签控件提示内容的颜色////
	CColorStatic m_LogText1;
	CColorStatic m_RGBTextLog;
	CMFCButton m_MakeColorValue;
	CMFCButton m_MakeRGBValue;
	//CMFCButton m_16DataCtrl;
	afx_msg void OnEnChangeEdit16jz();
	afx_msg void OnEnChangeEdit10jz();
	CColorStatic m_ChangeDate;
};
