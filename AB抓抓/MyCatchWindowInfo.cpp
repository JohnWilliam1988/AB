// MyCatchWindowInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyCatchWindowInfo.h"
#include "afxdialogex.h"


// CMyCatchWindowInfo �Ի���

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


// CMyCatchWindowInfo ��Ϣ�������


BOOL CMyCatchWindowInfo::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMyCatchWindowInfo::OnBnClickedButtonCatch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
