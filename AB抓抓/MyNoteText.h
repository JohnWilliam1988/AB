#pragma once


// CMyNoteText �Ի���

class CMyNoteText : public CDialogEx
{
	DECLARE_DYNAMIC(CMyNoteText)

public:
	CMyNoteText(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyNoteText();

// �Ի�������
	enum { IDD = IDD_DIALOG_NOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
