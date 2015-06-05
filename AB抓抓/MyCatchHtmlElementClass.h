#pragma once
#include <mshtml.h>
#include "afxwin.h"
#include "MyPic.h"
#include "ColorStatic.h"

// CMyCatchHtmlElementClass �Ի���

class CMyCatchHtmlElementClass : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CMyCatchHtmlElementClass)

public:
	CMyCatchHtmlElementClass();
	virtual ~CMyCatchHtmlElementClass();

// �Ի�������
	enum { IDD = IDD_DIALOG_CATCHWEB_ELEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	long m_FramesIndex;
	CString m_TypeText;
	CMyPic m_DragCtrl;
	CColorStatic m_TipsTxt;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool EnumWindowFramesEx(IWebBrowser2* pBrowserInput,CString tag,long &pIndex,IHTMLElement* pInElem,long &inFrames);
	bool FindElementInfo(IHTMLDocument2* pHtmlDoc,CString tag,long &pIndex,IHTMLElement* pInElem);
	void ShowElementText(IHTMLElement* pInElem,int index,int frame);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void CatTypeString();
	afx_msg void OnBnClickedCheckClass();
	afx_msg void OnBnClickedCheckFrame();
	afx_msg void OnBnClickedCheckId();
	afx_msg void OnBnClickedCheckIndex();
	afx_msg void OnBnClickedCheckName();
	afx_msg void OnBnClickedCheckTag();
	afx_msg void OnBnClickedCheckTxt();
	afx_msg void OnBnClickedCheckType();
	afx_msg void OnBnClickedCheckValue();
	void ClearAllState();
	// ���Բ�����ҳԪ���Ƿ��ҵ�
	CColorStatic m_FindRetCtrl;
};
