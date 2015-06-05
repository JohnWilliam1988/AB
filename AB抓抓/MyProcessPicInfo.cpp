// MyProcessPicInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyProcessPicInfo.h"
#include "afxdialogex.h"

extern  HWND				g_ProcessPicInfoHWND;
extern  CMyShowPic			g_ShowPic;
extern	 CString	g_CurrentExePath;
IMPLEMENT_DYNAMIC(CMyProcessPicInfo, CMFCPropertyPage)

CMyProcessPicInfo::CMyProcessPicInfo(CWnd* pParent /*=NULL*/)
	: CMFCPropertyPage(CMyProcessPicInfo::IDD)
{
	
}

CMyProcessPicInfo::~CMyProcessPicInfo()
{
}

void CMyProcessPicInfo::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SELECTEWNDHANDLE, m_SelectWndHandle);
	DDX_Control(pDX, IDC_CHECK_SPECIFYHANDLE, m_WndCheckControl);
	DDX_Control(pDX, IDC_BUTTON_SHOWWNDPIC, m_ShowWndPic);
	DDX_Control(pDX, IDC_STATIC_PRINTTIP, m_PrintTip);
}

BEGIN_MESSAGE_MAP(CMyProcessPicInfo, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_LOADBMP, &CMyProcessPicInfo::OnBnClickedButtonLoadbmp)
	ON_BN_CLICKED(IDC_BUTTON_BMPEIDT, &CMyProcessPicInfo::OnBnClickedButtonEditbmp)
	ON_BN_CLICKED(IDC_BUTTON_SELECTEWNDHANDLE, &CMyProcessPicInfo::OnBnClickedButtonSelectewndhandle)
	ON_BN_CLICKED(IDC_CHECK_SPECIFYHANDLE, &CMyProcessPicInfo::OnBnClickedCheckSpecifyhandle)
	ON_BN_CLICKED(IDC_BUTTON_SHOWWNDPIC, &CMyProcessPicInfo::OnBnClickedButtonShowwndpic)
	ON_WM_COPYDATA()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyProcessPicInfo::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPIC, &CMyProcessPicInfo::OnBnClickedButtonSavepic)
END_MESSAGE_MAP()


// CMyProcessPicInfo 消息处理程序

void CMyProcessPicInfo::setPicturePathText(CString path)
{
	((CEdit*)this->GetDlgItem(IDC_EDIT_PICPATH))->SetWindowTextW(path);
}

void CMyProcessPicInfo::setStartPortText(CString port)
{
	((CEdit*)this->GetDlgItem(IDC_EDIT_STARTPOINT))->SetWindowTextW(port);
}

void CMyProcessPicInfo::setEndPortText(CString port)
{
	((CEdit*)this->GetDlgItem(IDC_EDIT_ENDPOINT))->SetWindowTextW(port);
}

void CMyProcessPicInfo::setSizeText(CString size)
{
	((CEdit*)this->GetDlgItem(IDC_EDIT_SIZEPIC))->SetWindowTextW(size);
}

////////`控件按钮事件//////////////////////
void CMyProcessPicInfo::OnBnClickedButtonLoadbmp()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR OldPath[MAX_PATH]={0};
	::GetCurrentDirectoryW(MAX_PATH,OldPath);

	CFileDialog openDLG(TRUE);
	openDLG.m_ofn.lpstrFilter=_T("24位位图(*.bmp)|*.bmp||");
	if(openDLG.DoModal()==IDOK)
	{
		m_PicPath=openDLG.GetPathName();
		g_ShowPic.ShowBmp(m_PicPath);
		setPicturePathText(openDLG.GetPathName());
	}
	::SetCurrentDirectoryW(OldPath);
}


void CMyProcessPicInfo::OnBnClickedButtonEditbmp()
{
	// TODO: 在此添加控件通知处理程序代码
	wchar_t pathw[MAX_PATH] = {0};
	//::GetSystemDirectoryW(pathw,MAX_PATH);
	::GetCurrentDirectoryW(MAX_PATH,pathw);

	CString pathName=_T("");
	while(true)
	{
		int pos = m_PicPath.Find(_T("\\"));
		if(pos == -1)
			break;
		pathName +=m_PicPath.Left(pos+1);
		m_PicPath = m_PicPath.Right(m_PicPath.GetLength()-pos-1);
	}

	::SetCurrentDirectoryW(pathName);

	char path[MAX_PATH]={0};
	USES_CONVERSION;
	::strcat(path,"mspaint.exe ");
	::strcat(path,W2A(m_PicPath.LockBuffer()));
	::WinExec(path,SW_SHOWNORMAL);
	/////// 还原路径 //////////////
	::SetCurrentDirectoryW(pathw);
}


BOOL CMyProcessPicInfo::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	CWnd * pGroup = GetDlgItem(IDC_STATIC_GROUP);
	// TODO:  在此添加额外的初始化
	g_ShowPic.Create(IDD_DIALOG_SHOWPIC,pGroup);

	//设置页面的位置
    CRect p_Rect;
    pGroup->GetClientRect(&p_Rect);
	g_ShowPic.MoveWindow(&p_Rect);
	g_ShowPic.ShowWindow(TRUE);

	m_SelectWndHandle.m_bTransparent = TRUE;
	m_SelectWndHandle.m_nFlatStyle = CMFCButton::BUTTONSTYLE_SEMIFLAT;
	m_SelectWndHandle.SetImage(IDB_BTN1);
	m_SelectWndHandle.SetWindowText(_T("选择句柄"));
	m_SelectWndHandle.m_bRightImage = TRUE;
	m_SelectWndHandle.m_bTopImage = FALSE;

	m_SelectWndHandle.SizeToContent();
	m_SelectWndHandle.Invalidate();
	m_SelectWndHandle.EnableWindow(FALSE);

	m_ShowWndPic.EnableWindow(FALSE);

	g_ProcessPicInfoHWND = m_hWnd;

	setPicturePathText(_T("点击载入位图之后才会显示位图路径!"));
	m_PrintTip.SetTextColor(RGB(6,121,50));
	//this->SetBackgroundColor(0xf5e7dd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMyProcessPicInfo::OnBnClickedButtonSelectewndhandle()
{
	// TODO: 在此添加控件通知处理程序代码
	////////在这里显示进程的句柄链表///////////
	m_WndOneHandle.DoModal();
	this->GetDlgItem(IDC_EDIT_Specify)->SetWindowTextW(m_WndOneHandle.m_ListWndHandle);
}

void CMyProcessPicInfo::OnBnClickedCheckSpecifyhandle()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_WndCheckControl.GetCheck() == BST_CHECKED)
	{
		m_SelectWndHandle.EnableWindow();
		m_ShowWndPic.EnableWindow();
	}
	else
	{
		m_SelectWndHandle.EnableWindow(FALSE);
		m_ShowWndPic.EnableWindow(FALSE);
	}
}

bool CMyProcessPicInfo::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName)
{
	if(!hBitmap)
		return false;
	HDC     hDC;         
	  
	//当前显示分辨率下每个像素所占字节数
	WORD    wBitCount;
	//位图中每个像素所占字节数
	//定义调色板大小， 位图中像素字节大小 ，  位图文件大小 ， 写入文件字节数
	DWORD           dwPaletteSize=0,dwBmBitsSize,dwDIBSize, dwWritten;
	BITMAP          Bitmap;
	//位图属性结构
	BITMAPFILEHEADER   bmfHdr;        
	//位图文件头结构
	BITMAPINFOHEADER   bi;            
	//位图信息头结构 
	LPBITMAPINFOHEADER lpbi;          
	//指向位图信息头结构
	HANDLE          fh, hDib, hPal;
	HPALETTE     hOldPal=NULL;
	
	wBitCount = 24;

	//设置位图信息头结构
	int wordNum = GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	if(wordNum == 0)
		return false;

	bi.biSize            = sizeof(BITMAPINFOHEADER);
	bi.biWidth           = Bitmap.bmWidth;
	bi.biHeight          = Bitmap.bmHeight;
	bi.biPlanes          = 1;
	bi.biBitCount         = wBitCount;
	bi.biCompression      = BI_RGB;
	bi.biSizeImage        = 0;
	bi.biXPelsPerMeter     = 0;
	bi.biYPelsPerMeter     = 0;
	bi.biClrUsed         = 0;
	bi.biClrImportant      = 0;

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;
	//为位图内容分配内存

	hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	// 处理调色板   
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal=SelectPalette(hDC,(HPALETTE)hPal,FALSE);
		RealizePalette(hDC);
	}
	// 获取该调色板下新的像素值
	GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
	//恢复调色板   
	if (hOldPal)
	{
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	//创建位图文件    
	fh=CreateFile(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh==INVALID_HANDLE_VALUE)
		return FALSE;
	// 设置位图文件头
	bmfHdr.bfType = 0x4D42;  // "BM"
	dwDIBSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;

	BOOL bw1=FALSE;
	BOOL bw2=FALSE;

	// 写入位图文件头
	bw1=WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// 写入位图文件其余内容
	bw2=WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize , &dwWritten, NULL); 
	//清除   
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	if(bw1&&bw2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void CMyProcessPicInfo::OnBnClickedButtonShowwndpic()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();
	CString wndStr;
	this->GetDlgItem(IDC_EDIT_Specify)->GetWindowTextW(wndStr);
	int m_WndHandle = ::wcstol(wndStr,NULL,10);

	HWND src_hWnd = (HWND)m_WndHandle;
	RECT rc;
	::GetWindowRect(src_hWnd, &rc);
	// 24位图的BITMAPINFO
	BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
	memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
	BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
	pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
	pInfo_Header->biWidth = rc.right - rc.left;   
	pInfo_Header->biHeight = (rc.bottom - rc.top);   
	pInfo_Header->biPlanes = 1;   
	pInfo_Header->biBitCount = 24;   
	pInfo_Header->biCompression = BI_RGB;

	// 创建兼容DC 打印目标窗体
	HDC src_hdc = ::GetWindowDC(src_hWnd);        
	HBITMAP hBitmap = ::CreateCompatibleBitmap(src_hdc,pInfo_Header->biWidth, pInfo_Header->biHeight);
	HDC hdcCompatible = ::CreateCompatibleDC(src_hdc); 
	HBITMAP oldbmp =(HBITMAP)::SelectObject(hdcCompatible, hBitmap);
	::PrintWindow(src_hWnd, hdcCompatible, 0/*PW_CLIENTONLY*/);
	::ReleaseDC(src_hWnd, src_hdc);
	::SelectObject(hdcCompatible, oldbmp);

	if(!hBitmap)
	{
		::ReleaseDC(src_hWnd, src_hdc);
		::DeleteDC(hdcCompatible);
		return ;
	}

	SaveBitmapToFile(hBitmap,g_CurrentExePath+ _T("temp.bmp"));
	//m_showPic.ShowHBitBmp(hBitmap);
	g_ShowPic.ShowBmp(g_CurrentExePath+ _T("temp.bmp"));

	::ReleaseDC(src_hWnd, src_hdc);
	::DeleteDC(hdcCompatible);
	::DeleteObject(hBitmap);
	return ;
}


BOOL CMyProcessPicInfo::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(pCopyDataStruct->dwData==0)
	{
		setStartPortText((TCHAR*)pCopyDataStruct->lpData);
	}
	else if(pCopyDataStruct->dwData==1)
	{
		setEndPortText((TCHAR*)pCopyDataStruct->lpData);
	}
	else if(pCopyDataStruct->dwData==2)
	{
		setSizeText((TCHAR*)pCopyDataStruct->lpData);
	}
	return CMFCPropertyPage::OnCopyData(pWnd, pCopyDataStruct);
}


void CMyProcessPicInfo::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMyProcessPicInfo::OnBnClickedButtonSavepic()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR oldPath[MAX_PATH]={0};
	::GetCurrentDirectoryW(MAX_PATH,oldPath);
	CFileDialog saveDlg(FALSE, _T("*.bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Save File(*.bmp)|*.bmp||"));
	saveDlg.m_ofn.lpstrDefExt=_T("bmp");
	if(saveDlg.DoModal() == IDOK)
	{
		CString fileName = saveDlg.GetPathName();
		BOOL ret = ::CopyFileW(g_CurrentExePath+_T("abpic.bmp"),fileName,FALSE);
		DWORD err = ::GetLastError();
	}
	::SetCurrentDirectoryW(oldPath);
}
