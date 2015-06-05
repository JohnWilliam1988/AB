// MyCatchWindowInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyCatchWindowInfo.h"
#include "afxdialogex.h"


// CMyCatchWindowInfo 对话框

IMPLEMENT_DYNAMIC(CMyCatchWindowInfo, CMFCPropertyPage)

CMyCatchWindowInfo::CMyCatchWindowInfo()
	: CMFCPropertyPage(CMyCatchWindowInfo::IDD)
{

}

CMyCatchWindowInfo::~CMyCatchWindowInfo()
{
}

void CMyCatchWindowInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyCatchWindowInfo, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_CATCH, &CMyCatchWindowInfo::OnBnClickedButtonCatch)
END_MESSAGE_MAP()


// CMyCatchWindowInfo 消息处理程序


BOOL CMyCatchWindowInfo::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMyCatchWindowInfo::OnBnClickedButtonCatch()
{
	// TODO: 在此添加控件通知处理程序代码
}
