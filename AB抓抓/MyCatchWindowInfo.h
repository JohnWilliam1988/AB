#pragma once


// CMyCatchWindowInfo 对话框

class CMyCatchWindowInfo : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyCatchWindowInfo)

public:
	CMyCatchWindowInfo();
	virtual ~CMyCatchWindowInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_CATCHWINDOWINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
