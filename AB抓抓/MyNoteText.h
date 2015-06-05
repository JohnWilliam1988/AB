#pragma once


// CMyNoteText 对话框

class CMyNoteText : public CDialogEx
{
	DECLARE_DYNAMIC(CMyNoteText)

public:
	CMyNoteText(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyNoteText();

// 对话框数据
	enum { IDD = IDD_DIALOG_NOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
