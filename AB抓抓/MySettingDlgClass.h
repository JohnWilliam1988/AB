#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMySettingDlgClass �Ի���

class CMySettingDlgClass : public CDialogEx
{
	DECLARE_DYNAMIC(CMySettingDlgClass)

public:
	CMySettingDlgClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMySettingDlgClass();

// �Ի�������
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWinApp* m_pApp;    // ���ڱ���������Ϣ
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
	WORD GetRegisterModfile(WORD inWord);   // ת��ΪRegsiter����ʶ��ļ�ֵ
	WORD GetHotKeyModfile(WORD inWord);   // ת��ΪHotKey�ؼ�ʶ��ļ�ֵ
	afx_msg void OnBnClickedButtonReset();
};
