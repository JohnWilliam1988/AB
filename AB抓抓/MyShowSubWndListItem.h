#pragma once


// CMyShowSubWndListItem �Ի���

class CMyShowSubWndListItem : public CDialogEx
{
	DECLARE_DYNAMIC(CMyShowSubWndListItem)

public:
	CMyShowSubWndListItem(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyShowSubWndListItem();

// �Ի�������
	enum { IDD = IDD_DIALOG_SUBWNDHANDLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancle();

	void	AddWndHandle(CString wnd,CString wmdClass,CString wndTitle);
	afx_msg void OnBnClickedCheck10jinzhi();
};
