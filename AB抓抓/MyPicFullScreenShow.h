#pragma once
// CMyPicFullScreenShow 对话框

class CMyPicFullScreenShow : public CDialogEx
{
	DECLARE_DYNAMIC(CMyPicFullScreenShow)

public:
	CMyPicFullScreenShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyPicFullScreenShow();

// 对话框数据
	enum { IDD = IDD_DIALOG_FULLSCREENSHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	HBITMAP CopyRectToBitmap(LPRECT lpRect);
	BOOL CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi);
	BOOL CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC);
	BOOL SaveBmpFile(CRect lpRect,CString path);
public:
	int		m_Height;
	int		m_Width;
	int		m_xScreen;
	int		m_yScreen;
	////////记录 鼠标的按下和弹起坐标点//
	CRect	m_Rect;                        // 矩形图
	CPoint	m_StartPos;
	CPoint	m_EndPos;
	CPoint	m_RightPos;
	bool	m_MouseClickDown;              //记录鼠标是按下状态

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	void	paintWindow();
	void	exitWindow();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRightClickFullScreen();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLeftClickFullScreen();
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
	afx_msg void OnPaint();
	afx_msg void OnClickLeftSaveBmp();
	afx_msg void OnClickLeftCallSystemPicture();
	afx_msg void OnClickLeftCallABmakePicture();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
