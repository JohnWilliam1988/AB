
// ABץץDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "MyProcessPicInfo.h"

// CABץץDlg �Ի���
class CABץץDlg : public CDialogEx
{
// ����
public:
	CABץץDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CMyProcessPicInfo m_picProcessWnd;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabGroup;
};
