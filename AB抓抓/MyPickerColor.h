#pragma once
#include "afxwin.h"
#include "ColorStatic.h"
#include "CatchScreenDlg.h"
#include "afxcmn.h"
// CMyPickerColor �Ի���

class CMyPickerColor : public CDialogEx
{
	DECLARE_DYNAMIC(CMyPickerColor)

public:
	CMyPickerColor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyPickerColor();

// �Ի�������
	enum { IDD = IDD_DIALOG_PICKCOLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//////////////��ʾ�ض���ɫֵ����ɫ10���ؼ�����
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
	///////��ʾƫɫ
	CColorStatic m_GetOffsetColor;
	//CCatchScreenDlg  m_CatchScreenDlg;
	CWinApp* m_pApp;    // ���ڱ���������Ϣ

	CColorStatic m_SetLogText1;

	CColorStatic m_CatchPoint;   //////ץ�����ȼ���ʾ��
	POINT   m_FristPoint;         // ��һ����
	int     m_PointAcount;        // �������
	CString m_FristColor;         // ��һ�������ɫ��Ϣ
	CString m_MutilColor;         // ��¼�����ɫ��Ϣ
	void PromCatchMutiPoint();
public:
	HICON		m_hIcon1;     // ȡɫ����ͼ��
	HICON		m_hIcon2;     // �������ָ���ͼ��
	COLORREF	m_BackColor;  // ������ɫ
	bool		m_Click;      // ����������չ��
	bool		m_MutiClick;  // ����ץ����������չ��
	//////////���洰��ԭ�еĿ�Ȼ��߶�
	int			m_Width;      // ����ԭʼ���ڵĿ��
	int			m_heigth;	  // ����ԭʼ���ڵĸ߶�
	int			m_LastWidth;  // ����ԭʼ���ڵĿ��
	int			m_Lastheigth; // ����ԭʼ���ڵĸ߶�
	POINT		m_LastPoint;  // �����ϴ�����λ��
	COLORREF	m_LastColor;  // �����ϴ����λ�õ���ɫֵ
	///////////�Զ���ķ���
	void runHotKeyFunction(UINT nNote,UINT nEditID,UINT nColorID);

	//��������ϵ�����
	void SaveAllSetText();

	// �����ϴν��汣�������
	void LoadSet();

	// ���ý�����������
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
