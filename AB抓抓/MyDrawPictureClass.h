#pragma once
#include "afxwin.h"
#include "ColorStatic.h"
#include <atlimage.h>

// CMyDrawPictureClass 对话框

class CMyDrawPictureClass : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyDrawPictureClass)

public:
	CMyDrawPictureClass(CWnd* pParent =NULL);
	virtual ~CMyDrawPictureClass();

// 对话框数据
	enum { IDD = IDD_DIALOG_DRAWPICTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CImage			m_SourceImgOriginal;
	CImage			m_TargetImgOriginal;
	int				m_nFilterLoad;
	HCURSOR			m_OldSursor;
	HCURSOR			m_CurrentSursor;

	bool			m_IsMakePic;
	bool			m_IsPicLoaded;
	///////////////自定义函数
	void			Loadbmp(CString path);	
	void			drawPicture();
	void			ChangePicColor(HBITMAP bitmap);
	HBITMAP			m_HSourceBitmap;
	HDC				m_Hdc;
	HDC				m_hMemDC;
	int				m_Width;				// 位图显示区域宽
	int				m_Height;				// 位图显示区域高
	COLORREF		m_LowColor;				// 底色
	COLORREF		m_ForegroundColor;		// 前台色
	CString			m_SavePicPath;			// 位图路径
public:
	HBITMAP			m_Hbitmap;
	HBITMAP			helpBMP;
	CColorStatic	m_SourcePic;
	CColorStatic	m_TargetPic;
	
	CColorStatic	m_LoadSourcePic;
	CColorStatic	m_ProTargetPic;

	CColorStatic	m_BaseColor1;			//基色显示控件变量
	CColorStatic	m_DownColor;			//底色显示控件变量
	virtual BOOL	OnInitDialog();
	afx_msg void	OnBnClickedButtonLoadbmp();	
	afx_msg void	OnPaint();
	afx_msg void	OnStnClickedStaticDowncolor();
//	afx_msg void OnStnClickedStaticBasecolor1();
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL	PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL	OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void	OnDestroy();
	afx_msg void	OnBnClickedButtonSavepic();
	afx_msg void	OnBnClickedButtonChangeoffsetcolor();
	afx_msg void OnBnClickedButtonEditpic();
//	afx_msg void OnClose();
	CColorStatic m_DrawTipText;
	CMFCButton m_btLoadBmpCtrl;
	CMFCButton m_btSaveBmpCtrl;
	CMFCButton m_btEditBmpCtrl;
	afx_msg void OnBnClickedBtnTestpic();
	afx_msg void OnBnClickedBtnBuiltcode();
	CColorStatic m_TestFindpicLog;
};
