// MyDrawPictureClass.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyDrawPictureClass.h"
#include "afxdialogex.h"

#include "MyAutoBuiltCodeClass.h"
#include "MyFindPictureClass.h"

extern	 HWND		g_MainFormHwnd;
extern	 CString	g_CurrentExePath;
// CMyDrawPictureClass 对话框

IMPLEMENT_DYNAMIC(CMyDrawPictureClass, CMFCPropertyPage)

CMyDrawPictureClass::CMyDrawPictureClass(CWnd* pParent /*= NUL*/)
	: CMFCPropertyPage(CMyDrawPictureClass::IDD)
{
	m_IsPicLoaded = false;
	m_LowColor = 0;
	m_ForegroundColor = 0;

	m_SavePicPath = _T("");
}

CMyDrawPictureClass::~CMyDrawPictureClass()
{
	::ReleaseDC(NULL,m_Hdc);
}

void CMyDrawPictureClass::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SOURCEPIC, m_SourcePic);
	DDX_Control(pDX, IDC_STATIC_TARGETPIC, m_TargetPic);
	DDX_Control(pDX, IDC_STATIC_BASECOLOR1, m_BaseColor1);
	DDX_Control(pDX, IDC_STATIC_LOADSOURCEPIC, m_LoadSourcePic);
	DDX_Control(pDX, IDC_STATIC_PROCESSTARGETPIC, m_ProTargetPic);
	DDX_Control(pDX, IDC_STATIC_DOWNCOLOR, m_DownColor);
	DDX_Control(pDX, IDC_STATIC_DRAWTIP, m_DrawTipText);
	DDX_Control(pDX, IDC_BUTTON_LOADBMP, m_btLoadBmpCtrl);
	DDX_Control(pDX, IDC_BUTTON_SAVEPIC, m_btSaveBmpCtrl);
	DDX_Control(pDX, IDC_BUTTON_EDITPIC, m_btEditBmpCtrl);
	DDX_Control(pDX, IDC_STATIC_TESTLOG, m_TestFindpicLog);
}


BEGIN_MESSAGE_MAP(CMyDrawPictureClass, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_LOADBMP, &CMyDrawPictureClass::OnBnClickedButtonLoadbmp)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STATIC_DOWNCOLOR, &CMyDrawPictureClass::OnStnClickedStaticDowncolor)
//	ON_STN_CLICKED(IDC_STATIC_BASECOLOR1, &CMyDrawPictureClass::OnStnClickedStaticBasecolor1)
//	ON_WM_LBUTTONUP()
ON_WM_SETCURSOR()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_BUTTON_SAVEPIC, &CMyDrawPictureClass::OnBnClickedButtonSavepic)
ON_BN_CLICKED(IDC_BUTTON_CHANGEOFFSETCOLOR, &CMyDrawPictureClass::OnBnClickedButtonChangeoffsetcolor)
ON_BN_CLICKED(IDC_BUTTON_EDITPIC, &CMyDrawPictureClass::OnBnClickedButtonEditpic)
//ON_WM_CLOSE()
ON_BN_CLICKED(IDC_BTN_TESTPIC, &CMyDrawPictureClass::OnBnClickedBtnTestpic)
ON_BN_CLICKED(IDC_BTN_BUILTCODE, &CMyDrawPictureClass::OnBnClickedBtnBuiltcode)
END_MESSAGE_MAP()


// CMyDrawPictureClass 消息处理程序


BOOL CMyDrawPictureClass::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	::SetWindowPos(this->m_hWnd,HWND_TOPMOST,300,0,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);

	// TODO:  在此添加额外的初始化
	/*CRect rect;
	((CButton*)this->GetDlgItem(IDC_BUTTON_LOADBMP))->GetWindowRect(&rect);

	CRect rt;
	m_SourcePic.GetClientRect(&rt);
	m_SourcePic.MoveWindow(rt.left+5,rt.top+5,rect.left-15,rect.bottom+20);
*/
	//CRect rt2;
	//int width = rect.left-30 - rt.left;
	////m_TargetPic.GetClientRect(&rt2);
	//m_TargetPic.MoveWindow(rect.right+10,rt.top+5,width,rect.bottom+20);
	//m_SourcePic.SetBkColor(0);
	//m_TargetPic.SetBkColor(0);
	m_BaseColor1.SetBkColor(0);
	this->GetDlgItem(IDC_EDIT_COLOR1)->SetWindowTextW(_T("000000"));

	m_DownColor.SetBkColor(0);
	this->GetDlgItem(IDC_EDIT_DOWNCOLOR1)->SetWindowTextW(_T("000000"));

	this->GetDlgItem(IDC_EDIT_OffsetColor1)->SetWindowTextW(_T("000000"));

	//m_LoadSourcePic.SetBkColor(0);
	/*m_ProTargetPic.SetBkColor(0);*/
	m_Hbitmap = NULL;

	m_IsMakePic = false;

	m_Hdc = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	m_hMemDC = CreateCompatibleDC(m_Hdc);

	///////加载处理时的鼠标资源
	m_CurrentSursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);

	//this->SetBackgroundColor(0xf5e7dd);
	m_DrawTipText.SetTextColor(RGB(6,121,50));
	m_TestFindpicLog.SetTextColor(RGB(6,121,50));

	// 背景色  EEF3F4
	m_DrawTipText.SetBkColor(0xEEF3F4);
	m_TestFindpicLog.SetBkColor(0xEEF3F4);
	////////////////////按钮的鼠标提示/////////////////////////////
	m_btLoadBmpCtrl.SetTooltip(_T("加载指定路径的图片来制作透明图!"));
	m_btSaveBmpCtrl.SetTooltip(_T("保存制作好的透明图!"));
	m_btEditBmpCtrl.SetTooltip(_T("使用系统画板工具编辑制作的透明图!"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMyDrawPictureClass::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//if (!m_SourceImgOriginal.IsNull()) 
	//{
	//	CRect rctWindowSize;
	//	m_LoadSourcePic.GetWindowRect(rctWindowSize);
	//	//GetDlgItem(IDC_STATIC_SOURCE)->GetWindowRect(&rctWindowSize);
	//	//GetDlgItem(IDC_STATIC_SOURCE)->GetClientRect(&rctWindowSize);
	//	CPoint point(rctWindowSize.left,rctWindowSize.top);
	//	::ScreenToClient(m_hWnd,&point);
	//	m_SourceImgOriginal.StretchBlt(dc.GetSafeHdc(),point.x,point.y,rctWindowSize.Width(),rctWindowSize.Height(),0,0,rctWindowSize.Width(),rctWindowSize.Height(),SRCCOPY);
	//	if(rctWindowSize.Width()<=m_SourceImgOriginal.GetWidth())
	//		m_Width = rctWindowSize.Width();
	//	else
	//		m_Width = m_SourceImgOriginal.GetWidth();

	//	if(rctWindowSize.Height()<=m_SourceImgOriginal.GetHeight())
	//		m_Height = rctWindowSize.Height();
	//	else
	//		m_Height = m_SourceImgOriginal.GetHeight();
	//}

	if(m_IsPicLoaded)
	{
		CRect rctWindowSize;
		m_LoadSourcePic.GetWindowRect(rctWindowSize);
		////// 获得位图和显示位图的区域大小
		/*BITMAP bitm;
		::GetObjectW(m_Hbitmap,sizeof(BITMAP),&bitm);
		if(rctWindowSize.Width()<=bitm.bmWidth)
			m_Width = rctWindowSize.Width();
		else
			m_Width = bitm.bmWidth;
		if(rctWindowSize.Height()<=bitm.bmHeight)
			m_Height = rctWindowSize.Height();
		else
			m_Height = bitm.bmHeight;*/

		CPoint point(rctWindowSize.left,rctWindowSize.top);
		::ScreenToClient(m_hWnd,&point);
		/*CBitmap cbt;
		cbt.Attach(m_Hbitmap);*/
		////绘图
		SelectObject(m_hMemDC,m_Hbitmap);
		StretchBlt(dc.GetSafeHdc(),point.x,point.y,rctWindowSize.Width(),rctWindowSize.Height(),m_hMemDC,0,0,rctWindowSize.Width(),rctWindowSize.Height(),SRCCOPY);
		
	}
}

void CMyDrawPictureClass::OnBnClickedButtonLoadbmp()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR OldPath[MAX_PATH]={0};
	::GetCurrentDirectoryW(MAX_PATH,OldPath);

	CFileDialog fOpenDLG(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("BMP位图(*.bmp)|*bmp||"));

	if(fOpenDLG.DoModal()==IDOK)
	{
		m_Hbitmap = (HBITMAP)LoadImage( AfxGetInstanceHandle(),fOpenDLG.GetPathName(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
		if(m_Hbitmap==NULL)
		{
			return ;
		}
	}

	///////设置回原来的路径/////////////
	::SetCurrentDirectoryW(OldPath);

	CRect rctWindowSize;
	m_LoadSourcePic.GetWindowRect(rctWindowSize);
	////// 获得位图和显示位图的区域大小
	BITMAP bitm;
	::GetObjectW(m_Hbitmap,sizeof(BITMAP),&bitm);
	if(rctWindowSize.Width()<=bitm.bmWidth)
		m_Width = rctWindowSize.Width();
	else
		m_Width = bitm.bmWidth;
	if(rctWindowSize.Height()<=bitm.bmHeight)
		m_Height = rctWindowSize.Height();
	else
		m_Height = bitm.bmHeight;

	
	/*HBITMAP hBitmap = ::CreateCompatibleBitmap(m_Hdc,m_Width,this->m_Height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(m_hMemDC,hBitmap);
	BitBlt(hMemDC, 0, 0, m_Width,m_Height,hScrDC, rctWindowSize.left, rctWindowSize.top, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemDC,hOldBitmap);*/

	/*CString strFilter;
	CSimpleArray<GUID> aguidFileTypes;
	HRESULT hResult;

	hResult = m_SourceImgOriginal.GetExporterFilterString(strFilter,aguidFileTypes);
	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format(_T("GetExporterFilter failed:\n%x - %s"), hResult, _com_error(hResult).ErrorMessage());
		::AfxMessageBox(fmt);
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	dlg.m_ofn.nFilterIndex = m_nFilterLoad;
	hResult = (int)dlg.DoModal();
	if(FAILED(hResult)) {
		return;
	}

	m_nFilterLoad = dlg.m_ofn.nFilterIndex;
	m_SourceImgOriginal.Destroy();
	hResult = m_SourceImgOriginal.Load(dlg.GetFileName());
	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format(_T("Load image failed:\n%x - %s"), hResult, _com_error(hResult).ErrorMessage());
		::AfxMessageBox(fmt);
		return;
	}*/

	m_IsPicLoaded = true;
	Invalidate();
	UpdateWindow();
}

void	CMyDrawPictureClass::Loadbmp(CString path)
{
	/*CString strFilter;
	CSimpleArray<GUID> aguidFileTypes;
	HRESULT hResult;

	hResult = m_SourceImgOriginal.GetExporterFilterString(strFilter,aguidFileTypes);
	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format(_T("GetExporterFilter failed:\n%x - %s"), hResult, _com_error(hResult).ErrorMessage());
		::AfxMessageBox(fmt);
		return;
	}

	m_SourceImgOriginal.Destroy();
	hResult = m_SourceImgOriginal.Load(path);
	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format(_T("Load image failed:\n%x - %s"), hResult, _com_error(hResult).ErrorMessage());
		::AfxMessageBox(fmt);
		return;
	}*/

	/*CFileDialog fOpenDLG(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("BMP位图(*.bmp)|*bmp||"));

	if(fOpenDLG.DoModal()==IDOK)
	{
		m_Hbitmap = (HBITMAP)LoadImage( AfxGetInstanceHandle(),fOpenDLG.GetPathName(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
		if(m_Hbitmap==NULL)
		{
			return ;
		}
	}*/
	m_Hbitmap = (HBITMAP)LoadImage( AfxGetInstanceHandle(),path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	if(m_Hbitmap==NULL)
	{
		return ;
	}

	CRect rctWindowSize;
	m_LoadSourcePic.GetWindowRect(rctWindowSize);
	////// 获得位图和显示位图的区域大小
	BITMAP bitm;
	::GetObjectW(m_Hbitmap,sizeof(BITMAP),&bitm);
	if(rctWindowSize.Width()<=bitm.bmWidth)
		m_Width = rctWindowSize.Width();
	else
		m_Width = bitm.bmWidth;
	if(rctWindowSize.Height()<=bitm.bmHeight)
		m_Height = rctWindowSize.Height();
	else
		m_Height = bitm.bmHeight;

	m_IsPicLoaded = true;

	Invalidate();
	UpdateWindow();
}

void CMyDrawPictureClass::drawPicture()
{	
	this->UpdateData();
	CString offsetColorStr=_T("0");
	DWORD lowColor=0;
	this->GetDlgItem(IDC_EDIT_OffsetColor1)->GetWindowTextW(offsetColorStr);
	lowColor = ::wcstol(offsetColorStr,0,16);
	BYTE offr,offg,offb;
	offr = GetRValue(lowColor);
	offg = GetGValue(lowColor);
	offb = GetBValue(lowColor);


	CRect rctWindowSize,rctTargetPic;
	m_LoadSourcePic.GetWindowRect(rctWindowSize);

	this->GetDlgItem(IDC_STATIC_TARGET)->GetWindowRect(&rctTargetPic);

	//CClientDC cDC(this);
	HDC hScrDC,hMemDC;
	////为屏幕创建设备描述表
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	//////////////////创建一个原图大小的位图//////////////////////
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hScrDC,m_Width,this->m_Height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap);
	BitBlt(hMemDC, 0, 0, m_Width,m_Height,hScrDC, rctWindowSize.left, rctWindowSize.top, CAPTUREBLT|SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemDC,hOldBitmap);

	// 24位图的BITMAPINFO
    BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
    memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
    BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
    pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
    pInfo_Header->biWidth = m_Width;   
    pInfo_Header->biHeight = m_Height;   
    pInfo_Header->biPlanes = 1;   
    pInfo_Header->biBitCount = 24;   
    pInfo_Header->biCompression = BI_RGB;
	
	 // 获得数据buf
    DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
    BYTE * pBuffer = new BYTE[bufSize];

	int aHeight=pInfo_Header->biHeight;

    if(::GetDIBits(hMemDC, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
    {
       return ;
    }

	BYTE fr,fg,fb,lr,lg,lb;
	fr = GetRValue(m_ForegroundColor);
	fg = GetGValue(m_ForegroundColor);
	fb = GetBValue(m_ForegroundColor);

	lr = GetRValue(m_LowColor);
	lg = GetGValue(m_LowColor);
	lb = GetBValue(m_LowColor);

	int pitch=m_Width%4;
	for(int i=0;i<m_Height;i++)
	{
		int realPitch=i*pitch;
		for(int j=0;j<m_Width;j++)
		{
			UCHAR b=pBuffer[(i*m_Width+j)*3+realPitch];
			UCHAR g=pBuffer[(i*m_Width+j)*3+1+realPitch];
			UCHAR r=pBuffer[(i*m_Width+j)*3+2+realPitch];
			//helpcolor=RGB(r,g,b);
			if(abs(r-fr)<=offr&&abs(g-fg)<=offg&&abs(b-fb)<=offb)
			{
				continue;
			}
			else
			{
				pBuffer[(i*m_Width+j)*3+realPitch] = lb;
				pBuffer[(i*m_Width+j)*3+1+realPitch] = lg;
				pBuffer[(i*m_Width+j)*3+2+realPitch] = lr;
			}

		}
	}


	//保存到文件并创建位图结构
	BITMAPFILEHEADER bmfh;
	ZeroMemory(&bmfh,sizeof(BITMAPFILEHEADER));

	*((char*)&bmfh.bfType) = 'B';
	*(((char*)&bmfh.bfType) + 1) = 'M';

	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + (m_Width * m_Height) * pInfo_Header->biBitCount / 8;
	CFile file;
	if(file.Open(g_CurrentExePath+_T("TCTEMP.bmp"),CFile::modeWrite|CFile::modeCreate))
	{
		file.Write(&bmfh,sizeof(BITMAPFILEHEADER));
		file.Write(&(pBITMAPINFO->bmiHeader),sizeof(BITMAPINFOHEADER));
		file.Write(pBuffer,bufSize);
		file.Close();
	}

	//HBITMAP hBitmapTTT = (HBITMAP)LoadImage( AfxGetInstanceHandle(),_T("TCTEMP.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	HBITMAP hBitmapTTT = (HBITMAP)LoadImage( NULL,g_CurrentExePath+_T("TCTEMP.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	if(hBitmapTTT==NULL)
	{
		//::AfxMessageBox(_T("加载位图资源失败！"));
		return ;
	}
	m_TargetPic.SetBitmap(hBitmapTTT);
	//helpBMP =(HBITMAP)SelectObject(hMemDC,m_Hbitmap);
	//helpBMP =(HBITMAP)SelectObject(cDC.GetSafeHdc(),m_Hbitmap);
	//CRect rt;
	//m_LoadSourcePic.GetClientRect(&rt);
	//m_SourcePic.GetClientRect(&rt);

	//int width = rt.right-rt.left;
	//int height = rt.bottom-rt.top;	
	//StretchBlt(cDC.GetSafeHdc(),rt.left+8,rt.top+8,width,height,hMemDC,0,0,width,height,SRCCOPY);
	//::BitBlt(cDC.GetSafeHdc(),rt.left+8,rt.top+8,width,height,hMemDC,0,0,SRCCOPY);

	//::StretchBlt(hMemDC,rt.left+8,rt.top+8,width,height,cDC.GetSafeHdc(),0,0,width,height,SRCCOPY);

	//SelectObject(hMemDC,helpBMP);
	//m_SourcePic.SetBitmap(helpBMP);

	delete [] pBuffer;
	::DeleteDC(hMemDC);
	::DeleteDC(hScrDC);

	TCHAR currentPath[MAX_PATH]={0};
	::GetCurrentDirectoryW(MAX_PATH,currentPath);
	m_SavePicPath.Format(_T("%s\\TCTEMP.bmp"),g_CurrentExePath);
	return ;
}

void CMyDrawPictureClass::ChangePicColor(HBITMAP bitmap)
{

}


/////////////////////////////////选择底色/////////////////////////////////////
void CMyDrawPictureClass::OnStnClickedStaticDowncolor()
{
	// TODO: 在此添加控件通知处理程序代码
	////  设置底色
	CString wndColor=_T("000000");
	this->GetDlgItem(IDC_EDIT_DOWNCOLOR1)->GetWindowTextW(wndColor);
	COLORREF color;
	color = (COLORREF)::wcstol(wndColor,0,16);
	CColorDialog colorDlg(color,CC_FULLOPEN);

	if(colorDlg.DoModal() ==IDOK)
	{
		color = colorDlg.GetColor();
		wndColor.Format(_T("%06X"),color);
		m_DownColor.SetBkColor(color);
		//wndColor.MakeUpper();
		this->GetDlgItem(IDC_EDIT_DOWNCOLOR1)->SetWindowTextW(wndColor);
		////////设置后台色///////////////////
		m_LowColor = color;
	}
}


//void CMyDrawPictureClass::OnStnClickedStaticBasecolor1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	if(!m_IsMakePic)
//	{
//		m_OldSursor = ::GetCursor();
//		::SetCursor(m_CurrentSursor);
//		m_IsMakePic = true;
//	}
//}


//void CMyDrawPictureClass::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	if(m_IsMakePic)
//	{
//		::SetCursor(m_OldSursor);
//		m_IsMakePic = false;
//
//		COLORREF color;
//		color = ::GetPixel(NULL,point.x,point.y);
//		CString wndColor=_T("0");
//		wndColor.Format(_T("%x"),color);
//		m_BaseColor1.SetBkColor(color);
//		wndColor.MakeUpper();
//		this->GetDlgItem(IDC_EDIT_COLOR1)->SetWindowTextW(wndColor);
//	}
//	CDialogEx::OnLButtonUp(nFlags, point);
//}


BOOL CMyDrawPictureClass::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_LBUTTONDOWN&&m_IsPicLoaded)
	{
		CWnd * hwnd;
		POINT pointGetCtl;
		GetCursorPos(&pointGetCtl);
		hwnd= (CWnd *)WindowFromPoint(pointGetCtl);
		while (hwnd && hwnd->GetParent()!=this)
			hwnd = hwnd->GetParent();
		if(GetDlgItem(IDC_STATIC_BASECOLOR1)==hwnd)
		{
			if(!m_IsMakePic)
			{
				m_OldSursor = ::GetCursor();
				m_IsMakePic= true;
			}
			
		}
		else
		{

			if(m_IsMakePic)
			{
				::SetCursor(m_OldSursor);
				m_IsMakePic = false;

				COLORREF color;
				color = ::GetPixel(::GetDC(NULL),pMsg->pt.x,pMsg->pt.y);
				CString wndColor=_T("0");
				wndColor.Format(_T("%x"),color);
				m_BaseColor1.SetBkColor(color);
				wndColor.MakeUpper();
				this->GetDlgItem(IDC_EDIT_COLOR1)->SetWindowTextW(wndColor);

				////////设置前台色///////////////////
				m_ForegroundColor = color;

				m_IsPicLoaded = true;
				
				drawPicture();
			}
		}
	}

	return CMFCPropertyPage::PreTranslateMessage(pMsg);
}


BOOL CMyDrawPictureClass::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_IsMakePic)
	{
		::SetCursor(m_CurrentSursor);
		return TRUE;
	}

	return CMFCPropertyPage::OnSetCursor(pWnd, nHitTest, message);
}


void CMyDrawPictureClass::OnDestroy()
{
	//CMFCPropertyPage::OnDestroy();
	::DeleteFileW(m_SavePicPath);
	// TODO: 在此处添加消息处理程序代码
}


void CMyDrawPictureClass::OnBnClickedButtonSavepic()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR OldPath[MAX_PATH]={0};
	::GetCurrentDirectoryW(MAX_PATH,OldPath);

	CFileDialog saveDLG(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("BMP位图(*.bmp)|*bmp||"));
	saveDLG.m_ofn.lpstrDefExt = _T("bmp");
	if(saveDLG.DoModal() == IDOK)
	{
		//::CopyFile(m_SavePicPath,saveDLG.GetFileName(),FALSE );
		// 修改在win7下，CFileDialog 不会设置当前路径的问题，导致图片不能保存到指定目录。
		// 下面获取全路径，解决这一问题。
		::CopyFile(m_SavePicPath,saveDLG.GetPathName(),FALSE );
	}

	::SetCurrentDirectoryW(OldPath);
}


void CMyDrawPictureClass::OnBnClickedButtonChangeoffsetcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	drawPicture();
}


void CMyDrawPictureClass::OnBnClickedButtonEditpic()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_SavePicPath.IsEmpty())
	{
		::AfxMessageBox(_T("请先进行透明图处理操作!"));
		return;
	}

	wchar_t pathw[MAX_PATH] = {0};
	//::GetSystemDirectoryW(pathw,MAX_PATH);
	::GetCurrentDirectoryW(MAX_PATH,pathw);

	CString pathName=_T("");
	CString PicPath=m_SavePicPath;
	while(true)
	{
		int pos = PicPath.Find(_T("\\"));
		if(pos == -1)
			break;
		pathName +=PicPath.Left(pos+1);
		PicPath = PicPath.Right(PicPath.GetLength()-pos-1);
	}

	::SetCurrentDirectoryW(pathName);

	char path[MAX_PATH]={0};
	USES_CONVERSION;
	::strcat(path,"mspaint.exe ");
	::strcat(path,W2A(PicPath.LockBuffer()));
	::WinExec(path,SW_SHOWNORMAL);
	/////// 还原路径 //////////////
	::SetCurrentDirectoryW(pathw);
}


//void CMyDrawPictureClass::OnClose()
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	::SendMessage(g_MainFormHwnd,IDC_USER_CLOSEMAKEPICWND,0,0);
//	CDialogEx::OnClose();
//}






void CMyDrawPictureClass::OnBnClickedBtnTestpic()
{
	// TODO: 在此添加控件通知处理程序代码
	CString offsetColorStr=_T("0");
	DWORD lowColor=0;
	this->GetDlgItem(IDC_EDIT_OffsetColor1)->GetWindowTextW(offsetColorStr);
	lowColor = ::wcstol(offsetColorStr,0,16);

	MyFindPictureClass findPic;
	int x = -1,y = -1;
	TCHAR path[MAX_PATH] = {0};
	::wsprintfW(path,_T("%stctemp.bmp"),g_CurrentExePath);
	findPic.findPicture(NULL,0,0,2000,2000,path,lowColor,0.8,0,x,y);
	if(x>=0)
	{
		CString pointStr;
		pointStr.Format(_T("找到图片，左上角坐标为：X=%d ,Y=%d"),x,y);
		m_TestFindpicLog.SetWindowTextW(pointStr);
	}
	else
	{
		CString pointStr;
		pointStr.Format(_T("找不到图片！请检查图片是否存在问题！"));
		m_TestFindpicLog.SetWindowTextW(pointStr);
	}
	//::mouse_event(MOUSEEVENTF_MOVE ,x,y,0,NULL);
	return ;
	//////测试智能修剪处理后的透明图。。去掉周围多余的透明色。使之变小。。
	///////////////////////////加载的位图 //////////////////////////
	/*HBITMAP hbmp = (HBITMAP)LoadImage(NULL,_T("TCTEMP.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE );
	if(hbmp==NULL)
	{
		//::MessageBox(NULL,L"加载位图失败",L"TC",0);
		return ;
	}

	BITMAP bitmap;
	GetObject(hbmp, sizeof(BITMAP), &bitmap);

	BITMAPINFO info;
	HDC dc;
	dc=::CreateDC(L"DISPLAY",NULL,NULL,NULL);
	
	// 24位图的BITMAPINFO
	BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
	memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
	BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
	pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
	pInfo_Header->biWidth =bitmap.bmWidth;   
	pInfo_Header->biHeight = bitmap.bmHeight;   
	pInfo_Header->biPlanes = 1;   
	pInfo_Header->biBitCount = 24;   
	pInfo_Header->biCompression = BI_RGB;

	
	long width = bitmap.bmWidth;
	long height = bitmap.bmHeight;
	info.bmiHeader.biBitCount=24;


	DWORD bufSize = ( width * 3 + 3) / 4 * 4 * height;
	BYTE *buffer=new BYTE[bufSize];
	memset(buffer,0,sizeof(BYTE)*bufSize);
	if(!GetDIBits(dc, hbmp, 0, bitmap.bmHeight, buffer, pBITMAPINFO, DIB_RGB_COLORS))
	{
		::MessageBox(NULL,L"加载位图失败",L"TC",0);
		return ;
	}

	COLORREF** pLoadBmpBuffer = new COLORREF*[height];     ///// 二维数组 用来存储图像的颜色值
	for(int i=0;i<height;i++)
	{
		pLoadBmpBuffer[i]=new COLORREF[width];
	}
	COLORREF helpcolor=0,comparateColor=RGB(buffer[0],buffer[1],buffer[2]);
	int startx=0,starty=0,endx =0,endy=0;
	int pitch=width%4;
	for(int i=0;i<height;i++)
	{
		//bool isEqui = true;
		int realPitch=i*pitch;
		for(int j=0;j<width;j++)
		{
			UCHAR b=buffer[(i*width+j)*3+realPitch];
			UCHAR g=buffer[(i*width+j)*3+1+realPitch];
			UCHAR r=buffer[(i*width+j)*3+2+realPitch];
			helpcolor=RGB(r,g,b);

			pLoadBmpBuffer[height-i-1][j]=helpcolor;	
		}

	}
	bool isEqui = true;
	/// 先确定 starty的值
	for(int i=0;i<height;i++)
	{		
		for(int j=0;j<width;j++)
		{
			if(comparateColor != pLoadBmpBuffer[i][j])
			{
				isEqui = false;
				starty = i;
				break;
			}
		}
		if(!isEqui)  break;
	}
	isEqui = true;
	/// 再确定 startx的值
	for(int j=0;j<width;j++)
	{
		for(int i=height-1;i>=0;i--)
		{
			if(comparateColor != pLoadBmpBuffer[i][j])
			{
				isEqui = false;
				startx = j; 
				break;
			}
		}
		if(!isEqui)  break;
	}
	isEqui = true;
	/// 先确定 endx的值
	for(int j=width-1;j>=0;j--)
	{
		for(int i=0;i<height;i++)
		{
			if(comparateColor != pLoadBmpBuffer[i][j])
			{
				isEqui = false;
				endx = j;
				break;
			}
		}
		if(!isEqui)  break;
	}
	isEqui = true;
	/// 再确定 endy的值
	for(int i=height-1;i>=0;i--)
	{
		for(int j=width-1;j>=0;j--)
		{
			if(comparateColor != pLoadBmpBuffer[i][j])
			{
				isEqui = false;
				endy = i;
				break;
			}
		}
		if(!isEqui)  break;
	}

	////x 表示的width  y表示的height
	memset(buffer,0,sizeof(BYTE)*bufSize);
	int px=0,py=0;
	for(int i=startx; i<=endx; i++)
	{
		//for(int j=endy;j>=starty; j--)
		for(int j=starty;j<=endy; j++)
		{
			buffer[py] = GetBValue(pLoadBmpBuffer[j][i]);
			buffer[py+1] = GetGValue(pLoadBmpBuffer[j][i]);
			buffer[py+2] = GetRValue(pLoadBmpBuffer[j][i]);
			py = py + 4;			
		}
	}

	
	delete [] buffer;
	::DeleteDC(dc);
	::free(pBITMAPINFO);
	::DeleteObject(hbmp); */
}


void CMyDrawPictureClass::OnBnClickedBtnBuiltcode()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CMyAutoBuiltCodeClass autoBuiltDlg;
	CString str1=_T(""),str2=_T("");
	this->GetDlgItem(IDC_EDIT_COLOR1)->GetWindowTextW(str1);
	this->GetDlgItem(IDC_EDIT_OffsetColor1)->GetWindowTextW(str2);
	CString helpStr;
	helpStr.Format(_T(" int x,y\r\n color.findpic(0,0,1440,900,"d:\\111.bmp",#203040,0.8,0,x,y)"));
	autoBuiltDlg.DoModal();*/
}
