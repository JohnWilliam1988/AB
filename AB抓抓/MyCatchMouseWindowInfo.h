#pragma once
#include "afxcmn.h"
#include "MyShowSubWndListItem.h"
#include "afxwin.h"
#include "ColorStatic.h"
#include "MyPic.h"

// CMyCatchMouseWindowInfo 对话框

class CMyCatchMouseWindowInfo : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyCatchMouseWindowInfo)

public:
	CMyCatchMouseWindowInfo();
	virtual ~CMyCatchMouseWindowInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_CATCHWINDOWINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	void catchWndInfoInTimer();

public:
	bool		 m_IsGetWnd;
	HWND		 m_CurrWnd;
	void		 GetWndListTree();
	HTREEITEM	 m_hTree;
	CMyShowSubWndListItem m_ShowItem;
public:
	CTreeCtrl	 m_TreeWndList;	

	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonCatch();
	afx_msg void OnBnClickedButtonCopywndclassname();
	afx_msg void OnBnClickedButtonCopytitle();
	afx_msg void OnBnClickedButtonOprwnd();
	int m_Xpoint;
	int m_Ypoint;
	afx_msg void OnEnChangeEditXpoint();
	afx_msg void OnEnChangeEditYpoint();
	afx_msg void OnNMDblclkTreeWndlist(NMHDR *pNMHDR, LRESULT *pResult);
	/////////设置 提示性内容颜色
	CColorStatic m_CatchTip;
	CColorStatic m_MoveWndTip;
	CMyPic m_DrapCtrl;
	bool m_IsDrapCatch;
	void RegisterHotkey();
};
