#pragma once
#include "afxcmn.h"
#include "MyProcessPicInfo.h"        //  ͼƬ��ʾ�ͼ򵥴�����
#include "MyCatchMouseWindowInfo.h"  //  ץȡ��굱ǰ������Ϣ
#include "MyCatchMouseShape.h"       //  ץ��������봦����
#include "MyColorDialogInfo.h"       //  ץɫ�ȴ�����
#include "MyDrawPictureClass.h"
#include "MyCatchHtmlElementClass.h" //	 ץȡ��ҳ��Ԫ��

#define		IDC_BUTTON_SHOWCATCHCOLOR	 5325322
#define		IDC_BUTTON_SHOWPICTURE		 5325323
#define		IDC_BUTTON_SHOWSETTING		 5325324

class CMyInterfacePropSheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(CMyInterfacePropSheet)

// Construction
public:
	CMyInterfacePropSheet(CWnd* pParentWnd = NULL);

// Attributes
public:
	CMyProcessPicInfo		m_PicInfoPage;
	CMyColorDialogInfo		m_ColorInfo;
	CMyCatchMouseWindowInfo	m_CatchWndInfo;
	CMyCatchMouseShape		m_CatchMouseShape;
	HICON m_hIcon;
	CMyDrawPictureClass		m_DrawPicWnd;
	//CMyPickerColor			m_PickerColor;
	CMyCatchHtmlElementClass m_CatchWebElem;
// Overrides
public:
	virtual BOOL OnInitDialog();

// Implementation
public:
	virtual	~CMyInterfacePropSheet(void);
	CButton m_ColorCheck;
	CButton m_BtnSetting;
protected:
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedShowGetColorCheckButton();
	afx_msg void OnBnClickedShowPicCheckButton();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void activeCurrentPage(int page);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//afx_msg LRESULT OnClosePickerMSG(WPARAM, LPARAM);
	//afx_msg LRESULT OnCloseMakePicMSG(WPARAM, LPARAM);
	
	afx_msg void OnDestroy();
	afx_msg void OnClickShowSetting();
//	afx_msg void OnNcPaint();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

