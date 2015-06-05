#pragma once
#include "afxwin.h"
#include "ColorStatic.h"
#include <atlimage.h>

// CMyDrawPictureClass �Ի���

class CMyDrawPictureClass : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyDrawPictureClass)

public:
	CMyDrawPictureClass(CWnd* pParent =NULL);
	virtual ~CMyDrawPictureClass();

// �Ի�������
	enum { IDD = IDD_DIALOG_DRAWPICTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CImage			m_SourceImgOriginal;
	CImage			m_TargetImgOriginal;
	int				m_nFilterLoad;
	HCURSOR			m_OldSursor;
	HCURSOR			m_CurrentSursor;

	bool			m_IsMakePic;
	bool			m_IsPicLoaded;
	///////////////�Զ��庯��
	void			Loadbmp(CString path);	
	void			drawPicture();
	void			ChangePicColor(HBITMAP bitmap);
	HBITMAP			m_HSourceBitmap;
	HDC				m_Hdc;
	HDC				m_hMemDC;
	int				m_Width;				// λͼ��ʾ�����
	int				m_Height;				// λͼ��ʾ�����
	COLORREF		m_LowColor;				// ��ɫ
	COLORREF		m_ForegroundColor;		// ǰ̨ɫ
	CString			m_SavePicPath;			// λͼ·��
public:
	HBITMAP			m_Hbitmap;
	HBITMAP			helpBMP;
	CColorStatic	m_SourcePic;
	CColorStatic	m_TargetPic;
	
	CColorStatic	m_LoadSourcePic;
	CColorStatic	m_ProTargetPic;

	CColorStatic	m_BaseColor1;			//��ɫ��ʾ�ؼ�����
	CColorStatic	m_DownColor;			//��ɫ��ʾ�ؼ�����
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
