#pragma once
// CMyPicFullScreenShow �Ի���

class CMyPicFullScreenShow : public CDialogEx
{
	DECLARE_DYNAMIC(CMyPicFullScreenShow)

public:
	CMyPicFullScreenShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyPicFullScreenShow();

// �Ի�������
	enum { IDD = IDD_DIALOG_FULLSCREENSHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	////////��¼ ���İ��º͵��������//
	CRect	m_Rect;                        // ����ͼ
	CPoint	m_StartPos;
	CPoint	m_EndPos;
	CPoint	m_RightPos;
	bool	m_MouseClickDown;              //��¼����ǰ���״̬

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
