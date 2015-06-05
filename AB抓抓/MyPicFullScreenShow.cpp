// MyPicFullScreenShow.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyPicFullScreenShow.h"
#include "afxdialogex.h"

extern	HBITMAP				g_HbitMap;
extern	CMenu				g_MenuLeftMouseUp;
extern	CMenu				g_MenuRightMouseUp;
extern	bool				g_IsFullScreen;
//extern  CMyDrawPictureClass	g_DrawPicture;
extern  CButton				g_PicCheck;
extern	CMyPickerColor		g_PickColorDlg;
extern	 CString			g_CurrentExePath;
// CMyPicFullScreenShow 对话框

IMPLEMENT_DYNAMIC(CMyPicFullScreenShow, CDialogEx)

CMyPicFullScreenShow::CMyPicFullScreenShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyPicFullScreenShow::IDD, pParent)
{
	
}

CMyPicFullScreenShow::~CMyPicFullScreenShow()
{
}

void CMyPicFullScreenShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyPicFullScreenShow, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID__32787, &CMyPicFullScreenShow::OnRightClickFullScreen)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID__AB32773, &CMyPicFullScreenShow::OnLeftClickFullScreen)
	ON_COMMAND(ID__1, &CMyPicFullScreenShow::OnAddColor1)
	ON_COMMAND(ID__32778, &CMyPicFullScreenShow::OnAddColor2)
	ON_COMMAND(ID__32779, &CMyPicFullScreenShow::OnAddColor3)
	ON_COMMAND(ID__32780, &CMyPicFullScreenShow::OnAddColor4)
	ON_COMMAND(ID__32781, &CMyPicFullScreenShow::OnAddColor5)
	ON_COMMAND(ID__32782, &CMyPicFullScreenShow::OnAddColor6)
	ON_COMMAND(ID__32783, &CMyPicFullScreenShow::OnAddColor7)
	ON_COMMAND(ID__32784, &CMyPicFullScreenShow::OnAddColor8)
	ON_COMMAND(ID__32785, &CMyPicFullScreenShow::OnAddColor9)
	ON_COMMAND(ID__32786, &CMyPicFullScreenShow::OnAddColor10)
	ON_WM_PAINT()
	ON_COMMAND(ID__32771, &CMyPicFullScreenShow::OnClickLeftSaveBmp)
	ON_COMMAND(ID_32774, &CMyPicFullScreenShow::OnClickLeftCallSystemPicture)
	ON_COMMAND(ID_32775, &CMyPicFullScreenShow::OnClickLeftCallABmakePicture)
END_MESSAGE_MAP()


// CMyPicFullScreenShow 消息处理程序


BOOL CMyPicFullScreenShow::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*CBitmap *btm;
	btm=NULL;
	btm = CBitmap::FromHandle(g_HbitMap);
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	dcCompatible.SelectObject(btm);
	
	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);*/
	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CMyPicFullScreenShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_xScreen = ::GetSystemMetrics(SM_CXSCREEN);
	m_yScreen = ::GetSystemMetrics(SM_CYSCREEN);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void	CMyPicFullScreenShow::paintWindow()
{
	//把对化框设置成全屏顶层窗口
	SetWindowPos(&wndNoTopMost,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);
	if(g_HbitMap)
	{
		BITMAP bitmap;
		CBitmap *btm;
		btm=NULL;
		btm = CBitmap::FromHandle(g_HbitMap);	
		btm->GetBitmap(&bitmap);
		m_Width = bitmap.bmWidth;
		m_Height = bitmap.bmHeight;
		CClientDC pDC(this);
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(&pDC);
		dcCompatible.SelectObject(btm);

		CRect rect;
		GetClientRect(&rect);
		pDC.BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
	}
}

////// 退出
void	CMyPicFullScreenShow::exitWindow()
{
	this->OnOK();
}

HBITMAP CMyPicFullScreenShow::CopyRectToBitmap(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;      
	// 屏幕和内存设备描述表
	HBITMAP hBitmap,hOldBitmap;   
	// 位图句柄
	int       nX, nY, nX2, nY2;      
	// 选定区域坐标
	int       nWidth, nHeight;      
	// 位图宽度和高度
	int       xScrn, yScrn;         
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;

	//为屏幕创建设备描述表
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	// 获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, CAPTUREBLT|SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// 返回位图句柄
	return hBitmap;
}

BOOL CMyPicFullScreenShow::CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi)
{ 
	BITMAP bmp; 
	// Retrieve the bitmap color format, width, and height. 
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
	{
		return FALSE;
	}

	//int width = ::GetSystemMetrics(HORZRES);
	//int height = ::GetSystemMetrics(VERTRES);
	//if(2*width<bmp.bmWidth||2*height<bmp.bmHeight)
	//{
	//	//////表示保存的时候出现了异常。保存失败！！！！
	//	return false;
	//}

	pbmi = (PBITMAPINFO) LocalAlloc(LPTR,sizeof(BITMAPINFOHEADER)); 

	// Initialize the fields in the BITMAPINFO structure. 

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	pbmi->bmiHeader.biWidth = bmp.bmWidth; 
	pbmi->bmiHeader.biHeight = bmp.bmHeight; 
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
	pbmi->bmiHeader.biBitCount = /*bmp.bmBitsPixel*/24; 

	// If the bitmap is not compressed, set the BI_RGB flag. 
	pbmi->bmiHeader.biCompression = BI_RGB; 

	// Compute the number of bytes in the array of color 
	// indices and store the result in biSizeImage. 
	// For Windows NT, the width must be DWORD aligned unless 
	// the bitmap is RLE compressed. This example shows this. 
	// For Windows 95/98/Me, the width must be WORD aligned unless the 
	// bitmap is RLE compressed.
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * 24 +31) & ~31) /8
		* pbmi->bmiHeader.biHeight; 
	// Set biClrImportant to 0, indicating that all of the 
	// device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0; 
	return TRUE; 
} 

BOOL CMyPicFullScreenShow::CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC) 
{ 
	HANDLE hf;                 // file handle 
	BITMAPFILEHEADER hdr;       // bitmap file-header 
	PBITMAPINFOHEADER pbih;     // bitmap info-header 
	LPBYTE lpBits;              // memory pointer 
	DWORD dwTotal;              // total count of bytes 
	DWORD cb;                   // incremental count of bytes 
	BYTE *hp;                   // byte pointer 
	DWORD dwTmp; 

	pbih = (PBITMAPINFOHEADER) pbi; 
	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits) 
		return FALSE;

	// Retrieve the color table (RGBQUAD array) and the bits 
	// (array of palette indices) from the DIB. 
	if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, 
		DIB_RGB_COLORS)) 
	{
		return FALSE;
	}

	// Create the .BMP file. 
	hf = CreateFile(pszFile, 
		GENERIC_READ | GENERIC_WRITE, 
		(DWORD) 0, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL); 
	if (hf == INVALID_HANDLE_VALUE) 
		return FALSE;
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
	// Compute the size of the entire file. 
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof(RGBQUAD) + pbih->biSizeImage); 
	hdr.bfReserved1 = 0; 
	hdr.bfReserved2 = 0; 

	// Compute the offset to the array of color indices. 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof (RGBQUAD); 

	// Copy the BITMAPFILEHEADER into the .BMP file. 
	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
		(LPDWORD) &dwTmp,  NULL)) 
	{
		return FALSE;
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
		+ pbih->biClrUsed * sizeof (RGBQUAD), 
		(LPDWORD) &dwTmp, ( NULL))) 
		return FALSE;

	// Copy the array of color indices into the .BMP file. 
	dwTotal = cb = pbih->biSizeImage; 
	hp = lpBits; 
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
		return FALSE;
	// Close the .BMP file. 
	if (!CloseHandle(hf)) 
		return FALSE;

	// Free memory. 
	GlobalFree((HGLOBAL)lpBits);

	return TRUE;
}

BOOL CMyPicFullScreenShow::SaveBmpFile(CRect lpRect,CString path)
{
	// 屏幕和内存设备描述表
	HDC hScrDC, hMemDC;      
	// 位图句柄
	HBITMAP hBitmap,hOldBitmap;   
	// 选定区域坐标
	int       nX, nY, nX2, nY2;      
	// 位图宽度和高度 
	int       nWidth, nHeight;      
	
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return FALSE;

	//为屏幕创建设备描述表
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect.left;
	nY = lpRect.top;
	nX2 = lpRect.right;
	nY2 = lpRect.bottom;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	POINT point;
	point.x = nX;
	point.y = nY;
	::ScreenToClient(m_hWnd,&point);

	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	CClientDC ddc(this);
	BitBlt(hMemDC,0,0, nWidth,nHeight,/*hScrDC, nX, nY,*/ ddc.GetSafeHdc(),point.x,point.y,CAPTUREBLT|SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);

		// 24位图的BITMAPINFO
    BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
    memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
    BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
    pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
    pInfo_Header->biWidth = nWidth;   
    pInfo_Header->biHeight = nHeight;   
    pInfo_Header->biPlanes = 1;   
    pInfo_Header->biBitCount = 24;   
    pInfo_Header->biCompression = BI_RGB;

	 // 获得数据buf
    DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
    BYTE * pBuffer = new BYTE[bufSize];

	int aHeight=pInfo_Header->biHeight;

    if(::GetDIBits(hMemDC, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
    {
       return FALSE;
    }

	//保存到文件并创建位图结构
	BITMAPFILEHEADER bmfh;
	ZeroMemory(&bmfh,sizeof(BITMAPFILEHEADER));

	*((char*)&bmfh.bfType) = 'B';
	*(((char*)&bmfh.bfType) + 1) = 'M';

	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + (m_Width * m_Height) * pInfo_Header->biBitCount / 8;
	CFile file;
	if(file.Open(path.LockBuffer(),CFile::modeWrite|CFile::modeCreate))
	{
		file.Write(&bmfh,sizeof(BITMAPFILEHEADER));
		file.Write(&(pBITMAPINFO->bmiHeader),sizeof(BITMAPINFOHEADER));
		file.Write(pBuffer,bufSize);
		file.Close();
	}
	else
	{
		DeleteDC(hScrDC);
		DeleteDC(hMemDC);
		::DeleteObject(hBitmap);
		return FALSE;
	}

	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	::DeleteObject(hBitmap);
	return TRUE;
}

void CMyPicFullScreenShow::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_StartPos = point;
	m_EndPos = point;
	m_MouseClickDown = true;
	this->InvalidateRect(&m_Rect);
	CRect rect;
	this->GetWindowRect(&rect);
	int left = rect.left;
	int top  = rect.top;

	int wndWidth = rect.Width();
	int wndHeight = rect.Height();

	if(point.x<m_Width&&point.y<m_Height)
		ClipCursor(&CRect(0,0,m_Width,m_Height));  //// 锁定鼠标只能在图片大小范围内
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMyPicFullScreenShow::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_MouseClickDown&&point.x<this->m_Width&&point.y<this->m_Height)
	{
		CClientDC dc(this);
		CPen* pOldPen = NULL;
		CBrush* pOldBrush = NULL;

		HPEN hpen = ::CreatePen(PS_DOT,1,RGB(255,0,0));
		pOldPen = dc.SelectObject(CPen::FromHandle(hpen));
		pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);

		dc.SetROP2(R2_NOTXORPEN);  //屏幕的颜色跟画笔的颜色取反色。重新画，覆盖上旧图,相当于删除旧图形。
		dc.Rectangle(m_StartPos.x,m_StartPos.y,m_EndPos.x,m_EndPos.y);
		dc.Rectangle(m_StartPos.x,m_StartPos.y,point.x,point.y);

		if (pOldPen != NULL)
			dc.SelectObject(pOldPen);
		if (pOldBrush != NULL)
			dc.SelectObject(pOldBrush);
		DeleteObject(hpen); 

		m_Rect.SetRect(m_StartPos,point);
	}
	m_EndPos=point;

	CDialogEx::OnMouseMove(nFlags, point);
}

void CMyPicFullScreenShow::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//g_MenuLeftMouseUp.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	CClientDC dc(this);
	CPen* pOldPen = NULL;
	CBrush* pOldBrush = NULL;
	if(m_MouseClickDown)
	{
		HPEN hpen = ::CreatePen(PS_DOT,1,RGB(255,0,0));
		pOldPen = dc.SelectObject(CPen::FromHandle(hpen));
		pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);

		dc.SetROP2(R2_NOTXORPEN);  //
		dc.Rectangle(m_StartPos.x,m_StartPos.y,m_EndPos.x,m_EndPos.y);//擦除最后一次鼠标移动画的矩形。
		dc.Rectangle(m_StartPos.x,m_StartPos.y,point.x,point.y);      // 再重画新的矩阵
		if (pOldPen != NULL)
			dc.SelectObject(pOldPen);
		if (pOldBrush != NULL)
			dc.SelectObject(pOldBrush);
		DeleteObject(hpen); 
	
		m_MouseClickDown = false;

		ClipCursor(NULL);       ////释放鼠标

		if(point.x<m_StartPos.x)
			m_Rect.SetRect(point,m_StartPos);
		else
			m_Rect.SetRect(m_StartPos,point);

		/////////////弹出自定义菜单////////////////
		POINT   pt;   
		GetCursorPos(&pt);
		if(m_StartPos!=point)
		{
			if(m_Rect.Height()<3 ||m_Rect.Width()<3)
			{
				g_MenuLeftMouseUp.GetSubMenu(0)->EnableMenuItem(0,0);
				g_MenuLeftMouseUp.GetSubMenu(0)->EnableMenuItem(1,0);
			}
			g_MenuLeftMouseUp.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
		}

		////////////////////刷新掉当前的矩阵/////////
		this->InvalidateRect(&m_Rect);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

///////////////////////////左键功能菜单实现////////////////////
void CMyPicFullScreenShow::OnLeftClickFullScreen()
{
	// TODO: 在此添加命令处理程序代码
	g_IsFullScreen = false;
	(g_MenuLeftMouseUp.GetSubMenu(0))->CheckMenuItem(ID__AB32773,MF_UNCHECKED | MF_BYCOMMAND);
	this->OnOK();
}

void CMyPicFullScreenShow::OnClickLeftSaveBmp()
{
	// TODO: 在此添加命令处理程序代码
	this->UpdateData();
	SYSTEMTIME time;
	::GetLocalTime(&time);
	CString lpTime=_T("");
	if(time.wMinute<10&&time.wSecond<10)
		lpTime.Format(_T("TC截图%d%d%d%d%0d%0d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else if(time.wMinute<10)
		lpTime.Format(_T("TC截图%d%d%d%d%0d%d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else if(time.wSecond<10)
		lpTime.Format(_T("TC截图%d%d%d%d%d%0d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else
		lpTime.Format(_T("TC截图%d%d%d%d%d%d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);

	TCHAR fileBuffer[256]={_T("TC")};
	::memset(fileBuffer,0,256*sizeof(TCHAR));
	::memcpy(fileBuffer,lpTime.LockBuffer(),lpTime.GetLength()*sizeof(TCHAR));
	// 获取具体位置的图像
	CRect helpRect = m_Rect;
	this->ClientToScreen(&helpRect);
	int off = 1;
	helpRect.left = helpRect.left+off;
	helpRect.top = helpRect.top+off;
	helpRect.right = helpRect.right-off;
	helpRect.bottom = helpRect.bottom-off;
	HBITMAP tbmp=CopyRectToBitmap(helpRect);
	if(tbmp==NULL)
	{
		//::AfxMessageBox(_T("屏幕位图失败!0"));
		::DeleteObject(tbmp);
		return;
	}

	PBITMAPINFO pbmp;
	if(!CreateBitmapInfoStruct(tbmp, pbmp))
	{
		//::AfxMessageBox(_T("位图创建失败!1"));
		::DeleteObject(tbmp);
		return;
	}

	TCHAR OldPath[MAX_PATH]={0};
	::GetCurrentDirectoryW(MAX_PATH,OldPath);
	CFileDialog PathDlg(FALSE, _T("*.bmp"), fileBuffer, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Save File(*.bmp)|*.bmp||"));

	PathDlg.m_ofn.lpstrDefExt=_T("bmp");
	CString pathStr=_T("");	

	if(PathDlg.DoModal()==IDOK)
	{
		pathStr = PathDlg.GetPathName();
		HDC hdc = ::GetDC(NULL);
		if(!CreateBMPFile(pathStr.LockBuffer(), pbmp, tbmp,hdc))
		{
			//::AfxMessageBox(_T("位图保存失败!2"));
		}
		::ReleaseDC(NULL,hdc);
		//SaveBmpFile(helpRect,PathDlg.GetPathName());
	}
	this->InvalidateRect(&m_Rect);
	::DeleteObject(tbmp);
	::SetCurrentDirectoryW(OldPath);
}


void CMyPicFullScreenShow::OnClickLeftCallSystemPicture()
{
	// TODO: 在此添加命令处理程序代码
	CRect helpRt = m_Rect;
	this->ClientToScreen(&helpRt);
	int off = 1;
	helpRt.left = m_Rect.left+off;
	helpRt.top = m_Rect.top+off;
	helpRt.right = m_Rect.right-off;
	helpRt.bottom = m_Rect.bottom-off;
	
	CString pathStr = g_CurrentExePath+_T("tctemp.bmp");	
	if(SaveBmpFile(helpRt,pathStr))
	{
		char path[MAX_PATH]={0};
		USES_CONVERSION;
		::strcat(path,"mspaint.exe ");
		::strcat(path,W2A(pathStr.LockBuffer()));
		::WinExec(path,SW_SHOWNORMAL);
	}
}


void CMyPicFullScreenShow::OnClickLeftCallABmakePicture()
{
	// TODO: 在此添加命令处理程序代码
	CRect helpRt = m_Rect;
	this->ClientToScreen(&helpRt);
	int off = 1;
	helpRt.left = m_Rect.left+off;
	helpRt.top = m_Rect.top+off;
	helpRt.right = m_Rect.right-off;
	helpRt.bottom = m_Rect.bottom-off;
	
	CString pathStr = g_CurrentExePath+_T("tctemp.bmp");	
	if(SaveBmpFile(helpRt,pathStr))
	{
		/*if(g_DrawPicture.IsWindowVisible())
		{
			g_DrawPicture.Loadbmp(pathStr);
		}
		else
		{
			g_PicCheck.SetCheck(BST_CHECKED);
			g_DrawPicture.ShowWindow(TRUE);
			g_DrawPicture.Loadbmp(pathStr);
		}*/
		theApp.pPropSheet->activeCurrentPage(5);
		theApp.pPropSheet->m_DrawPicWnd.Loadbmp(pathStr);
	}
}

///////////////////////////////////鼠标右键菜单的处理//////////////////////////

void CMyPicFullScreenShow::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_RightPos = point;
	(g_MenuRightMouseUp.GetSubMenu(0))->EnableMenuItem(ID_32790,MF_GRAYED);
	(g_MenuRightMouseUp.GetSubMenu(0))->EnableMenuItem(ID_32791,MF_GRAYED);
	g_MenuRightMouseUp.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CMyPicFullScreenShow::OnRightClickFullScreen()
{
	// TODO: 在此添加命令处理程序代码
	g_IsFullScreen = false;
	(g_MenuRightMouseUp.GetSubMenu(0))->CheckMenuItem(ID__32787,MF_UNCHECKED | MF_BYCOMMAND);
	this->OnOK();
}


void CMyPicFullScreenShow::OnAddColor1()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(1,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor2()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(2,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor3()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(3,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor4()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(4,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor5()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(5,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor6()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(6,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor7()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(7,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor8()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(8,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor9()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(9,m_RightPos,0);
}


void CMyPicFullScreenShow::OnAddColor10()
{
	// TODO: 在此添加命令处理程序代码
	g_PickColorDlg.RightClickPickColor(10,m_RightPos,0);
}


void CMyPicFullScreenShow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//SetWindowPos(&wndTopMost,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);
	if(g_HbitMap)
	{
		BITMAP bitmap;
		CBitmap *btm;
		btm=NULL;
		btm = CBitmap::FromHandle(g_HbitMap);	
		btm->GetBitmap(&bitmap);
		m_Width = bitmap.bmWidth;
		m_Height = bitmap.bmHeight;
		CClientDC pDC(this);
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(&pDC);
		dcCompatible.SelectObject(btm);

		CRect rect;
		GetClientRect(&rect);
		dc.BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
	}
}




BOOL CMyPicFullScreenShow::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
