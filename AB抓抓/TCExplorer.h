#pragma once

#include <afxdhtml.h>

class CTCExplorer
{
public:
	CTCExplorer();   
	~CTCExplorer();
public:
	int m_FramesIndex;
	IWebBrowser2* GetDomFromWndHandleEx(HWND hwnd);
	IWebBrowser2* EnumWindowFramesEx(IWebBrowser2* pWindow,int framesNum);
	// ��ȡ��ҳԪ�صĹ���
	int HtmlGetData(CString subData,int hwnd);
};
