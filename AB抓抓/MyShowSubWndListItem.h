#pragma once


// CMyShowSubWndListItem 对话框

class CMyShowSubWndListItem : public CDialogEx
{
	DECLARE_DYNAMIC(CMyShowSubWndListItem)

public:
	CMyShowSubWndListItem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyShowSubWndListItem();

// 对话框数据
	enum { IDD = IDD_DIALOG_SUBWNDHANDLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancle();

	void	AddWndHandle(CString wnd,CString wmdClass,CString wndTitle);
	afx_msg void OnBnClickedCheck10jinzhi();
};
