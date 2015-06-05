#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMySettingDlgClass 对话框

class CMySettingDlgClass : public CDialogEx
{
	DECLARE_DYNAMIC(CMySettingDlgClass)

public:
	CMySettingDlgClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMySettingDlgClass();

// 对话框数据
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWinApp* m_pApp;    // 用于保存界面的信息
	CComboBox m_ComboCtrl;
	CHotKeyCtrl m_PicHotKeyCtrl;
	virtual BOOL OnInitDialog();
//	afx_msg void OnCbnEditchangeComboId();
	afx_msg void OnCbnSelchangeComboId();
	afx_msg void OnCbnDropdownComboId();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancle();
	CHotKeyCtrl m_OffsetColorCtrl;
	CHotKeyCtrl m_MultPointCtrl;
	CHotKeyCtrl m_CatchScreenCtrl;
	CHotKeyCtrl m_MouseWndCtrl;
	WORD GetRegisterModfile(WORD inWord);   // 转换为Regsiter命令识别的键值
	WORD GetHotKeyModfile(WORD inWord);   // 转换为HotKey控件识别的键值
	afx_msg void OnBnClickedButtonReset();
};
