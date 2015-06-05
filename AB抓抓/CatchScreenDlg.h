//#pragma once
//
//
//// CCatchScreenDlg 对话框
//
//class CCatchScreenDlg : public CDialogEx
//{
//	DECLARE_DYNAMIC(CCatchScreenDlg)
//
//public:
//	CCatchScreenDlg(CWnd* pParent = NULL);   // 标准构造函数
//	virtual ~CCatchScreenDlg();
//
//// 对话框数据
//	enum { IDD = IDD_DIALOG_CATCHSCREEN };
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//
//	DECLARE_MESSAGE_MAP()
//};
// CatchScreenDlg.h : header file
//
////////////////////
//     
///
///	  此类是用来处理 截图 保存图片功能
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

	BOOL m_bShowMsg;                //显示截取矩形大小信息
	BOOL m_bDraw;                   //是否为截取状态
	BOOL m_bFirstDraw;              //是否为首次截取
	BOOL m_bQuit;                   //是否为退出
	CPoint m_startPt;				//截取矩形左上角
	CMyTracker m_rectTracker;       //像皮筋类
	CBrush m_brush;					//
    HCURSOR m_hCursor;              //光标
	CBitmap * m_pBitmap;            //背景位图

	CRgn m_rgn;						//背景擦除区域
public:
	HBITMAP CopyScreenToBitmap(LPRECT lpRect,BOOL bSave=FALSE);   //考贝桌面到位图
	void DrawTip();                            //显示操作提示信息
	void DrawMessage(CRect &inRect,CDC * pDC);       //显示截取矩形信息
	void PaintWindow();               //重画窗口
	BOOL CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi);	///创建一个BMP所需的信息结构体
	BOOL CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC);	//创建一个BMP的文件
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

	////保存位图资源
	HBITMAP CopyRectToBitmap(LPRECT lpRect);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAbmakepin();
	afx_msg void OnSysmakepic();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

