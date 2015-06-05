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
	// 获取网页元素的功能
	int HtmlGetData(CString subData,int hwnd);
};
