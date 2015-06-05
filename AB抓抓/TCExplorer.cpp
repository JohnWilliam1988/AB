// TCExplorer.cpp : 实现文件
//
#include "stdafx.h"
#include "TCExplorer.h"

CTCExplorer::CTCExplorer()
{
	m_FramesIndex = -1;
}

CTCExplorer::~CTCExplorer()
{
}

///通过窗口名获取Dom对象
IWebBrowser2* CTCExplorer::GetDomFromWndHandleEx(HWND hwnd)
{
	CoInitialize( NULL );
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
	CoUninitialize();
	return pWebbrowser;
}

IWebBrowser2* CTCExplorer::EnumWindowFramesEx(IWebBrowser2* pBrowserInput,int framesNum)
{
	LPDISPATCH lpDisp = NULL;
	pBrowserInput->get_Document(&lpDisp);
	IWebBrowser2* pBrowserFrame=NULL;
	if (lpDisp)
	{
		IOleContainer* pContainer;
		// Get the container
		HRESULT hr = lpDisp->QueryInterface(IID_IOleContainer,(void**)&pContainer);
		lpDisp->Release();
		if (FAILED(hr))
			return NULL;

		IEnumUnknown* pEnumerator;
		// Get an enumerator for the frames
		hr = pContainer->EnumObjects(OLECONTF_EMBEDDINGS, &pEnumerator);
		pContainer->Release();
		if (FAILED(hr))
			return NULL;

		IUnknown* pUnk;
		ULONG uFetched;
		// Enumerate and refresh all the frames
		int helpIndex=0;
		for (UINT i = 0; S_OK == pEnumerator->Next(1, &pUnk, &uFetched); i++)
		{
			m_FramesIndex ++;
			//IWebBrowser2* pBrowser;
			hr = pUnk->QueryInterface(IID_IWebBrowser2,(void**)&pBrowserFrame);
			pUnk->Release();
			if (SUCCEEDED(hr))
			{
				if(m_FramesIndex == framesNum)
				{
					return pBrowserFrame;
				}
				pBrowserFrame = EnumWindowFramesEx(pBrowserFrame,framesNum);
				if(m_FramesIndex == framesNum)
				{
					return pBrowserFrame;
				}
				pBrowserFrame->Release();
			}
		}
		pEnumerator->Release();
	}
	return pBrowserInput;
}

//获取网页元素的功能
int CTCExplorer::HtmlGetData(CString subData,int hwnd)
{
	int findAccout = 0;
	CString subIDStr=L"",subNameStr=L"",subTagStr=L"",subTypeStr=L"",subValueStr=L"",subClassStr=L"",subIndexStr=L"",subTextStr=L"",subFrameStr=L"";

	int i_subCharacterNum = 0, i_indexNum = 0;
	int idPos = subData.Find(L"id:");
	int namePos = subData.Find(L"name:");
	int tagPos = subData.Find(L"tag:");
	int typePos = subData.Find(L"type:");
	int valuePos = subData.Find(L"value:");
	int indexPos = subData.Find(L"index:");
	int classPos = subData.Find(L"class:");
	int textPos = subData.Find(L"txt:");
	int framePos=  subData.Find(L"frame:");
	///////////// 非下面的特征字段直接返回 ///////////
	if(idPos==-1&&namePos==-1&&tagPos==-1&&typePos==-1&&valuePos==-1&&indexPos==-1&&classPos==-1&&textPos==-1&&framePos==-1)
	{
		////////实际操作中这里应该要返回false才行////////
		return findAccout;
	}

	if(idPos != -1)
	{
		subIDStr = subData.Right(subData.GetLength() - idPos - 3);
		if(subIDStr.Find(L"&") != -1)
		{
			subIDStr = subIDStr.Left(subIDStr.Find(L"&"));
		}
		i_subCharacterNum++;
	}
	if(namePos != -1)
	{
		subNameStr = subData.Right(subData.GetLength() - namePos - 5);
		if(subNameStr.Find(L"&") != -1)
		{
			subNameStr = subNameStr.Left(subNameStr.Find(L"&"));
		}
		i_subCharacterNum++;
	}
	if(tagPos != -1)
	{
		subTagStr = subData.Right(subData.GetLength() - tagPos - 4);
		if(subTagStr.Find(L"&") != -1)
		{
			subTagStr = subTagStr.Left(subTagStr.Find(L"&"));
		}
		i_subCharacterNum++;
	}
	if(classPos != -1)
	{
		subClassStr = subData.Right(subData.GetLength() - classPos - 6);
		if(subClassStr.Find(L"&") != -1)
		{
			subClassStr = subClassStr.Left(subClassStr.Find(L"&"));
		}
		i_subCharacterNum++;
	}
	if(typePos != -1)
	{
		subTypeStr = subData.Right(subData.GetLength() - typePos - 5);
		if(subTypeStr.Find(L"&") != -1)
		{
			subTypeStr = subTypeStr.Left(subTypeStr.Find(L"&"));
		}
		i_subCharacterNum++;
	}
	if(valuePos != -1)
	{
		subValueStr = subData.Right(subData.GetLength() - valuePos - 6);
		if(subValueStr.Find(L"&") != -1)
		{
			subValueStr = subValueStr.Left(subValueStr.Find(L"&"));
		}
		i_subCharacterNum++;
	}
	if(indexPos != -1)
	{
		subIndexStr = subData.Right(subData.GetLength() - indexPos - 6);
		if(subIndexStr.Find(L"&") != -1)
		{
			subIndexStr = subIndexStr.Left(subIndexStr.Find(L"&"));
		}
		i_subCharacterNum++;
	}
	if(textPos != -1)
	{
		subTextStr = subData.Right(subData.GetLength() - textPos - 4);
		if(subTextStr.Find(L"&") != -1)
		{
			subTextStr = subTextStr.Left(subTextStr.Find(L"&"));
		}
		i_subCharacterNum++;
	}
	if(framePos!=-1)
	{
		subFrameStr=subData.Right(subData.GetLength() - framePos - 6);
		if(subFrameStr.Find(L"&") != -1)
		{
			subFrameStr = subFrameStr.Left(subFrameStr.Find(L"&"));
		}
	}

	//////// 修剪数据前后的空格/////
	m_FramesIndex=-1;
	subIDStr.Trim();      
	subNameStr.Trim();
	subTagStr.Trim();
	subTypeStr.Trim();
	subValueStr.Trim();
	subClassStr.Trim();
	subIndexStr.Trim();
	subTextStr.Trim();
	subFrameStr.Trim();
	i_indexNum = ::_wtoi(subIndexStr);

	CString pRetStr = L""; 
	CString helpStr=L"";
	int pCharacterNum = 0;  /// 用于记录执行中的匹配特征计数器
	int index = -1;  //// 索引计数器
	HRESULT hr;

	CComQIPtr<IHTMLDocument2> pHTMLDoc;
	/////////////////frame测试代码////////////////////////
	CComQIPtr<IWebBrowser2> pBrowserFrame;
	pBrowserFrame = GetDomFromWndHandleEx((HWND)hwnd);
	if(pBrowserFrame == 0 )
		return findAccout;
	if(framePos!=-1)
	{
		int frameIndex=_wtoi(subFrameStr);
		IWebBrowser2* pWebBrowser = EnumWindowFramesEx(pBrowserFrame,frameIndex);
		IDispatch* pDoc;
		hr = pWebBrowser->get_Document(&pDoc);
		if ( FAILED( hr ) )
			return findAccout;
		hr = pDoc->QueryInterface(IID_IHTMLDocument2,(void**)&pHTMLDoc);
		if ( FAILED( hr ) )
			return findAccout;
		pDoc->Release();
	}
	else
	{
		IDispatch* pDoc;
		hr = pBrowserFrame->get_Document(&pDoc);
		if ( FAILED( hr ) )
			return findAccout;
		hr = pDoc->QueryInterface(IID_IHTMLDocument2,(void**)&pHTMLDoc);
		if ( FAILED( hr ) )
			return findAccout;
		pDoc->Release();
	}

	/////////////////frame测试代码////////////////////////
	CComQIPtr<IHTMLElementCollection> pElementColl;  //
	if(pHTMLDoc != NULL)
	{	
		if(SUCCEEDED(hr= pHTMLDoc->get_all(&pElementColl)))
		{
			long length = 0;
			if(SUCCEEDED(hr = pElementColl->get_length(&length)) && (length))
			{
				for(int x = 0; x < length; x++ )
				{
					CComQIPtr< IHTMLElement > pElement; //
					pCharacterNum = 0;
					CComBSTR pClassStr,pIdStr,pTagStr,pNameStr,pTypeStr,pValueStr,pTextStr;
					VARIANT	Index;
					IDispatch*	pDisp2	= NULL;
					Index.vt =	VT_UINT;
					Index.lVal	= x;
					VARIANT	var2;
					VariantInit( &var2 );
					if(SUCCEEDED(hr = pElementColl->item (Index, var2, &pDisp2)))
					{
						if(pDisp2&&SUCCEEDED(pDisp2->QueryInterface(IID_IHTMLElement,(void**)&pElement)))
						{
							VARIANT rv;
							if(tagPos != -1)
							{
								hr = pElement->get_tagName(&pTagStr);
								if(pTagStr.Length() == 0) continue;
								/// 特征符合就对特征计数器进行累加
								helpStr.Format(L"%s",pTagStr);
								helpStr.Trim();
								if(subTagStr.CompareNoCase(helpStr) == 0) pCharacterNum++;
								else  continue;
								index++;
							}
							if(idPos != -1)
							{
								hr = pElement->get_id(&pIdStr);
								if(pIdStr.Length() == 0)  continue;
								/// 特征符合就对特征计数器进行累加
								helpStr.Format(L"%s",pIdStr);
								helpStr.Trim();
								if(subIDStr.CompareNoCase(helpStr) == 0) pCharacterNum++;
								else 
									continue;
							}
							if(namePos != -1)
							{
								CString strAtt=_T("name");
								pElement->getAttribute(strAtt.AllocSysString(),0,&rv);
								pNameStr = rv.bstrVal;
								if(pNameStr.Length() == 0) continue;
								/// 特征符合就对特征计数器进行累加
								helpStr.Format(L"%s",pNameStr);
								helpStr.Trim();
								if(subNameStr.CompareNoCase(helpStr) == 0) pCharacterNum++;
								else 
									continue;
							}
							if(classPos != -1)
							{
								hr = pElement->get_className(&pClassStr);
								if(pClassStr.Length() == 0) continue;
								/// 特征符合就对特征计数器进行累加
								helpStr.Format(L"%s",pClassStr);
								helpStr.Trim();
								if(subClassStr.CompareNoCase(helpStr) == 0) pCharacterNum++;
								else 
									continue;
							}
							if(typePos != -1)
							{
								CString strAtt=_T("type");
								pElement->getAttribute(strAtt.AllocSysString(),0,&rv);
								pTypeStr = rv.bstrVal;
								if(pTypeStr.Length() == 0) continue;
								/// 特征符合就对特征计数器进行累加
								helpStr.Format(L"%s",pTypeStr);
								helpStr.Trim();
								if(subTypeStr.CompareNoCase(helpStr) == 0) pCharacterNum++;
								else 
									continue;
							}
							if(valuePos != -1)
							{
								CString strAtt=_T("value");
								pElement->getAttribute(strAtt.AllocSysString(),0,&rv);
								pValueStr = rv.bstrVal;
								if(pValueStr.Length() == 0) continue;
								/// 特征符合就对特征计数器进行累加
								helpStr.Format(L"%s",pValueStr);
								helpStr.Trim();
								if(subValueStr.CompareNoCase(helpStr) == 0) pCharacterNum++;
								else 
									continue;
							}
							if(textPos != -1)
							{
								hr = pElement->get_outerText(&pTextStr);
								if(pTextStr.Length() == 0) continue;
								/// 特征符合就对特征计数器进行累加									
								helpStr.Format(L"%s",pTextStr);
								helpStr.Trim();
								if(subTextStr.CompareNoCase(helpStr) == 0) pCharacterNum++;
								else 
									continue;
							}
							if(indexPos != -1) pCharacterNum++;

							if(pCharacterNum == i_subCharacterNum)
							{
								if(indexPos == -1)      // 不存在索引的情况下
								{
									findAccout ++;							
								}
								// 存在索引的情况下
								else
								{
									if(i_indexNum == index)  // 索引计数器的值 与 用户提供的索引值相等
									{
										findAccout++;								
									}
								}
							}
						}
					}
				}
			}
			pElementColl.Release();
		}
		pHTMLDoc.Release();
	}
	return findAccout;
}
