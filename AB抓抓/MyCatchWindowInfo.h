#pragma once


// CMyCatchWindowInfo �Ի���

class CMyCatchWindowInfo : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyCatchWindowInfo)

public:
	CMyCatchWindowInfo();
	virtual ~CMyCatchWindowInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_CATCHWINDOWINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
