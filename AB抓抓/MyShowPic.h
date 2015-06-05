#pragma once

#include "afxwin.h"

#define  PIC_OFFSET  5
// CMyShowPic 对话框

class CMyShowPic : public CDialogEx
{
	DECLARE_DYNAMIC(CMyShowPic)

public:
	CMyShowPic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyShowPic();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOWPIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	BOOL CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi);
	BOOL CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC);
public:
	//CMyProcessPicInfo  m_ProcessPic;
	CStatic m_PicShowControl;
	int		m_Height;
	int		m_Width;
	////////记录 鼠标的按下和弹起坐标点//
	CRect	m_Rect;                        // 矩形图
	CPoint	m_StartPos;
	CPoint	m_EndPos;
	CPoint  m_SizePos;
	CPoint	m_RightPos;
	CPoint	m_StoreScreenPos;
	bool	m_MouseClickDown;              //记录鼠标是按下状态
	//////////////////////////////////
	
public:
	bool	ShowBmp(CString path);

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void    SaveBmpFile(CRect lpRect,CString path);
	void	SaveBmpFile(HBITMAP hbmp,CString path);
	HBITMAP CopyRectToBitmap(LPRECT lpRect);
	afx_msg void OnClickSaveMenuBotton();
	afx_msg void OnClickShowFullScreenBotton();
	afx_msg void OnClickCallSystemMakePic();
	afx_msg void OnClickCallDefinePicBotton();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRightClickFullScreen();
	afx_msg void OnAddColor1();
	afx_msg void OnAddColor2();
	afx_msg void OnAddColor3();
	afx_msg void OnAddColor4();
	afx_msg void OnAddColor5();
	afx_msg void OnAddColor6();
	afx_msg void OnAddColor7();
	afx_msg void OnAddColor8();
	afx_msg void OnAddColor9();
	afx_msg void OnAddColor10();
	afx_msg void OnRightClickCallDefineMakePic();
	afx_msg void OnRightClickCallSystemMakePic();
	void LoadClipboardBMP();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
