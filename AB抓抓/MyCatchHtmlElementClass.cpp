// MyCatchHtmlElementClass.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyCatchHtmlElementClass.h"
#include "afxdialogex.h"
#include "TCExplorer.h"
#include < oleacc.h >
#pragma comment ( lib, "oleacc" )

#include <UrlMon.h>


extern HWND g_CatchElemhWnd;

// CMyCatchHtmlElementClass 对话框

IMPLEMENT_DYNAMIC(CMyCatchHtmlElementClass, CMFCPropertyPage)

CMyCatchHtmlElementClass::CMyCatchHtmlElementClass()
	: CMFCPropertyPage(CMyCatchHtmlElementClass::IDD)
{
	m_TypeText = _T("");
	::CoInitialize(NULL);
}

CMyCatchHtmlElementClass::~CMyCatchHtmlElementClass()
{
	::CoUninitialize();
}

void CMyCatchHtmlElementClass::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CATCHHTML_PIC, m_DragCtrl);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_TipsTxt);
	DDX_Control(pDX, IDC_STATIC_FINDRET, m_FindRetCtrl);
}


BEGIN_MESSAGE_MAP(CMyCatchHtmlElementClass, CMFCPropertyPage)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_CLASS, &CMyCatchHtmlElementClass::OnBnClickedCheckClass)
	ON_BN_CLICKED(IDC_CHECK_FRAME, &CMyCatchHtmlElementClass::OnBnClickedCheckFrame)
	ON_BN_CLICKED(IDC_CHECK_ID, &CMyCatchHtmlElementClass::OnBnClickedCheckId)
	ON_BN_CLICKED(IDC_CHECK_INDEX, &CMyCatchHtmlElementClass::OnBnClickedCheckIndex)
	ON_BN_CLICKED(IDC_CHECK_NAME, &CMyCatchHtmlElementClass::OnBnClickedCheckName)
	ON_BN_CLICKED(IDC_CHECK_TAG, &CMyCatchHtmlElementClass::OnBnClickedCheckTag)
	ON_BN_CLICKED(IDC_CHECK_TXT, &CMyCatchHtmlElementClass::OnBnClickedCheckTxt)
	ON_BN_CLICKED(IDC_CHECK_TYPE, &CMyCatchHtmlElementClass::OnBnClickedCheckType)
	ON_BN_CLICKED(IDC_CHECK_VALUE, &CMyCatchHtmlElementClass::OnBnClickedCheckValue)
END_MESSAGE_MAP()


// CMyCatchHtmlElementClass 消息处理程序


BOOL CMyCatchHtmlElementClass::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_CatchElemhWnd = this->m_hWnd;
	//m_DragCtrl.SubclassDlgItem(IDC_CATCHHTML_PIC,this);
	CString tips = _T("<-- 拖动图标到网页，获取鼠标当前的元素内容！首次获取元素时，可能会有一点延时，之后就好了！");
	m_TipsTxt.SetTextColor(RGB(6,121,50));
	m_TipsTxt.SetWindowTextW(tips);
	tips = _T("查找结果:特征字符串找到 0 个");
	m_FindRetCtrl.SetTextColor(RGB(6,121,50));
	m_FindRetCtrl.SetWindowTextW(tips);

	GetDlgItem(IDC_CHECK_TAG)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_VALUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_INDEX)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_CLASS)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_TXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_FRAME)->EnableWindow(FALSE);
	//GetDlgItem(IDC_EDIT_TYPESTRING)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

///通过窗口名获取Dom对象
IWebBrowser2* GetDomFromWndHandleEx(HWND hwnd)
{	
	IWebBrowser2* pWebbrowser = NULL;
	HINSTANCE hInst = LoadLibrary( _T("OLEACC.DLL") );
	if ( hInst == NULL ) return NULL;

	LRESULT lRes;
	UINT nMsg = ::RegisterWindowMessage( _T("WM_HTML_GETOBJECT") );
	::SendMessageTimeout( hwnd, nMsg, 0L, 0L,SMTO_NORMAL|SMTO_BLOCK/*SMTO_ABORTIFHUNG*/, 1000, (DWORD*)&lRes );
	LPFNOBJECTFROMLRESULT pfObjectFromLresult = (LPFNOBJECTFROMLRESULT)::GetProcAddress( hInst, ("ObjectFromLresult") );
	if ( pfObjectFromLresult != NULL )
	{
		HRESULT hr;
		CComPtr<IHTMLDocument2> spDoc;
		hr=pfObjectFromLresult(lRes,IID_IHTMLDocument2,0,(void**)&spDoc);
		if ( SUCCEEDED(hr) )
		{
			CComPtr<IHTMLWindow2> spWnd2;
			CComPtr<IServiceProvider>spServiceProv;
			hr=spDoc->get_parentWindow ((IHTMLWindow2**)&spWnd2);
			if(SUCCEEDED(hr))
			{
				hr=spWnd2->QueryInterface (IID_IServiceProvider,(void**)&spServiceProv);
				if(SUCCEEDED(hr))
				{
					hr = spServiceProv->QueryService(SID_SWebBrowserApp,IID_IWebBrowser2,(void**)&pWebbrowser);
				}
				spServiceProv.Release();
			}
		}
	}
	::FreeLibrary(hInst);	
	return pWebbrowser;
}
// 获取元素的位置
HRESULT GetElementOffset( IHTMLElement *pElement, SIZE &offset )
{
	if( !pElement )
	{
		return E_POINTER;
	}
	::ZeroMemory( &offset, sizeof( SIZE ) );
	HRESULT hr;
	try
	{
		CComPtr< IHTMLElement > pParent;
		hr = pElement->get_offsetParent( &pParent );
		if( pParent )
		{
			hr = GetElementOffset( pParent, offset );
		}

		POINT   ptScroll = { 0 };
		CComQIPtr< IHTMLTextContainer > pTC = pElement;
		if( pTC )
		{
			pTC->get_scrollLeft( &ptScroll.x );
			pTC->get_scrollTop( &ptScroll.y );
		}

		POINT   ptClient = { 0 };
		CComQIPtr< IHTMLControlElement >    pCE = pElement;
		if( pCE )
		{
			pCE->get_clientLeft( &ptClient.x );
			pCE->get_clientTop( &ptClient.y );
		}

		long    cx, cy;
		hr = pElement->get_offsetLeft( &cx );
		hr = pElement->get_offsetTop( &cy );

		offset.cx = offset.cx + cx - ptScroll.x + ptClient.x;
		offset.cy = offset.cy + cy - ptScroll.y + ptClient.y;
	}
	catch( HRESULT )
	{
	}

	return hr;
}
// 获取鼠标当前位置的元素
HRESULT HitTest( IWebBrowser2 *pWB, const POINT &pt, IHTMLElement **ppElement)
{
	if( pWB == NULL )
	{
		return E_INVALIDARG;
	}

	if( !ppElement )
	{
		return E_POINTER;
	}

	*ppElement = NULL;
	HRESULT  hr;
	try
	{
		CComPtr< IDispatch > pDisp;
		hr = pWB->get_Document( &pDisp );

		CComQIPtr< IHTMLDocument2 > pDoc = pDisp;
		if( pDoc == NULL )
		{
			return S_OK;
		}

		CComPtr< IHTMLElement > pElement;
		hr = pDoc->elementFromPoint( pt.x, pt.y, &pElement );
		if( pElement == NULL )
		{
			return S_OK;
		}

		CComQIPtr< IWebBrowser2 > pFrame = pElement;
		if( pFrame )
		{
			SIZE    offset;
			hr = GetElementOffset( pElement, offset );
			POINT   ptInFrame = { pt.x - offset.cx, pt.y - offset.cy };
			return HitTest( pFrame, ptInFrame, ppElement);
		}
		hr = pElement->QueryInterface( IID_IHTMLElement,reinterpret_cast< void ** >( ppElement ));
	}
	catch( HRESULT )
	{

	}

	return hr;
}

void CMyCatchHtmlElementClass::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		ClearAllState();
		CString TagStr=L"";
		POINT point;
		::GetCursorPos(&point);
		HWND hWnd = ::WindowFromPoint(point);

		CString helpStr;
		helpStr.Format(_T("%d"),hWnd);
		this->GetDlgItem(IDC_EDIT_HWND)->SetWindowText(helpStr);

		TCHAR buffer[512]={0};
		// 获取窗口的类名
		::GetClassNameW(hWnd,buffer,512);
		helpStr.Format(L"%s",buffer);
		if(helpStr.CompareNoCase(L"Internet Explorer_Server") == 0)
		{
			m_FindRetCtrl.SetWindowTextW(_T(""));
			m_FramesIndex = -1;
			HRESULT hr;
			CComPtr<IWebBrowser2> spWeb;
			CComPtr<IHTMLDocument2> spDoc;
			spWeb = GetDomFromWndHandleEx(hWnd);
			if(spWeb == NULL)
			{
				m_FindRetCtrl.SetWindowTextW(_T("获取目标窗口信息失败!"));
				return ;
			}

			IDispatch* disp=NULL; 
			hr = spWeb->get_Document(&disp);
			if(SUCCEEDED(hr))
			{
				if(FAILED(disp->QueryInterface(IID_IHTMLDocument2,(void**)&spDoc)))
				{
					m_FindRetCtrl.SetWindowTextW(_T("获取目标窗口标题信息失败!"));
					return ;
				}
				BSTR bstr;
				spDoc->get_title(&bstr);
				this->GetDlgItem(IDC_EDIT_TITLE)->SetWindowText(bstr);
			}
			POINT tPoint;
			tPoint = point;
			::ScreenToClient(hWnd,&tPoint);

			CComPtr<IHTMLElement> pElement;
			hr = HitTest(spWeb,tPoint,&pElement);
			if(pElement == NULL)
			{
				m_FindRetCtrl.SetWindowTextW(_T("获取pElement信息失败!"));
				/*hr = spDoc->elementFromPoint( tPoint.x, tPoint.y, &pElement );
				if(FAILED(hr))*/
				return ;
					//IHTMLWindow2 *pWindow;
					//pWindow->scroll(10,10);
					//pWindow->scrollBy(10,10);
					//pWindow->scrollTo(10,10);
			}
			if ( SUCCEEDED(hr)&&pElement)
			{
				CComBSTR pTagStr;
				hr = pElement->get_tagName(&pTagStr);
				TagStr.Format(L"%s",pTagStr);
				long index = -1,frames = -1;
				EnumWindowFramesEx(spWeb,TagStr,index,pElement,frames); 
				ShowElementText(pElement,index,frames);
			}
			else
			{
				m_FindRetCtrl.SetWindowTextW(_T("获取网页内元素信息失败!"));
			}
		}		
		else
		{
			m_FindRetCtrl.SetWindowTextW(_T("目标窗口非IE窗口!"));
			return ;
		}
	}
	CMFCPropertyPage::OnTimer(nIDEvent);
}

bool CMyCatchHtmlElementClass::EnumWindowFramesEx(IWebBrowser2* pBrowserInput,CString tag,long &pIndex,IHTMLElement* pInElem,long &inFrames)
{
	LPDISPATCH lpDisp = NULL;
	pBrowserInput->get_Document(&lpDisp);
	CComQIPtr< IHTMLDocument2 > pHTMLDoc; //
	HRESULT hr ;
	hr = lpDisp->QueryInterface(IID_IHTMLDocument2,(void**)&pHTMLDoc);
	if(SUCCEEDED(hr))
	{
		if(FindElementInfo(pHTMLDoc,tag,pIndex,pInElem))
			return true;
	}
	IWebBrowser2* pBrowserFrame=NULL;
	if (lpDisp)
	{
		IOleContainer* pContainer;
		hr = lpDisp->QueryInterface(IID_IOleContainer,(void**)&pContainer);
		lpDisp->Release();
		if (FAILED(hr))
			return false;

		IEnumUnknown* pEnumerator;
		hr = pContainer->EnumObjects(OLECONTF_EMBEDDINGS, &pEnumerator);
		pContainer->Release();
		if (FAILED(hr))
			return false;

		IUnknown* pUnk;
		ULONG uFetched;
		int helpIndex=0;
		for (UINT i = 0; S_OK == pEnumerator->Next(1, &pUnk, &uFetched); i++)
		{
			m_FramesIndex ++;
			hr = pUnk->QueryInterface(IID_IWebBrowser2,(void**)&pBrowserFrame);
			pUnk->Release();
			if (SUCCEEDED(hr))
			{
				if(EnumWindowFramesEx(pBrowserFrame,tag,pIndex,pInElem,inFrames))
				{
					inFrames = m_FramesIndex;
					pBrowserFrame->Release();
					return true;
				}
				pBrowserFrame->Release();
			}
		}
		pEnumerator->Release();
	}
	return false;
}

bool CMyCatchHtmlElementClass::FindElementInfo(IHTMLDocument2* pHtmlDoc,CString tag,long &pIndex,IHTMLElement* pInElem)
{
	HRESULT hr;
	IHTMLElementCollection* pElementColl = NULL;  //
	CComQIPtr< IHTMLDocument3 > pDoc3 ;
	pDoc3 = pHtmlDoc;
	if(pDoc3)
	{
		CComBSTR tagBstr(tag);
		hr = pDoc3->getElementsByTagName(tagBstr,&pElementColl);
		if(SUCCEEDED(hr))
		{
			long length = 0;
			DWORD ss = ::GetTickCount();
			if(SUCCEEDED(hr = pElementColl->get_length(&length)) && (length))
			{
				CComBSTR pClassStr,pIdStr,pTagStr,pNameStr,pTypeStr,pValueStr,pTextStr;
				VARIANT	Index;
				VARIANT	var2;
				IDispatch*	pDisp2	= NULL;
				IHTMLElement* pElement2 = NULL;
				Index.vt =	VT_UINT;
				for(int x = 0; x < length; x++ )
				{					
					Index.lVal	= x;
					VariantInit( &var2 );
					IDispatch*	pDisp2	= NULL;
					if(SUCCEEDED(hr = pElementColl->item (Index, var2, &pDisp2)))
					{
						if(pDisp2&&SUCCEEDED(pDisp2->QueryInterface(IID_IHTMLElement,(void**)&pElement2)))
						{
							if(pInElem != pElement2)
							{
								continue;
							}
							pIndex = x;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void CMyCatchHtmlElementClass::ShowElementText(IHTMLElement* pInElem,int index,int frame)
{
	VARIANT rv;
	CComBSTR cBstr;
	CString strAtt = _T("");
	pInElem->get_tagName(&cBstr);
	if(cBstr.Length() != 0)	
	{
		strAtt.Format(_T("%s"),cBstr);
		((CButton*)GetDlgItem(IDC_CHECK_TAG))->EnableWindow(TRUE);
	}
	else
		((CButton*)GetDlgItem(IDC_CHECK_TAG))->EnableWindow(FALSE);
	this->SetDlgItemTextW(IDC_EDIT_TAG,strAtt);  // 设置tag内容

	pInElem->get_id(&cBstr);
	strAtt.Empty();
	if(cBstr.Length() != 0)	
	{
		strAtt.Format(_T("%s"),cBstr);
		((CButton*)GetDlgItem(IDC_CHECK_ID))->EnableWindow(TRUE);
	}
	else
		((CButton*)GetDlgItem(IDC_CHECK_ID))->EnableWindow(FALSE);
	this->SetDlgItemTextW(IDC_EDIT_ID,strAtt);  // 设置id内容

	pInElem->get_outerText(&cBstr);
	strAtt.Empty();
	if(cBstr.Length() != 0)	
	{
		strAtt.Format(_T("%s"),cBstr);
		((CButton*)GetDlgItem(IDC_CHECK_TXT))->EnableWindow(TRUE);
	}
	else
		((CButton*)GetDlgItem(IDC_CHECK_TXT))->EnableWindow(FALSE);
	this->SetDlgItemTextW(IDC_EDIT1_TXT,strAtt);  // 设置Txt内容

	pInElem->get_className(&cBstr);
	strAtt.Empty();
	if(cBstr.Length() != 0)
	{
		strAtt.Format(_T("%s"),cBstr);
		((CButton*)GetDlgItem(IDC_CHECK_CLASS))->EnableWindow(TRUE);
	}
	else
		((CButton*)GetDlgItem(IDC_CHECK_CLASS))->EnableWindow(FALSE);
	this->SetDlgItemTextW(IDC_EDIT_CLASS,strAtt);  // 设置class内容

	strAtt=_T("type");
	pInElem->getAttribute(strAtt.AllocSysString(),0,&rv);
	strAtt = rv.bstrVal;
	if(strAtt.GetLength() == 0) // 没内容就不显示
		((CButton*)GetDlgItem(IDC_CHECK_TYPE))->EnableWindow(FALSE);
	else
		((CButton*)GetDlgItem(IDC_CHECK_TYPE))->EnableWindow(TRUE);
	this->SetDlgItemTextW(IDC_EDIT_TYPE,strAtt);  // 设置type内容

	strAtt=_T("name");
	pInElem->getAttribute(strAtt.AllocSysString(),0,&rv);
	strAtt = rv.bstrVal;
	if(strAtt.GetLength() == 0) // 没内容就不显示
		((CButton*)GetDlgItem(IDC_CHECK_NAME))->EnableWindow(FALSE);
	else
		((CButton*)GetDlgItem(IDC_CHECK_NAME))->EnableWindow(TRUE);
	this->SetDlgItemTextW(IDC_EDIT_NAME,strAtt);  // 设置name内容

	strAtt=_T("value");
	pInElem->getAttribute(strAtt.AllocSysString(),0,&rv);
	strAtt = rv.bstrVal;
	if(strAtt.GetLength() == 0) // 没内容就不显示
		((CButton*)GetDlgItem(IDC_CHECK_VALUE))->EnableWindow(FALSE);
	else
		((CButton*)GetDlgItem(IDC_CHECK_VALUE))->EnableWindow(TRUE);
	this->SetDlgItemTextW(IDC_EDIT_VALUE,strAtt);  // 设置value内容

	strAtt.Format(_T("%d"),index);
	GetDlgItem(IDC_CHECK_INDEX)->EnableWindow(TRUE);
	this->SetDlgItemTextW(IDC_EDIT_INDEX,strAtt);  // 设置index内容

	strAtt.Empty();
	if(frame != -1)
	{
		strAtt.Format(_T("%d"),frame);
		((CButton*)GetDlgItem(IDC_CHECK_FRAME))->EnableWindow(TRUE);
	}
	else
		((CButton*)GetDlgItem(IDC_CHECK_FRAME))->EnableWindow(FALSE);
	this->SetDlgItemTextW(IDC_EDIT_FRAME,strAtt);  // 设置frame内容
}

BOOL CMyCatchHtmlElementClass::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CMFCPropertyPage::PreTranslateMessage(pMsg);
}

void CMyCatchHtmlElementClass::CatTypeString()
{
	m_FindRetCtrl.SetWindowTextW(_T("提示:匹配过程中,请稍等……"));
	::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_WAIT)));
	CString capStr = _T("");
	CButton* button = ((CButton*)GetDlgItem(IDC_CHECK_TAG));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT_TAG,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("tag:") + capStr;
			else m_TypeText = m_TypeText + _T("&tag:") + capStr;
		}
	}

	button = ((CButton*)GetDlgItem(IDC_CHECK_ID));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT_ID,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("id:") + capStr;
			else m_TypeText = m_TypeText + _T("&id:") + capStr;
		}
	}

	button = ((CButton*)GetDlgItem(IDC_CHECK_NAME));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT_NAME,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("name:") + capStr;
			else m_TypeText = m_TypeText + _T("&name:") + capStr;
		}
	}

	button = ((CButton*)GetDlgItem(IDC_CHECK_TYPE));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT_TYPE,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("type:") + capStr;
			else m_TypeText = m_TypeText + _T("&type:") + capStr;
		}
	}

	button = ((CButton*)GetDlgItem(IDC_CHECK_VALUE));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT_VALUE,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("value:") + capStr;
			else m_TypeText = m_TypeText + _T("&value:") + capStr;
		}
	}

	button = ((CButton*)GetDlgItem(IDC_CHECK_INDEX));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT_INDEX,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("index:") + capStr;
			else m_TypeText = m_TypeText + _T("&index:") + capStr;
		}
	}

	button = ((CButton*)GetDlgItem(IDC_CHECK_CLASS));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT_CLASS,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("class:") + capStr;
			else m_TypeText = m_TypeText + _T("&class:") + capStr;
		}
	}

	button = ((CButton*)GetDlgItem(IDC_CHECK_TXT));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT1_TXT,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("txt:") + capStr;
			else m_TypeText = m_TypeText + _T("&txt:") + capStr;
		}
	}

	button = ((CButton*)GetDlgItem(IDC_CHECK_FRAME));
	if(button->IsWindowEnabled())
	{
		if(button->GetCheck() == BST_CHECKED)
		{
			GetDlgItemTextW(IDC_EDIT_FRAME,capStr);
			if(m_TypeText.IsEmpty()) m_TypeText = m_TypeText + _T("frame:") + capStr;
			else m_TypeText = m_TypeText + _T("&frame:") + capStr;
		}
	}
	SetDlgItemTextW(IDC_EDIT_TYPESTRING,m_TypeText);
	int hwnd = GetDlgItemInt(IDC_EDIT_HWND);
	CTCExplorer myFindElem;
	int num = myFindElem.HtmlGetData(m_TypeText,hwnd);
	CString tips;
	tips.Format(_T("查找结果:与特征字符串匹配的找到 %d 个"),num);
	m_FindRetCtrl.SetWindowTextW(tips);
	::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
	return ;
}


void CMyCatchHtmlElementClass::OnBnClickedCheckClass()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TypeText = _T("");
	CatTypeString();
}


void CMyCatchHtmlElementClass::OnBnClickedCheckFrame()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TypeText = _T("");
	CatTypeString();
}


void CMyCatchHtmlElementClass::OnBnClickedCheckId()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TypeText = _T("");
	CatTypeString();
}


void CMyCatchHtmlElementClass::OnBnClickedCheckIndex()
{
	// TODO: 在此添加控件通知处理程序代码
	if(((CButton*)GetDlgItem(IDC_CHECK_INDEX))->GetCheck() == BST_CHECKED)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK_TAG))->GetCheck() == BST_UNCHECKED)
			((CButton*)GetDlgItem(IDC_CHECK_TAG))->SetCheck(BST_CHECKED);
	}
	m_TypeText = _T("");
	CatTypeString();
}


void CMyCatchHtmlElementClass::OnBnClickedCheckName()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TypeText = _T("");
	CatTypeString();
}


void CMyCatchHtmlElementClass::OnBnClickedCheckTag()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TypeText = _T("");
	if(((CButton*)GetDlgItem(IDC_CHECK_TAG))->GetCheck() == BST_UNCHECKED)
	{
		((CButton*)GetDlgItem(IDC_CHECK_INDEX))->SetCheck(BST_UNCHECKED);
	}
	CatTypeString();
}


void CMyCatchHtmlElementClass::OnBnClickedCheckTxt()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TypeText = _T("");
	CatTypeString();
}


void CMyCatchHtmlElementClass::OnBnClickedCheckType()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TypeText = _T("");
	CatTypeString();
}


void CMyCatchHtmlElementClass::OnBnClickedCheckValue()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TypeText = _T("");
	CatTypeString();
}

void CMyCatchHtmlElementClass::ClearAllState()
{
	((CButton*)GetDlgItem(IDC_CHECK_TAG))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_ID))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_NAME))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_TYPE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_VALUE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_INDEX))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_CLASS))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_TXT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_FRAME))->EnableWindow(FALSE);

	((CButton*)GetDlgItem(IDC_CHECK_TAG))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_ID))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_NAME))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_TYPE))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_VALUE))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_INDEX))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_CLASS))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_TXT))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_FRAME))->SetCheck(BST_UNCHECKED);

	SetDlgItemTextW(IDC_EDIT_TYPESTRING,_T(""));
	CString strAtt = _T("");
	this->SetDlgItemTextW(IDC_EDIT_TAG,strAtt);  // 设置tag内容
	this->SetDlgItemTextW(IDC_EDIT_ID,strAtt);  // 设置id内容
	this->SetDlgItemTextW(IDC_EDIT1_TXT,strAtt);  // 设置txt内容
	this->SetDlgItemTextW(IDC_EDIT_NAME,strAtt);  // 设置name内容
	this->SetDlgItemTextW(IDC_EDIT_TYPE,strAtt);  // 设置type内容
	this->SetDlgItemTextW(IDC_EDIT_VALUE,strAtt);  // 设置value内容
	this->SetDlgItemTextW(IDC_EDIT_INDEX,strAtt);  // 设置index内容
	this->SetDlgItemTextW(IDC_EDIT_FRAME,strAtt);  // 设置frame内容
	this->SetDlgItemTextW(IDC_EDIT_CLASS,strAtt);  // 设置class内容
	this->GetDlgItem(IDC_EDIT_TITLE)->SetWindowText(strAtt);
}


