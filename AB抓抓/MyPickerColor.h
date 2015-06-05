#pragma once
#include "afxwin.h"
#include "ColorStatic.h"
#include "CatchScreenDlg.h"
#include "afxcmn.h"
// CMyPickerColor 对话框

class CMyPickerColor : public CDialogEx
{
	DECLARE_DYNAMIC(CMyPickerColor)

public:
	CMyPickerColor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyPickerColor();

// 对话框数据
	enum { IDD = IDD_DIALOG_PICKCOLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//////////////显示特定颜色值的颜色10个控件变量
	CColorStatic m_SeeColor1;
	CColorStatic m_SeeColor2;
	CColorStatic m_SeeColor3;
	CColorStatic m_SeeColor4;
	CColorStatic m_SeeColor5;
	CColorStatic m_SeeColor6;
	CColorStatic m_SeeColor7;
	CColorStatic m_SeeColor8;
	CColorStatic m_SeeColor9;
	CColorStatic m_SeeColor10;
	///////显示偏色
	CColorStatic m_GetOffsetColor;
	//CCatchScreenDlg  m_CatchScreenDlg;
	CWinApp* m_pApp;    // 用于保存界面的信息

	CColorStatic m_SetLogText1;

	CColorStatic m_CatchPoint;   //////抓多点的热键提示语
	POINT   m_FristPoint;         // 第一个点
	int     m_PointAcount;        // 点的数量
	CString m_FristColor;         // 第一个点的颜色信息
	CString m_MutilColor;         // 记录多点颜色信息
	void PromCatchMutiPoint();
public:
	HICON		m_hIcon1;     // 取色器的图标
	HICON		m_hIcon2;     // 保存鼠标指针的图标
	COLORREF	m_BackColor;  // 保存颜色
	bool		m_Click;      // 控制收缩与展开
	bool		m_MutiClick;  // 控制抓多点的收缩与展开
	//////////保存窗口原有的宽度还高度
	int			m_Width;      // 保存原始窗口的宽度
	int			m_heigth;	  // 保存原始窗口的高度
	int			m_LastWidth;  // 保存原始窗口的宽度
	int			m_Lastheigth; // 保存原始窗口的高度
	POINT		m_LastPoint;  // 保存上次鼠标的位置
	COLORREF	m_LastColor;  // 保存上次鼠标位置的颜色值
	///////////自定义的方法
	void runHotKeyFunction(UINT nNote,UINT nEditID,UINT nColorID);

	//保存界面上的数据
	void SaveAllSetText();

	// 加载上次界面保存的数据
	void LoadSet();

	// 重置界面所有数据
	void Reset();

	void RegisterAllHotKey();

	bool m_IsCatchScreen;

	void	RightClickPickColor(UINT key,CPoint spt,CPoint bkPt);
	void	runIntWndHotKeyFunction(UINT nNote,UINT nEditID,UINT nColorID,CPoint spt,CPoint bkPt);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonZhedie();
	afx_msg void OnBnClickedButtonCatchscreen();
	CStatic m_postX;
	CStatic m_postY;
	CStatic m_rgb_r;
	CStatic m_rgb_g;
	CStatic m_rgb_b;
	CStatic m_colorValue;
	afx_msg void OnStnDblclickStaticNote1();
	afx_msg void OnStnDblclickStaticNote2();
	afx_msg void OnStnDblclickStaticNote3();
	afx_msg void OnStnDblclickStaticNote4();
	afx_msg void OnStnDblclickStaticNote5();
	afx_msg void OnStnDblclickStaticNote6();
	afx_msg void OnStnDblclickStaticNote7();
	afx_msg void OnStnDblclickStaticNote8();
	afx_msg void OnStnDblclickStaticNote9();
	afx_msg void OnStnDblclickStaticNote10();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
//	afx_msg void OnClose();
	int m_SetDefineX;
	int m_SetDefineY;
	
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonFindmutipoint();
	CListCtrl m_MutiPointAndColor;
	afx_msg void OnBnClickedButtonClearalldata();
	afx_msg void OnBnClickedButtonDeletelaststep();
	afx_msg void OnBnClickedCheckSettop();
	afx_msg void OnEnChangeEditSetdefx();
	afx_msg void OnEnUpdateEditSetdefy();
	afx_msg void OnBnClickedBtnClearall();
};
