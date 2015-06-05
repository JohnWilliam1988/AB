//#pragma once
//
//
//// CCatchScreenDlg �Ի���
//
//class CCatchScreenDlg : public CDialogEx
//{
//	DECLARE_DYNAMIC(CCatchScreenDlg)
//
//public:
//	CCatchScreenDlg(CWnd* pParent = NULL);   // ��׼���캯��
//	virtual ~CCatchScreenDlg();
//
//// �Ի�������
//	enum { IDD = IDD_DIALOG_CATCHSCREEN };
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
//
//	DECLARE_MESSAGE_MAP()
//};
// CatchScreenDlg.h : header file
//
////////////////////
//     
///
///	  �������������� ��ͼ ����ͼƬ����
////
////
////
////////////////////////////////////////////////

#pragma once
#include "MyEdit.h"

#ifndef MYTRACKER_
#include "MyTracker.h"
#endif

/////////////////////////////////////////////////////////////////////////////

class CCatchScreenDlg : public CDialog
{
	DECLARE_DYNAMIC(CCatchScreenDlg)
//**********************************************************************
public:
	int  m_xScreen;
	int  m_yScreen;

	BOOL m_bShowMsg;                //��ʾ��ȡ���δ�С��Ϣ
	BOOL m_bDraw;                   //�Ƿ�Ϊ��ȡ״̬
	BOOL m_bFirstDraw;              //�Ƿ�Ϊ�״ν�ȡ
	BOOL m_bQuit;                   //�Ƿ�Ϊ�˳�
	CPoint m_startPt;				//��ȡ�������Ͻ�
	CMyTracker m_rectTracker;       //��Ƥ����
	CBrush m_brush;					//
    HCURSOR m_hCursor;              //���
	CBitmap * m_pBitmap;            //����λͼ

	CRgn m_rgn;						//������������
public:
	HBITMAP CopyScreenToBitmap(LPRECT lpRect,BOOL bSave=FALSE);   //�������浽λͼ
	void DrawTip();                            //��ʾ������ʾ��Ϣ
	void DrawMessage(CRect &inRect,CDC * pDC);       //��ʾ��ȡ������Ϣ
	void PaintWindow();               //�ػ�����
	BOOL CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi);	///����һ��BMP�������Ϣ�ṹ��
	BOOL CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC);	//����һ��BMP���ļ�
//**********************************************************************
// Construction
public:
	void ChangeRGB();	
	
	CCatchScreenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCatchScreenDlg)
	enum { IDD = IDD_DIALOG_CATCHSCREEN };
	CMyEdit	m_tipEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatchScreenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CCatchScreenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickSaveBmp();
	afx_msg void OnExitCatchScreen();

	////����λͼ��Դ
	HBITMAP CopyRectToBitmap(LPRECT lpRect);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAbmakepin();
	afx_msg void OnSysmakepic();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

