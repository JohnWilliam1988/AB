
// AB抓抓Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "MyProcessPicInfo.h"

// CAB抓抓Dlg 对话框
class CAB抓抓Dlg : public CDialogEx
{
// 构造
public:
	CAB抓抓Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMyProcessPicInfo m_picProcessWnd;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabGroup;
};
